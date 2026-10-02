#include <SignalDef.h>
#include <string>
#include <vector>

#ifndef SIGNALDEF_H
#define SIGNALDEF_H

struct DCBEntry {
    uint32_t id;
    std::string name;
    std::vector<SignalDef> signalDefList;
};

#endif