#include <DCBEntry.h>
#include <unordered_map>


struct DCBTable {
    std::unordered_map<uint32_t, DCBEntry> DCBTableData;
};