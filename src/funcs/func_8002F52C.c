#include "common.h"

extern u8 D_8006F890[];

u8 *func_8002E8C0(u16);

typedef struct {
    s32 vx, vy, vz, pad;
} Vec4;

typedef struct {
    s16 vx, vy, vz, pad;
} SVec;

typedef struct {
    u16 id;
    u8 pad02[0x2E];
    s16 c30;
    s16 c32;
    s16 c34;
    s16 r36;
    s16 r38;
    s16 r3A;
    u8 pad3C[8];
    SVec pts[1];
} S_8002F52C;

void func_8002F52C(S_8002F52C *s) {
    Vec4 mn;
    Vec4 mx;
    s32 n;
    s32 i;
    s32 v;

    n = *(s32 *) (D_8006F890 + *func_8002E8C0(s->id) * 8);
    mn.vx = mn.vy = mn.vz = 0xFFFF;
    mx.vx = mx.vy = mx.vz = 0xFFFF0001;
    for (i = 0; i < n; i++) {
        v = s->pts[i].vx; if (mn.vx < v) v = mn.vx; mn.vx = v;
        v = s->pts[i].vy; if (mn.vy < v) v = mn.vy; mn.vy = v;
        v = s->pts[i].vz; if (mn.vz < v) v = mn.vz; mn.vz = v;
        v = s->pts[i].vx; if (v < mx.vx) v = mx.vx; mx.vx = v;
        v = s->pts[i].vy; if (v < mx.vy) v = mx.vy; mx.vy = v;
        v = s->pts[i].vz; if (v < mx.vz) v = mx.vz; mx.vz = v;
    }
    mn.vx--;
    mn.vy--;
    mn.vz--;
    mx.vx++;
    mx.vy++;
    mx.vz++;
    s->c30 = (mx.vx + mn.vx) >> 1;
    s->c32 = (mx.vy + mn.vy) >> 1;
    s->c34 = (mx.vz + mn.vz) >> 1;
    s->r36 = (u16) mx.vx - s->c30;
    s->r38 = (u16) mx.vy - s->c32;
    s->r3A = (u16) mx.vz - s->c34;
}
