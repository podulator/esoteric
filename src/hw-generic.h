#ifndef _HWGENERIC_
#define _HWGENERIC_

#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>

#include "hw-ihardware.h"
#include "constants.h"

class HwGeneric : IHardware {
    private:

        IClock * clock_;
        ISoundcard * soundcard_;
        ICpu * cpu_;
        IPower * power_;
        ILed * led_;
        IHdmi * hdmi_;

    public:
        HwGeneric();
        ~HwGeneric();

        IClock * Clock() { return this->clock_; }
        ISoundcard * Soundcard() { return this->soundcard_; }
        ICpu * Cpu() { return this->cpu_; }
        IPower * Power() { return this->power_; }
        ILed * Led() { return this->led_; }
        IHdmi * Hdmi() { return this->hdmi_; }

        int getBacklightLevel();
        int setBacklightLevel(int val);

        bool getKeepAspectRatio();
        bool setKeepAspectRatio(bool val);

        std::string getDeviceType();

        bool setScreenState(const bool &enable);
};

#endif