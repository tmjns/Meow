#include "controller.h"

Controller::Controller(){}

void Controller::start() {
    cJSON *settings = Util::getInstance().getSettings(); 
    const char* wifi_ssid = cJSON_GetObjectItem(settings,"wifi_ssid")->valuestring;
    const char* wifi_pass = cJSON_GetObjectItem(settings,"wifi_pass")->valuestring; 
    
    wifi.start(wifi_ssid,wifi_pass);
    webserver.setup(80);
    module.init();
    module.connectToSlack();
}

void Controller::update() {
    webserver.writeData();
    module.update();
}
