#include <SignalDef.h>
#include <string>
#include <vector>

#ifndef DCBENTRY_H
#define DCBENTRY_H

struct DCBEntry {
    uint32_t id;
    uint8_t dlc;
    std::string name;
    std::vector<SignalDef> signalDefList;
};

#endif