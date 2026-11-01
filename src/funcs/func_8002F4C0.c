#include "common.h"

typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} Plane;

s32 func_80032C54(s32, s32);

s32 func_8002F4C0(s32 x, s32 y, Plane *p) {
    if (p == NULL || p->b == 0) {
        return 0x27100000;
    }
    return func_80032C54(-(p->a * x + p->c * y + p->d), p->b);
}
