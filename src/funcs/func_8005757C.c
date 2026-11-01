#include "common.h"

typedef struct {
    s8 type;
    u8 pad1;
    u16 status;
    s32 b4;
    s32 b8;
    u8 padC[4];
    union {
        struct {
            s32 w10;
            s32 w14;
        } w;
        struct {
            u16 h10;
            u16 h12;
            u16 h14;
            u16 h16;
        } h;
        struct {
            s8 x;
            u8 y;
            u8 z;
        } b;
    } u;
} PadRaw_5757C;

typedef struct {
    PadRaw_5757C *raw;
    s32 held;
    s32 edge;
    u16 unkC;
    u16 flags;
    s32 axis[4];
    s32 prev[4];
} Pad_5757C;

extern Pad_5757C D_800B2C7C[2];
extern u8 D_80089FA0[4];
s32 abs(s32);

s32 func_80032C28(s32, s32);
s32 func_80055D58(void);

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

u32 func_8005757C(void) {
    Pad_5757C *p;
    PadRaw_5757C *raw;
    u32 ret;
    u32 i;

    ret = 0;
    for (i = 0; i < 2; i++) {
        p = &D_800B2C7C[i];
        if (p->flags & 1) {
            if (!(p->raw->status & 1)) {
                ret |= 2;
                p->unkC = 0;
                p->flags &= ~1;
            }
        }
        if (!(p->flags & 1)) {
            raw = p->raw;
            if (!(raw->status & 1)) {
                p->held = raw->b4;
                p->edge = p->raw->b8;
                p->prev[0] = p->axis[0];
                p->prev[1] = p->axis[1];
                p->prev[2] = p->axis[2];
                p->prev[3] = p->axis[3];
                p->axis[0] = 0;
                p->axis[1] = 0;
                p->axis[2] = 0;
                p->axis[3] = 0;
                switch (p->raw->type) {
                case 1:
                    p->axis[0] = ((p->raw->u.h.h12 & ~0xFF) - 0x8000) * 2;
                    p->axis[1] = ((p->raw->u.w.w10 & 0xFF00) - 0x8000) * 2;
                    p->axis[2] = ((p->raw->u.h.h16 & ~0xFF) - 0x8000) * 2;
                    p->axis[3] = ((p->raw->u.w.w14 & 0xFF00) - 0x8000) * 2;
                    break;
                case 2:
                    p->axis[0] = MIN(MAX(func_80032C28(p->raw->u.b.x << 9, 0x20000), -0x10000), 0x10000) & ~0x1FF;
                    p->axis[1] = 0;
                    p->axis[2] = p->raw->u.b.y << 9;
                    p->axis[3] = p->raw->u.b.z << 9;
                    break;
                }
                if (D_80089FA0[-4] == 1 || func_80055D58() == 1) {
                    if (abs(p->axis[0]) > 0x8000) {
                        p->held |= (p->axis[0] < 0) ? 4 : 8;
                        if (abs(p->prev[0]) <= 0x8000) {
                            p->edge |= (p->axis[0] < 0) ? 4 : 8;
                        }
                    } else if (abs(p->prev[0]) > 0x8000) {
                        p->edge |= (p->prev[0] < 0) ? 4 : 8;
                    }
                    if (abs(p->axis[1]) > 0x8000) {
                        p->held |= (p->axis[1] < 0) ? 1 : 2;
                        if (abs(p->prev[1]) <= 0x8000) {
                            p->edge |= (p->axis[1] < 0) ? 1 : 2;
                        }
                    } else if (abs(p->prev[1]) > 0x8000) {
                        p->edge |= (p->prev[1] < 0) ? 1 : 2;
                    }
                }
            } else {
                ret |= 1;
                p->flags |= 1;
            }
        }
    }
    return ret;
}
