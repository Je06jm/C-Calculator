#include <windows.h>
#include <tchar.h>

#include <stdio.h>
#include <math.h>

#include "gui/window.h"

#define CELLS_X 4
#define CELLS_Y 6.4

#define PI 3.14159265358979323846

#define MATH_OP(op)\
    totalValue = lastValue;\
    lastValue = 0.0;\
    operation = op;\
    place = 0;\
    posSign = TRUE;\
    updateText()

char txtNum[64];
char operation = ' ';

long double totalValue = 0.0;
long double lastValue = 0.0;
int place = 0;
bool posSign = TRUE;

typedef struct {
    CalcButton btn;
    int value;
} ValueButton;

void updateText() {
    sprintf(txtNum, "%f", lastValue);
}

bool buttonPowClick(CalcButton* button) {
    MATH_OP('^');

    return TRUE;
}

bool buttonClearClick(CalcButton* button) {
    totalValue = 0.0;
    lastValue = 0.0;
    operation = ' ';
    place = 0;
    posSign = TRUE;

    updateText();

    return TRUE;
}

bool buttonPiClick(CalcButton* button) {
    lastValue = PI;

    updateText();

    return TRUE;
}

bool buttonDivClick(CalcButton* button) {
    MATH_OP('/');

    return TRUE;
}

bool buttonMulClick(CalcButton* button) {
    MATH_OP('*');

    return TRUE;
}

bool buttonSubClick(CalcButton* button) {
    MATH_OP('-');

    return TRUE;
}

bool buttonAddClick(CalcButton* button) {
    MATH_OP('+');

    return TRUE;
}

bool buttonEqualsClick(CalcButton* button) {
    switch(operation) {
        case '+':
            lastValue = totalValue + lastValue;
        break;
        case '-':
            lastValue = totalValue - lastValue;
        break;
        case '*':
            lastValue = totalValue * lastValue;
        break;
        case '/':
            lastValue = totalValue / lastValue;
        break;
        case '^':
            lastValue = pow(totalValue, lastValue);
        break;
        default:
        break;
    }

    operation = ' ';
    place = 0;
    posSign = TRUE;
    updateText();

    return TRUE;
}

bool buttonSignClick(CalcButton* button) {
    lastValue = -lastValue;

    if (posSign) {
        posSign = FALSE;
    } else {
        posSign = TRUE;
    }

    updateText();

    return TRUE;
}

bool buttonDotClick(CalcButton* button) {
    if (place == 0) {
        place = 1;
    }

    return FALSE;
}

bool valButtonClick(CalcButton* button) {
    ValueButton* btn = (ValueButton*)button;

    if (place == 0) {
        lastValue *= 10.0;
        if (!posSign) {
            lastValue -= (double)btn->value;
        } else {
            lastValue += (double)btn->value;
        }
    } else {
        if (!posSign) {
            lastValue -= (double)btn->value / pow(10.0, (double)place);
        } else {
            lastValue += (double)btn->value / pow(10.0, (double)place);
        }
        place += 1;
    }

    updateText();

    return TRUE;
}

#define CALC_BUTTON(txt, x, y, cellX, cellY) {\
    CALC_NEW_ELEMENT(CALC_ELEMENT_BUTTON),\
    txt,\
    x/(float)cellX, y/(float)cellY,\
    1.0/cellX, 1.0/cellY\
}

#define VALUE_BUTTON(txt, val, x, y, cellX, cellY) {{\
    CALC_NEW_ELEMENT(CALC_ELEMENT_BUTTON),\
    txt,\
    x/(float)cellX, y/(float)cellY,\
    1.0/cellX, 1.0/cellY,\
    valButtonClick},\
    val\
}


int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
) {
    CalcWindow cw = CalcNewWindowObject();
    cw->platform.hInstance = hInstance;
    cw->platform.nCmdShow = nCmdShow;

    cw->title = "Calculator";
    cw->width = 500;
    cw->height = 500;

    updateText();
    CalcText txt = {CALC_NEW_ELEMENT(CALC_ELEMENT_TEXT)};
    txt.text = txtNum;
    txt.x = 0.0f;
    txt.y = 0.0f;

    ValueButton vb7 = VALUE_BUTTON("7", 7, 0, 2, CELLS_X, CELLS_Y);
    ValueButton vb8 = VALUE_BUTTON("8", 8, 1, 2, CELLS_X, CELLS_Y);
    ValueButton vb9 = VALUE_BUTTON("9", 9, 2, 2, CELLS_X, CELLS_Y);

    ValueButton vb4 = VALUE_BUTTON("4", 4, 0, 3, CELLS_X, CELLS_Y);
    ValueButton vb5 = VALUE_BUTTON("5", 5, 1, 3, CELLS_X, CELLS_Y);
    ValueButton vb6 = VALUE_BUTTON("6", 6, 2, 3, CELLS_X, CELLS_Y);

    ValueButton vb1 = VALUE_BUTTON("1", 1, 0, 4, CELLS_X, CELLS_Y);
    ValueButton vb2 = VALUE_BUTTON("2", 2, 1, 4, CELLS_X, CELLS_Y);
    ValueButton vb3 = VALUE_BUTTON("3", 3, 2, 4, CELLS_X, CELLS_Y);

    ValueButton vb0 = VALUE_BUTTON("0", 0, 0, 5, CELLS_X, CELLS_Y);
    CalcButton vbP = CALC_BUTTON(".", 1, 5, CELLS_X, CELLS_Y);
    CalcButton vbS = CALC_BUTTON("+/-", 2, 5, CELLS_X, CELLS_Y);

    CalcButton vbPow = CALC_BUTTON("^", 0, 1, CELLS_X, CELLS_Y);
    CalcButton vbCle = CALC_BUTTON("C", 1, 1, CELLS_X, CELLS_Y);
    CalcButton vbPI = CALC_BUTTON("PI", 2, 1, CELLS_X, CELLS_Y);
    
    CalcButton vbDiv = CALC_BUTTON("/", 3, 1, CELLS_X, CELLS_Y);
    CalcButton vbMul = CALC_BUTTON("*", 3, 2, CELLS_X, CELLS_Y);
    CalcButton vbSub = CALC_BUTTON("-", 3, 3, CELLS_X, CELLS_Y);
    CalcButton vbAdd = CALC_BUTTON("+", 3, 4, CELLS_X, CELLS_Y);

    CalcButton vbEqu = CALC_BUTTON("=", 3, 5, CELLS_X, CELLS_Y);

    vbP.onRelease = buttonDotClick;
    vbS.onRelease = buttonSignClick;

    vbPow.onRelease = buttonPowClick;
    vbCle.onRelease = buttonClearClick;
    vbPI.onRelease = buttonPiClick;

    vbDiv.onRelease = buttonDivClick;
    vbMul.onRelease = buttonMulClick;
    vbSub.onRelease = buttonSubClick;
    vbAdd.onRelease = buttonAddClick;

    vbEqu.onRelease = buttonEqualsClick;

    CalcWindowAddElement(cw, CALC_ELEMENT_PTR(txt));

    CalcWindowAddElement(cw, CALC_ELEMENT_PTR(vb7));
    CalcWindowAddElement(cw, CALC_ELEMENT_PTR(vb8));
    CalcWindowAddElement(cw, CALC_ELEMENT_PTR(vb9));

    CalcWindowAddElement(cw, CALC_ELEMENT_PTR(vb4));
    CalcWindowAddElement(cw, CALC_ELEMENT_PTR(vb5));
    CalcWindowAddElement(cw, CALC_ELEMENT_PTR(vb6));

    CalcWindowAddElement(cw, CALC_ELEMENT_PTR(vb1));
    CalcWindowAddElement(cw, CALC_ELEMENT_PTR(vb2));
    CalcWindowAddElement(cw, CALC_ELEMENT_PTR(vb3));

    CalcWindowAddElement(cw, CALC_ELEMENT_PTR(vb0));
    CalcWindowAddElement(cw, CALC_ELEMENT_PTR(vbP));
    CalcWindowAddElement(cw, CALC_ELEMENT_PTR(vbS));

    CalcWindowAddElement(cw, CALC_ELEMENT_PTR(vbPow));
    CalcWindowAddElement(cw, CALC_ELEMENT_PTR(vbCle));
    CalcWindowAddElement(cw, CALC_ELEMENT_PTR(vbPI));

    CalcWindowAddElement(cw, CALC_ELEMENT_PTR(vbDiv));
    CalcWindowAddElement(cw, CALC_ELEMENT_PTR(vbMul));
    CalcWindowAddElement(cw, CALC_ELEMENT_PTR(vbSub));
    CalcWindowAddElement(cw, CALC_ELEMENT_PTR(vbAdd));

    CalcWindowAddElement(cw, CALC_ELEMENT_PTR(vbEqu));

    if (!CalcCreateWindow(cw)) {
        return EXIT_FAILURE;
    }


    int result = CalcWindowLoop(cw);

    CalcDestroyWindow(cw);
    return result;
}
