#include "common.h"

typedef struct {
    u8 pad0[0x114];
    u8 mode;
    u8 pad115[3];
    s32 x;
    s32 y;
    s32 z;
    u16 a;
    u16 b;
    u16 c;
} Cam_80013D98;

typedef struct {
    u8 pad0[4];
    u32 flags;
    u8 pad8[0x18];
    s32 sx;
    s32 sy;
    s32 sz;
    u8 pad2C[0xC];
    Cam_80013D98 *cam;
} Obj_80013D98;

extern s32 func_80032C28(s32, s32);
extern void func_80033428(s32 *, s16);
extern s16 D_80089F50;
extern s32 D_80089F54;
extern s32 D_8008ACD4[1];
extern s32 D_8008ACD8[1];
extern s32 D_8008ACDC[1];
extern u16 D_8008ACE0[1];
extern u16 D_8008ACE2[1];
extern u16 D_8008ACE4[1];
extern s16 D_8008ACE6;

s32 *func_80013D98(Obj_80013D98 *o) {
    if (o->cam->mode != 2) {
        return NULL;
    }
    D_8008ACD4[0] = o->cam->x;
    D_8008ACD8[0] = o->cam->y;
    D_8008ACDC[0] = o->cam->z;
    D_8008ACE6 = 0;
    if (D_80089F54 == 0) {
        func_80033428(D_8008ACD4, D_80089F50);
    } else {
        func_80033428(D_8008ACD4, -D_80089F50);
    }
    if (o->flags & 8) {
        D_8008ACD4[0] = func_80032C28(D_8008ACD4[0], o->sx);
        D_8008ACD8[0] = func_80032C28(D_8008ACD8[0], o->sy);
        D_8008ACDC[0] = func_80032C28(D_8008ACDC[0], o->sz);
    }
    D_8008ACE0[0] = o->cam->a;
    D_8008ACE2[0] = o->cam->b;
    D_8008ACE4[0] = o->cam->c;
    return D_8008ACD4;
}
