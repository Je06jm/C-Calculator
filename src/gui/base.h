#pragma once

typedef enum CalcElementType {
    CALC_ELEMENT_BUTTON,
    CALC_ELEMENT_TEXT
} CalcElementType;

#ifdef _WIN32

#include <windows.h>

typedef struct {
    HWND hWnd;
} CalcElementPlatform;

#define CALC_NEW_ELEMENT(n) {n, NULL}

#else

typedef struct {

} CalcElementPlatform;

#define CALC_NEW_ELEMENT(n) {n}

#endif

typedef struct __CalcElementBase {
    CalcElementType type;
    CalcElementPlatform platform;
    unsigned int id;
} CalcElementBase;

#define CALC_ELEMENT_BASE CalcElementBase base
