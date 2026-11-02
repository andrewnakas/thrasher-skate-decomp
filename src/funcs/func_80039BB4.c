#include "common.h"

typedef struct {
    s16 x, y, w, h;
} Rect_80039BB4;

typedef struct {
    u32 addr : 24;
    u32 len : 8;
} PTag_80039BB4;

typedef struct {
    u32 tag;
    u32 code[2];
} DrArea_80039BB4;

void func_8005A794(DrArea_80039BB4 *, Rect_80039BB4 *);
extern u16 *D_80082430[];
extern u32 *D_8008B1A0;
/* D_8008B3AC accessed as D_8008B3B0[-1] for the game's unsplit lui/lw */
extern DrArea_80039BB4 *D_8008B3B0[2];

void func_80039BB4(u16 x0, u16 y0, u16 x1, u16 y1) {
    DrArea_80039BB4 *p;
    Rect_80039BB4 r;
    u32 *ot;
    u32 t;

    p = D_8008B3B0[-1];
    if (p != NULL) {
        {
        s16 c;
        t = x0;
        c = x0;
        if (t < 0x200) {
            if ((s32) t <= 0) {
                goto zx0;
            }
        }
        if (t > 0x200) {
            c = 0x200;
        }
        if (0) {
        zx0:
            c = 0;
        }
        x0 = c;
        }
        t = x1;
        if (t < 0x200) {
            if ((s32) t <= 0) {
                goto zx1;
            }
        }
        if (t > 0x200) {
            x1 = 0x200;
        }
        if (0) {
        zx1:
            x1 = 0;
        }
        t = y0;
        if (t < 0x1E0) {
            if ((s32) t <= 0) {
                goto zy0;
            }
        }
        if (t > 0x1E0) {
            y0 = 0x1E0;
        }
        if (0) {
        zy0:
            y0 = 0;
        }
        t = y1;
        if (t < 0x1E0) {
            if ((s32) t <= 0) {
                goto zy1;
            }
        }
        if (t > 0x1E0) {
            y1 = 0x1E0;
        }
        if (0) {
        zy1:
            y1 = 0;
        }
        r.x = D_80082430[0][0] + x0;
        r.y = D_80082430[0][1] + y0;
        r.w = x1 - x0;
        r.h = y1 - y0;
        func_8005A794(p, &r);
        ot = D_8008B1A0;
        D_8008B1A0 = ot - 1;
        ((PTag_80039BB4 *) p)->addr = ((PTag_80039BB4 *) ot)->addr;
        ((PTag_80039BB4 *) ot)->addr = (u32) p;
        p++;
        *(&D_8008B3B0[0] - 1) = p;
    }
}
