#include <DCBEntry.h>
#include <unordered_map>

#ifndef SIGNALDEF_H
#define SIGNALDEF_H
struct DCBTable {
    std::unordered_map<uint32_t, DCBEntry> DCBTableData;
};

#endif