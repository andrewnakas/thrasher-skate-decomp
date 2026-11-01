#include "common.h"

typedef struct {
    u8 flags;           /* 0x00 */
    u8 id;              /* 0x01 */
    s16 p0[3];          /* 0x02 */
    s16 p1[3];          /* 0x08 */
    u16 len;            /* 0x0E */
    s32 dir[3];         /* 0x10 */
} Seg_8002FFDC;

extern u16 func_80032D3C(s32);
extern s32 func_80032C54(s32, s32);

void func_8002FFDC(Seg_8002FFDC *s, s32 id, u16 *a, u16 *b, s32 side) {
    s32 dx;
    s32 dy;
    s32 dz;

    s->flags = 0;
    s->id = id;
    s->p0[0] = a[0];
    s->p0[1] = a[1];
    s->p0[2] = a[2];
    s->p1[0] = b[0];
    s->p1[1] = b[1];
    dx = s->p1[0] - s->p0[0];
    s->p1[2] = b[2];
    dy = s->p1[1] - s->p0[1];
    dz = s->p1[2] - s->p0[2];
    s->len = func_80032D3C(dx * dx + dy * dy + dz * dz);
    s->dir[0] = func_80032C54(dx << 16, s->len << 16);
    s->dir[1] = func_80032C54(dy << 16, s->len << 16);
    s->dir[2] = func_80032C54(dz << 16, s->len << 16);
    if (side > 0) {
        s->flags |= 1;
    } else if (side < 0) {
        s->flags |= 2;
    }
}
