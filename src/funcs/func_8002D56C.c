#include "common.h"

typedef struct {
    s16 x, y, z;
} SVec_8002D56C;

typedef struct {
    u8 pad0[4];
    s32 x;
    u8 pad8[4];
    s32 z;
    s32 w;
    u8 pad14[4];
    s32 d;
} Box_8002D56C;

typedef struct {
    u8 pad0[0x2C];
    Box_8002D56C *box;
} Obj_8002D56C;

typedef struct {
    s32 x;
    s32 z;
    s32 hw;
    s32 hd;
} Rect_8002D56C;

extern void func_8002D734(SVec_8002D56C *, SVec_8002D56C *, SVec_8002D56C *, s32);
extern void func_8002D81C(SVec_8002D56C *, SVec_8002D56C *, SVec_8002D56C *, s32);

s32 func_8002D56C(Obj_8002D56C *o, SVec_8002D56C *from, SVec_8002D56C *to) {
    SVec_8002D56C a;
    SVec_8002D56C b;
    SVec_8002D56C hit;
    Rect_8002D56C r;
    Box_8002D56C *bx;
    s32 ret;

    bx = o->box;
    a.x = from->x;
    a.y = from->y;
    a.z = from->z;
    b.x = to->x;
    b.y = to->y;
    b.z = to->z;
    r.x = bx->x;
    r.hw = bx->w >> 1;
    r.z = bx->z;
    r.hd = bx->d >> 1;
    ret = 0;
    if (to->x < r.x - r.hw) {
        func_8002D734(&a, &b, &hit, r.x - r.hw - 1);
    } else if (to->x > r.x + r.hw) {
        func_8002D734(&a, &b, &hit, r.x + r.hw + 1);
    } else {
        goto checkz;
    }
    ret = 1;
    if (hit.z >= r.z - r.hd && hit.z <= r.z + r.hd) {
        from->x = hit.x;
        from->y = hit.y;
        from->z = hit.z;
        return ret;
    }
checkz:
    if (to->z < r.z - r.hd) {
        func_8002D81C(&a, &b, &hit, r.z - r.hd - 1);
        ret = 1;
    } else if (to->z > r.z + r.hd) {
        func_8002D81C(&a, &b, &hit, r.z + r.hd + 1);
        ret = 1;
    }
    if (ret) {
        from->x = hit.x;
        from->y = hit.y;
        from->z = hit.z;
    }
    return ret;
}
