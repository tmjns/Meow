#include <WiFi.h>
#include <DNSServer.h>
#include <pthread.h>

#include "helpers/common.h"
#include "helpers/Util.h"

class WifiHandling{

    public:
        WifiHandling();
        void start(const char* wifi_ssid, const char* wifi_pass);
        void update();

    private:
        static void *thread_helper(void *context);
        pthread_t loop_thread;
        DNSServer dnsServer;
};
