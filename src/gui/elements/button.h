#pragma once

#include "gui/base.h"
#include "types.h"

typedef struct __CalcButton CalcButton;

typedef bool (*CalcButtonEvent)(CalcButton* button);

struct __CalcButton {
    CALC_ELEMENT_BASE;

    char* text;
    float x, y;
    float width, height;

    CalcButtonEvent onRelease;
};
