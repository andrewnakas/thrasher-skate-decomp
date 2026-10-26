#include "common.h"

extern s32 D_8008B120;
extern u16 *D_8008B114;

s32 func_80035810(s32 arg0) {
    u16 *p;
    u16 v;

    v = (u16)arg0;
    switch (D_8008B120) {
    case 1:
        p = D_8008B114;
        *p = v;
        D_8008B114 = p + 1;
        break;
    case 2:
        p = D_8008B114;
        v = *p;
        D_8008B114 = p + 1;
        break;
    }
    return v;
}
