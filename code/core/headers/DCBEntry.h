#include <SignalDef.h>
#include <string>
#include <vector>

#ifndef DCBENTRY_H
#define DCBENTRY_H

struct DCBEntry {
    uint32_t id;
    std::string name;
    std::vector<SignalDef> signalDefList;
};

#endif