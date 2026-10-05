#include <string>
#include <DCBTable.h>

#ifndef IPARSER_H
#define IPARSER_H


class IParser {
    public:
        virtual ~IParser() = default;
        virtual void loadFile(const std::string pathname) {};
        virtual void createEntries(DCBTable& table) {};
};

#endif