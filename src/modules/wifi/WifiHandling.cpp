#include "WifiHandling.h"
#include <esp_wifi.h>

IPAddress apIP(76,76,76,76);
const byte DNS_PORT = 53;

WifiHandling::WifiHandling(){}

void WifiHandling::start(const char* wifi_ssid, const char* wifi_pass){

    wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
    wifi_init_config.ampdu_rx_enable = 0;
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_init_config));

    SPIFFS.begin(true);
    WiFi.disconnect(true);   
    WiFi.mode(WIFI_AP_STA);

    cJSON *credentials = Util::getInstance().getCredentials();
    int retry_connect = 0;
    
    if ((credentials != NULL))
    {  
      const char* ssid = cJSON_GetObjectItem(credentials,"ssid")->valuestring;
      const char* password = cJSON_GetObjectItem(credentials,"password")->valuestring;
      
      WiFi.disconnect(true);
      WiFi.enableSTA(true);
      WiFi.begin(ssid, password);
      
      while ((WiFi.status() != WL_CONNECTED) && (retry_connect < 5))
      {
        WiFi.begin(ssid, password);
        delay(3000);
        retry_connect++;
        Serial.println("connecting ...");
      }

      if(WiFi.status() == WL_CONNECTED){
        Serial.println(WiFi.localIP()); 
        Serial.println("connected!");
      }
    }
    
    if ((credentials == NULL) || (retry_connect == 5))
    {
      Serial.println("No valid file found!");
      WiFi.disconnect(true);
      WiFi.enableAP(true);
      delay(100);

      while(!(WiFi.softAPIP() == apIP)){
        WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
        delay(100);
      }

      IPAddress myIP = WiFi.softAPIP();
    }
}

void* WifiHandling::thread_helper(void *context){
  while (true)
    ((WifiHandling *)context)->update();
}

void WifiHandling::update(){
    dnsServer.processNextRequest();
    delay(10);
}