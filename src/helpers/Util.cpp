#include "Util.h"

cJSON *Util::getSettings(boolean reload){
  
  SPIFFS.begin(true);

  if ((reload) || (this->settings==NULL)){

    File settings_file = SPIFFS.open("/settings.json", "r+");
    String temp_settings = "";

    for(int i=0;i<settings_file.size();i++){
      temp_settings+=char(settings_file.read());
    }

    Serial.println(temp_settings);
    settings_file.close();
    this->settings = cJSON_Parse(temp_settings.c_str());

  }
  return this->settings;
}

cJSON *Util::getCredentials(boolean reload){
   
  if ((reload) || (this->credentials==NULL)){
    
    File credentials_file = SPIFFS.open("/www/credentials.json", "r+");
    String temp_credentials = "";

    for(int i=0;i<credentials_file.size();i++){
      temp_credentials+=char(credentials_file.read());
    }

    Serial.println(temp_credentials);
    credentials_file.close();
    this->credentials = cJSON_Parse(temp_credentials.c_str());

  }
  return this->credentials;
}

void Util::startMDNS(){
  if(!MDNS.begin("meow")) {
    Serial.println("Error starting mDNS");
    return;
  } 
}