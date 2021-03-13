#pragma once

#include "gui/base.h"
#include "types.h"

typedef struct __CalcText CalcText;

typedef bool (*CalcTextEvent)(CalcText* text);

struct __CalcText {
    CALC_ELEMENT_BASE;

    char* text;
    float x, y;
};
