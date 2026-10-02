#include <string>
#include <vector>
#include <cstdint> 
#ifndef SIGNALDEF_H
#define SIGNALDEF_H

enum class MultiplexType {
    Standard,
    Switch,
    Multiplexed
};

struct SignalDef{
    std::string name;
    uint8_t startingBit;
    uint8_t endingBit;
    MultiplexType muxType = MultiplexType::Standard;
    int muxValue = 0;
    bool endianess; // true means little endian, false means big endian
    bool isSigned;
    float weight;
    float scale;
    int min;
    int max;
    std::string unit;
    std::vector<std::string> nodes;



};

#endif