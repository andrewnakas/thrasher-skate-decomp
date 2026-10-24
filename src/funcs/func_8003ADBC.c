#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect_8003ADBC;

extern void func_8003AD7C(Rect_8003ADBC *r, u8 a, u8 b, u8 c, s32 d);

void func_8003ADBC(u8 a, u8 b, u8 c, s32 d) {
    Rect_8003ADBC r;

    r.w = 0x400;
    r.h = 0x200;
    r.x = 0;
    r.y = 0;
    func_8003AD7C(&r, a, b, c, d);
}
