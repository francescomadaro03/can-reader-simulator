#include <cinttypes>

#ifndef TRANSLATEDRAW_H
#define TRANSLATEDRAW_H

struct TranslatedRawMessage {
    double timestamp;
    uint32_t id;
    char* rawData;

};

#endif