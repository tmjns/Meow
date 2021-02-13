#pragma once
#include "common.h"

class Util{

  public:
    static Util& getInstance(){
        static Util instance;
        return instance;
    }

    Util(Util const&) = delete;
    void operator=(Util const&) = delete;

    cJSON *getSettings(boolean reload = false);
    cJSON *getCredentials(boolean reload = false);
    void startMDNS();
         
  private:
    Util() {
    }
    cJSON *settings;
    cJSON *credentials;
};