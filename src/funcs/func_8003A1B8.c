#include "common.h"

typedef struct {
    u32 addr : 24;
    u32 len : 8;
} PTag_8003A1B8;

typedef struct {
    s16 x, y, w, h;
} Rect_8003A1B8;

typedef struct {
    Rect_8003A1B8 r;
    u16 lo;
    u16 hi;
} Load_8003A1B8;

typedef struct {
    PTag_8003A1B8 tag;
    u8 pad4[0xC];
    u32 data;
    u8 pad14[0x30];
} DrLoad_8003A1B8;

extern Rect_8003A1B8 D_800A8404[];
extern void SetDrawLoad(DrLoad_8003A1B8 *p, Rect_8003A1B8 *r);

DrLoad_8003A1B8 *func_8003A1B8(PTag_8003A1B8 *ot, DrLoad_8003A1B8 *p, u16 *id, s32 mode, u32 c0, u32 c1) {
    Load_8003A1B8 l;
    Rect_8003A1B8 *r;

    mode &= 0xFF;
    if (mode == 2) {
        r = &D_800A8404[*id >> 8];
        l.r.x = r->x;
        l.r.y = r->y;
        l.r.w = mode;
        l.r.h = r->h;
        l.lo = ((c1 >> 6) & 3) | ((c1 >> 9) & 0x60) | ((c1 >> 12) & 0xC00);
        l.hi = ((c0 >> 6) & 3) | ((c0 >> 9) & 0x60) | ((c0 >> 12) & 0xC00);
        SetDrawLoad(p, &l.r);
        p->data = l.lo | (l.hi << 16);
        p->tag.addr = ot->addr;
        ot->addr = (u32)p;
        p++;
    }
    return p;
}
