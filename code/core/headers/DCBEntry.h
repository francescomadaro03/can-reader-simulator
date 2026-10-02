#include <SignalDef.h>
#include <string>
#include <vector>

struct DCBEntry {
    uint32_t id;
    std::string name;
    std::vector<SignalDef> signalDefList;
};