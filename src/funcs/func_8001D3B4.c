#include "common.h"

extern s32 D_8008AEA8;
extern s32 D_800928C4[];

void func_8001D3B4(s32 key, s32 value) {
    s32 *p;
    s32 *end;

    for (p = D_800928C4; p < (s32 *)D_8008AEA8; p += 2) {
        if (key == p[0]) {
            if (value != p[1]) {
                p[1] = value;
            }
            return;
        }
    }
    end = (s32 *)D_8008AEA8;
    end[0] = key;
    end[1] = value;
    D_8008AEA8 = (s32)(end + 2);
}
