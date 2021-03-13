#ifdef _WIN32

#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>

#include "gui/window.h"
#include "gui/elements.h"

#define SCREEN_POS(pos, size) ((int)(pos*size))

char szWindowClass[] = "DesktopApp";

CalcWindow cWin;

LRESULT CALLBACK WndProc(
    _In_ HWND hWnd,
    _In_ UINT message,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
) {
    struct __CalcDrawStruct ds;
    ds.hWnd = hWnd;
    RECT rect;

    int width, height;

    CalcElement element;
    HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);

    switch(message) {
        case WM_COMMAND: {
            unsigned int index = LOWORD(wParam);

            if (index < cWin->count) {
                element = cWin->elements[index];

                switch(element->type) {
                    case CALC_ELEMENT_BUTTON: {
                        CalcButton* btn = (CalcButton*)element;
                        
                        if (btn->onRelease != NULL) {
                            if (btn->onRelease(btn)) {
                                RedrawWindow(
                                    hWnd,
                                    NULL,
                                    NULL,
                                    RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE
                                );
                            }
                        }
                    } break;
                }
            }
        } break;
        case WM_PAINT:
            GetWindowRect(ds.hWnd, &rect);
            width = rect.right - rect.left;
            height = rect.bottom - rect.top;

            ds.hdc = BeginPaint(ds.hWnd, &ds.ps);

            for (unsigned int i = 0; i < cWin->count; i++) {
                element = cWin->elements[i];

                switch(element->type) {
                    case CALC_ELEMENT_BUTTON: {
                        CalcButton* btn = (CalcButton*)element;

                        if (btn->base.platform.hWnd == NULL) {
                            btn->base.platform.hWnd = CreateWindow(
                                "BUTTON",
                                btn->text,
                                WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                SCREEN_POS(btn->x, width), SCREEN_POS(btn->y, height),
                                SCREEN_POS(btn->width, width), SCREEN_POS(btn->height, height),
                                hWnd,
                                (HMENU)btn->base.id,
                                hInstance,
                                NULL
                            );
                        } else {
                            SetWindowPos(
                                btn->base.platform.hWnd,
                                HWND_TOP,
                                SCREEN_POS(btn->x, width), SCREEN_POS(btn->y, height),
                                SCREEN_POS(btn->width, width), SCREEN_POS(btn->height, height),
                                0
                            );

                            SetWindowText(
                                btn->base.platform.hWnd,
                                btn->text
                            );
                        }
                    } break;
                    case CALC_ELEMENT_TEXT: {
                        CalcText* txt = (CalcText*)element;

                        TextOut(
                            ds.hdc,
                            SCREEN_POS(txt->x, width), SCREEN_POS(txt->y, height),
                            txt->text,
                            strlen(txt->text)
                        );
                    } break;
                    default: break;
                }
            }

            EndPaint(ds.hWnd, &ds.ps);
            break;
        
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
            break;
    }
    
    return 0;
}

CalcWindow CalcNewWindowObject() {
    CalcWindow cw = (CalcWindow)malloc(sizeof(struct __CalcWindow));
    ZERO_MEM_S(cw, __CalcWindow);

    return cw;
}

bool CalcCreateWindow(CalcWindow cw) {
    cWin = cw;
    char* title = cw->title;

    if (title == NULL) {
        title = "MISSING WINDOW TITLE";
    }

    WNDCLASSEX wcex = {sizeof(WNDCLASSEX)};
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = cw->platform.hInstance;
    wcex.hIcon = LoadIcon(cw->platform.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(cw->platform.hInstance, IDI_APPLICATION);

    
    if (!RegisterClassEx(&wcex)) {
        MessageBox(
            NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Desktop Application"),
            0
        );

        return FALSE;
    }

    cw->platform.hWnd = CreateWindowEx(
        0,
        szWindowClass,
        cw->title,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        cw->width, cw->height,
        NULL,
        NULL,
        cw->platform.hInstance,
        NULL
    );

    if (!cw->platform.hWnd) {
        MessageBox(
            NULL,
            _T("Call to CreateWindow failed!"),
            _T("Desktop Application"),
            0
        );

        return FALSE;
    }

    ShowWindow(cw->platform.hWnd, cw->platform.nCmdShow);
    UpdateWindow(cw->platform.hWnd);

    return TRUE;
}

void CalcDestroyWindow(CalcWindow cw) {
    if (cw->elements != NULL) {
        free(cw->elements);
    }
    free(cw);
}

int CalcWindowLoop(CalcWindow cw) {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

void CalcWindowAddElement(CalcWindow cw, CalcElement ce) {
    CalcElement* newList = (CalcElement*)malloc(sizeof(CalcElement*) * (cw->count + 1));
    
    if (cw->elements != NULL) {
        memcpy(newList, cw->elements, sizeof(CalcElement*) * cw->count);
        free(cw->elements);
    }

    newList[cw->count] = ce;
    ce->id = cw->count;

    cw->elements = newList;
    cw->count++;
}

#endif