#pragma once

#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef char bool;

#define ZERO_MEM(v) (memset(&v, 0, sizeof(v)))
#define ZERO_MEM_S(v, s) (memset(v, 0, sizeof(struct s)))
