#include "Arduino.h"

#include "helpers/common.h"
#include "helpers/Util.h"

#include "modules/module/module.h"
#include "modules/wifi/WifiHandling.h"
#include "modules/webserver/WebServer.h"

class Controller{
    
    public:
        Controller();
        void start();
        void update();
      
    private:
        WifiHandling wifi;
        WebServer webserver;
        Module module;
};