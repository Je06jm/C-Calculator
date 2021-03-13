#pragma once

#include "types.h"
#include "gui/elements.h"

#ifdef _WIN32

#include <windows.h>

typedef struct {
    HWND hWnd;
    HINSTANCE hInstance;
    int nCmdShow;
} CalcPlatformWindow;

struct __CalcDrawStruct{
    HWND hWnd;
    PAINTSTRUCT ps;
    HDC hdc;
};

#else

typedef struct {
    
} CalcPlatformWindow;

struct __CalcDrawStruct{
    
};

#endif

typedef struct __CalcDrawStruct* CalcDrawStruct;

struct __CalcWindow {
    CalcPlatformWindow platform;

    char* title;
    int width, height;


    CalcElement* elements;
    unsigned int count;
};

typedef struct __CalcWindow* CalcWindow;

CalcWindow CalcNewWindowObject();
bool CalcCreateWindow(CalcWindow cw);
void CalcDestroyWindow(CalcWindow cw);
int CalcWindowLoop(CalcWindow cw);

void CalcWindowAddElement(CalcWindow cw, CalcElement ce);
