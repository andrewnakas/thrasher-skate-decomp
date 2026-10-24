#include "common.h"

typedef struct {
    s32 f0;
    u16 f4;
    u16 f6;
    s32 f8;
    s32 fC;
} Rec;

s32 func_8001B3F4(s32);
void func_8001C2B8(s32, s32, s32, s32, s32);

s32 func_8001B40C(Rec *rec, s32 count) {
    s32 i;
    s32 j;
    s32 r;

    for (i = 0; i < count; i++) {
        r = func_8001B3F4(rec->f6);
        if (rec->f8 != 0) {
            *(u16 *)rec->f8 = (u16)r;
        }
        for (j = 0; j < rec->f6; j++) {
            func_8001C2B8(rec->f0, (u16)(rec->f4 + j), (u16)(r + j), rec->fC, 0);
        }
        rec++;
    }
    return 0;
}
