#include "helpers/common.h"
#include "helpers/Util.h"

class Module {
    public:
        Module();
        
        void init();
        void sendPing();
        int processSlackMessage(char *payload);
        void webSocketEvent(WStype_t type, uint8_t *payload, size_t len);
        bool connectToSlack();
        void update();
        
        int smartPaw = 14;
        long nextCmdId = 1;
        bool connected = false;
        unsigned long lastPing = 0;

    private:
        WebSocketsClient webSocket;
};