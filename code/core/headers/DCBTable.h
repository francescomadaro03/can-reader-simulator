#include <DCBEntry.h>
#include <unordered_map>

#ifndef DCBTABLE_H
#define DCBTABLE_H
struct DCBTable {
    std::unordered_map<uint32_t, DCBEntry> DCBTableData;
};

#endif