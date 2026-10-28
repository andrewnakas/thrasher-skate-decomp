#include "common.h"

extern u8 D_8006F890[];

u8 *func_8002E8C0(u16);

typedef struct {
    u8 pad00[0x30];
    s16 c30;
    s16 c32;
    s16 c34;
    s16 r36;
    s16 r38;
    s16 r3A;
} S_8002F52C;

void func_8002F52C(S_8002F52C *s) {
    u8 *p;
    s32 n;
    s32 i;
    s32 minx = 0xFFFF;
    s32 miny = 0xFFFF;
    s32 minz = 0xFFFF;
    s32 maxx = 0xFFFF0001;
    s32 maxy = 0xFFFF0001;
    s32 maxz = 0xFFFF0001;
    s16 v;

    p = func_8002E8C0(*(u16 *) s);
    n = *(s32 *) (*(u8 *) p * 8 + (s32) D_8006F890);
    for (i = 0; i < n; i++) {
        v = *(s16 *) ((u8 *) s + 0x44 + i * 8 + 0);
        if (minx < v) {
            v = minx;
        }
        minx = v;
        v = *(s16 *) ((u8 *) s + 0x44 + i * 8 + 2);
        if (miny < v) {
            v = miny;
        }
        miny = v;
        v = *(s16 *) ((u8 *) s + 0x44 + i * 8 + 4);
        if (minz < v) {
            v = minz;
        }
        minz = v;
        v = *(s16 *) ((u8 *) s + 0x44 + i * 8 + 0);
        if (v < maxx) {
            v = maxx;
        }
        maxx = v;
        v = *(s16 *) ((u8 *) s + 0x44 + i * 8 + 2);
        if (v < maxy) {
            v = maxy;
        }
        maxy = v;
        v = *(s16 *) ((u8 *) s + 0x44 + i * 8 + 4);
        if (v < maxz) {
            v = maxz;
        }
        maxz = v;
    }
    minx--;
    miny--;
    minz--;
    maxx++;
    maxy++;
    maxz++;
    s->c30 = (maxx + minx) >> 1;
    s->c32 = (maxy + miny) >> 1;
    s->c34 = (maxz + minz) >> 1;
    s->r36 = (u16) maxx - (u16) s->c30;
    s->r38 = (u16) maxy - (u16) s->c32;
    s->r3A = (u16) maxz - (u16) s->c34;
}
