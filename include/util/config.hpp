#pragma once

#include <vector>

#define STR_IMPL(x) #x
#define STR(x) STR_IMPL(x)

namespace inst::config
{
    static const std::string appDir = "sdmc:/switch/Awoo-Installer";
    static const std::string configPath = appDir + "/config.json";
    static const std::string appVersion = STR(APP_VERSION);

    extern std::string sigPatchesUrl;
    extern std::string lastNetUrl;
    extern std::string lastUserName;
    extern std::string lastPassword;
    extern std::string aliDriveToken;
    extern std::vector<std::string> updateInfo;
    extern int languageSetting;
    extern bool ignoreReqVers;
    extern bool validateNCAs;
    extern bool overClock;
    extern bool deletePrompt;
    extern bool autoUpdate;
    extern bool gayMode;
    extern bool usbAck;

    void setConfig();
    void parseConfig();
}