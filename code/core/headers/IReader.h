#include "TranslatedRawMessage.h"
#include <string>
#include <string_view>

#ifndef IREADER_H
#define IREADER_H


class IReader {
    public:
        ~IReader() = default;
        virtual int ComputeRawTranslationAndSend(std::string_view rawMessage) = 0;
        virtual bool checkSupportedInterfaces(std::string interface) = 0;
};


#endif