#include <string>
#include <DCBTable.h>

#ifndef SIGNALDEF_H
#define SIGNALDEF_H


class IParser {
    virtual ~IParser() = default;
    virtual void loadFile(const std::string pathname) {};
    virtual void createEntries(DCBTable table) {};
};

#endif