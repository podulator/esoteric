
#include <string>
#include <vector>

#include "debug.h"
#include "utilities.h"

#include "hwfactory.h"
#include "ihardware.h"
#include "generic.h"
#include "gkd350h.h"
#include "linux.h"
#include "rg350.h"

IHardware* HwFactory::GetHardware(std::string device) {
    TRACE("enter : %s", device.c_str());
    if (0 == device.compare("gcw0")) {
        return (IHardware*)new HwGeneric();
    } else if (0 == device.compare("generic")) {
        return (IHardware*)new HwGeneric();
    } else if (0 == device.compare("gkd350h")) {
        return (IHardware*)new HwGkd350h();
    } else if (0 == device.compare("linux")) {
        return (IHardware*)new HwLinux();
    } else if (0 == device.compare("pg2")) {
        return (IHardware*)new HwGeneric();
    } else if (0 == device.compare("retrofw")) {
        return (IHardware*)new HwGeneric();
    } else if (0 == device.compare("rg350")) {
        return (IHardware*)new HwRg350();
    } else
        return (IHardware*)new HwGeneric();
}

std::vector<std::string> HwFactory::supportedDevices() {
    return std::vector<std::string>{
        "gcw0",
        "generic",
        "gkd350h",
        "linux",
        "pg2",
        "retrofw"
        "rg350"};
}

std::string HwFactory::readDeviceType() {
    std::string cmdLine = fileReader("/proc/cmdline");
    std::vector<std::string> cmdParts;
    std::string result = "generic";
    split(cmdParts, cmdLine, " ");
    for (std::vector<std::string>::iterator it = cmdParts.begin(); it != cmdParts.end(); it++) {
        std::string cmdPart = (*it);

        std::string::size_type pos = cmdPart.find("=");
        if (std::string::npos == pos) continue;
        std::string name = trim(cmdPart.substr(0, pos));
        std::string value = trim(cmdPart.substr(pos + 1, cmdPart.length()));
        if (0 == value.length()) continue;

        if (name == "hwvariant") {
            if (0 == value.compare("rg350")) {
                result = "rg350";
            } else if (0 == value.compare("v11_ddr2_256mb")) {
                result = "gcw0";
            } else if (0 == value.compare("v20_mddr_512mb")) {
                result = "pg2";
            }
            break;
        }
    }
    if (result == "generic") {
        // is it retro fw?
        if (fileExists("/etc/hostname")) {
            std::string host = fileReader("/etc/hostname");
            host = toLower(full_trim(host));
            if (0 == host.compare("retrofw")) {
                return "retrofw";
            }
        }
        // ok, is it open dingux?
        if (fileExists("/etc/issue")) {
            std::string issue = fileReader("/etc/issue");
            bool isDingux = false;
            if (!issue.empty()) {
                std::string lowerIssue = toLower(issue);
                std::vector<std::string> issueParts;
                split(issueParts, lowerIssue, " ");
                for (std::vector<std::string>::iterator it = issueParts.begin(); it != issueParts.end(); it++) {
                    TRACE("checking token : %s", (*it).c_str());
                    if (0 == (*it).compare("opendingux")) {
                        isDingux = true;
                        break;
                    }
                }
                if (!isDingux) {
                    result = "linux";
                }
            }
        }
    }
    return result;
}