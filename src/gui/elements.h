#pragma once

#include "gui/base.h"

#include "gui/elements/button.h"
#include "gui/elements/text.h"

typedef CalcElementBase* CalcElement;

#define CALC_ELEMENT_PTR(ptr) ((CalcElement)&ptr)
