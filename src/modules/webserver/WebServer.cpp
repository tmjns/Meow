#include "WebServer.h"

void WebServer::setup(int port){
    if(!SPIFFS.begin(true)){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    _server = new AsyncWebServer(port);

    if(WiFi.status() == WL_CONNECTED && WiFi.mode(WIFI_STA)){
      Util::getInstance().startMDNS(); 
      _server->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/www/config.html","text/html", false, processor);
      });
    }

    _server->serveStatic("/", SPIFFS, "/www/").setCacheControl("max-age=10").setDefaultFile("index.html");
    
    _server->on("/reboot", HTTP_GET, [](AsyncWebServerRequest *request){
      request->redirect("http://meow.local/");
      delay(100);
      ESP.restart();
    });

    _server->begin();
}

String WebServer::processor(const String& var){
  cJSON *credentials = Util::getInstance().getCredentials();
  if(var == "ssid"){
    return cJSON_GetObjectItem(credentials,"ssid")->valuestring;
  }
  
  if(var == "password"){
    return cJSON_GetObjectItem(credentials,"password")->valuestring;
  }

  cJSON *token=cJSON_GetObjectItem(credentials,"token");
  cJSON *user=cJSON_GetObjectItem(credentials,"user");

  if(token && var == "api_token"){
    return cJSON_GetObjectItem(credentials,"token")->valuestring;
  }
  
  if(user && var == "user_id"){
    return cJSON_GetObjectItem(credentials,"user")->valuestring;
  }
  
  return String();
}

void WebServer::writeData(){
  _server->onRequestBody([](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {

    File credentials_json = SPIFFS.open("/www/credentials.json", "w");
      for(size_t i=0; i<len; i++){
        credentials_json.write(data[i]);
    }
    credentials_json.close();

    request->send(200, "text/plain", "true");
  }); 
}