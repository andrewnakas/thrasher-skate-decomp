#include "common.h"

typedef struct {
    u8 pad0[0x608];
    s16 f608;
    u8 pad60A[0x64C - 0x60A];
    s32 pos0[3];
    u8 pad658[0x670 - 0x658];
    u8 f670[0x694 - 0x670];
    s16 f694;
    u8 pad696[0x6D8 - 0x696];
    s32 pos1[3];
} Obj_80024B14;

typedef struct {
    s32 vx;
    s32 vy;
    s32 vz;
    s32 pad;
} Vec_80024B14;

extern void func_80024958(s32 *c, u8 *seg, s32 *out);
extern u8 ***func_8002E8E0(s32 *, u8 *, s32, s32);
extern s32 D_8008A2BC;
extern s32 D_8008A30C;
extern s32 D_8008AF6C[2];
extern s32 D_8008AF74[2];

void func_80024B14(Obj_80024B14 *arg0) {
    Vec_80024B14 d;
    Vec_80024B14 v;
    u8 ***list;
    u8 **e;
    u32 lim;

    lim = 10000;
    if (D_8008AF74[D_8008A2BC] == 0 && D_8008AF6C[D_8008A2BC] == 0) {
        list = func_8002E8E0(arg0->pos0, arg0->f670, 0xC80000, 0);
        e = *list++;
        while (e != NULL) {
            func_80024958(arg0->pos0, *e, &v.vx);
            d.vx = (v.vx - arg0->pos0[0]) >> 16;
            d.vy = (v.vy - arg0->pos0[1]) >> 16;
            d.vz = (v.vz - arg0->pos0[2]) >> 16;
            if ((u32) (d.vx * d.vx + d.vy * d.vy + d.vz * d.vz) < lim) {
                arg0->pos0[0] = v.vx;
                arg0->pos0[1] = v.vy + D_8008A30C;
                arg0->pos0[2] = v.vz;
                arg0->f608 = 0;
                D_8008AF74[D_8008A2BC] = 1;
                D_8008AF6C[D_8008A2BC] = 1;
            }
            func_80024958(arg0->pos1, *e, &v.vx);
            d.vx = (v.vx - arg0->pos1[0]) >> 16;
            d.vy = (v.vy - arg0->pos1[1]) >> 16;
            d.vz = (v.vz - arg0->pos1[2]) >> 16;
            if ((u32) (d.vx * d.vx + d.vy * d.vy + d.vz * d.vz) < lim) {
                arg0->pos1[0] = v.vx;
                arg0->pos1[1] = v.vy + D_8008A30C;
                arg0->pos1[2] = v.vz;
                arg0->f694 = 0;
                D_8008AF74[D_8008A2BC] = 1;
                D_8008AF6C[D_8008A2BC] = 1;
            }
            e = *list++;
        }
    }
}
