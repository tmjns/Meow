#include "module.h"

Module::Module(){}

void Module::init(){
  pinMode(smartPaw, OUTPUT);
  digitalWrite(smartPaw, LOW);
}

void Module::sendPing() {
  printf("%s\n", "PING%PONG");
}

int Module::processSlackMessage(char *payload){ 

  cJSON *root = cJSON_Parse(payload);
  if (!cJSON_IsObject(root)) {
		return EXIT_FAILURE;
	}
  /////////////////////////////////////////////////////////////////////////////////
  cJSON *user = NULL;
  cJSON *user_id = NULL;
  cJSON *action = NULL;
  cJSON *blocks = cJSON_GetObjectItem(root,"blocks");
  cJSON *credentials = Util::getInstance().getCredentials();

  int i;
  
  for (i = 0 ; i < cJSON_GetArraySize(blocks) ; i++)
  {
    cJSON *blocks_item = cJSON_GetArrayItem(blocks, i);
    cJSON *elements = cJSON_GetArrayItem(blocks_item, 2);

    for (i = 0 ; i < cJSON_GetArraySize(elements) ; i++)
    {
      cJSON *elements_item = cJSON_GetArrayItem(elements, i);
      cJSON *elements_2 = cJSON_GetArrayItem(elements_item, 1);  

      for (i = 0 ; i < cJSON_GetArraySize(elements_2) ; i++)
      { 
        cJSON *elements_2_item = cJSON_GetArrayItem(elements_2, i);
        user_id = cJSON_GetObjectItemCaseSensitive(elements_2_item, "user_id");

        if (cJSON_IsString(user_id) && (user_id->valuestring != NULL))
        {  
          const char* slack_user_id = cJSON_GetObjectItem(credentials,"user")->valuestring;
          if (strcmp(user_id->valuestring, slack_user_id) == 0)
          {
            Serial.println("MEOW ON");
            digitalWrite(smartPaw, HIGH);
          }
        }
      } 
    }
  }
  /////////////////////////////////////////////////////////////////////////////////
  user = cJSON_GetObjectItem(root, "user");
  action = cJSON_GetObjectItem(root, "type");

  if (cJSON_IsString(action) && (action->valuestring != NULL))
  {   
    const char* slack_user_id = cJSON_GetObjectItem(credentials,"user")->valuestring;
    if (strcmp(action->valuestring, "reaction_added") == 0 && strcmp(user->valuestring, slack_user_id) == 0)
    {
      Serial.println("MEOW OFF");
      digitalWrite(smartPaw, LOW);
    }
  }
  /////////////////////////////////////////////////////////////////////////////////
  cJSON_Delete(root);
  return true;

}

void Module::webSocketEvent(WStype_t type, uint8_t *payload, size_t len) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WebSocket] Disconnected :-( \n");
      connected = false;
      break;

    case WStype_CONNECTED:
      Serial.printf("[WebSocket] Connected to: %s\n", payload);
      sendPing();
      break;

    case WStype_TEXT:
      Serial.printf("[WebSocket] Message: %s\n", payload);
      processSlackMessage((char*)payload);
      break;
    
    case WStype_ERROR:
      Serial.printf("[WebSocket] Error occurred :`-( \n");
      break;
      
    default:
      break;
  }
}

bool Module::connectToSlack() {
  HTTPClient http;
  /////////////////////////////////////////////////////////////////////////////////
  cJSON *credentials = Util::getInstance().getCredentials();
  cJSON *token = cJSON_GetObjectItem(credentials,"token");
  String SLACK_API_TOKEN;
  if(!token)
  { 
    Serial.println("No valid Token!");
  }else{
    Serial.println("Token");
    const char* slack_api_token = cJSON_GetObjectItem(credentials,"token")->valuestring;
    SLACK_API_TOKEN = slack_api_token;
  }
  http.begin("https://slack.com/api/rtm.connect?token=" + SLACK_API_TOKEN, SLACK_SSL_FINGERPRINT);
  /////////////////////////////////////////////////////////////////////////////////
  int httpCode = http.GET();

  if (httpCode != HTTP_CODE_OK) {
    Serial.printf("HTTP GET failed with code %d\n", httpCode);
    return false;
  }

  WiFiClient *client = http.getStreamPtr();
  client->find("wss:\\/\\/");
  String host = client->readStringUntil('\\');
  String path = client->readStringUntil('"');
  path.replace("\\/", "/");

  Serial.println("WebSocket Host=" + host + " Path=" + path);
  webSocket.beginSSL(host, 443, path, "", "");
  webSocket.onEvent(std::bind(&Module::webSocketEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
  return true;
}

void Module::update(){
  webSocket.loop();

  if (connected) {
    if (millis() - lastPing > 5000) {
      sendPing();
      lastPing = millis();
    }
  } else {
    connected = connectToSlack();
    if (!connected) {
      Serial.println("Disconnected from Slack");
      delay(500);
    }
  }
}