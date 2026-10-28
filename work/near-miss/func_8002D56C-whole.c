#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} V_8002D56C;

typedef struct {
    u8 pad00[4];
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
} Ctx_8002D56C;

void func_8002D734(V_8002D56C *, V_8002D56C *, V_8002D56C *, s32);
void func_8002D81C(V_8002D56C *, V_8002D56C *, V_8002D56C *, s32);

s32 func_8002D56C(u8 *e, V_8002D56C *delta, V_8002D56C *cur) {
    Ctx_8002D56C *c;
    V_8002D56C d;
    V_8002D56C u;
    V_8002D56C o;
    s32 lo;
    s32 hi;
    s32 mid;
    s32 half;
    s32 t;
    s32 r;

    c = *(Ctx_8002D56C **) (e + 0x2C);
    d = *delta;
    u = *cur;
    lo = c->f04;
    half = c->f10 >> 1;
    mid = c->f0C;
    hi = c->f18 >> 1;
    r = 0;
    t = lo - half;
    if (u.x < t) {
        func_8002D734(&d, &u, &o, t - 1);
        r = 1;
    } else {
        t = lo + half;
        if (t < u.x) {
            func_8002D734(&d, &u, &o, t + 1);
            r = 1;
        } else {
            goto axis_y;
        }
    }
    t = mid - hi;
    if (o.z >= t) {
        t = mid + hi;
        if (o.z <= t) {
            *cur = o;
            return r;
        }
    }
axis_y:
    t = mid - hi;
    if (u.y < t) {
        func_8002D81C(&d, &u, &o, t - 1);
        r = 1;
    } else {
        t = mid + hi;
        if (t < u.y) {
            func_8002D81C(&d, &u, &o, t + 1);
            r = 1;
        } else {
            goto done;
        }
    }
done:
    if (r != 0) {
        *cur = o;
    }
    return r;
}
