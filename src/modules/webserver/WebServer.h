#include "ESPAsyncWebServer.h"
#include <DNSServer.h>
#include <HTTPClient.h>
#include "SPIFFS.h"
#include "helpers/Util.h"

class WebServer{

    public:
      WebServer(){
        _server = NULL;
      };
      void setup(int port);
      static String processor(const String& var);
      void writeData();
  
    protected:
      AsyncWebServer *_server;
      
};