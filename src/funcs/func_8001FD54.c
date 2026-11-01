#include "common.h"

typedef struct {
    u8 pad0[4];
    s32 flags;
    u8 pad8[4];
    s32 x;
    s32 y;
    s32 z;
} Obj1FD54;

typedef struct {
    Obj1FD54 *obj;
    u8 pad4[0x14];
} Ent1FD54;

typedef struct {
    u8 pad0[0xC];
    s32 state;
    s32 pos[3];
    u8 pad1C[0x28];
    s32 vel[3];
} Me1FD54;

Ent1FD54 *func_8001A6F8(s32 *cnt);
void func_8001DC58(Me1FD54 *, s32);
u32 func_80011B48(void);
void func_80032FF4(s32 *, s32 *);
void func_8001EB4C(Me1FD54 *);

void func_8001FD54(Me1FD54 *me) {
    s32 d[3];
    s32 cnt;
    Ent1FD54 *e;
    Obj1FD54 *o;
    u32 r;

    if (me->state != 1) {
        e = func_8001A6F8(&cnt);
        while (--cnt != -1) {
            o = e->obj;
            if (o->flags & 1) {
                d[0] = (o->x - me->pos[0]) >> 16;
                d[2] = (o->z - me->pos[2]) >> 16;
                if (d[0] * d[0] + d[2] * d[2] < 250000) {
                    d[1] = (o->y - me->pos[1]) >> 16;
                    if (abs(d[1]) < 100) {
                        func_8001DC58(me, 1);
                        r = func_80011B48();
                        me->vel[0] = (r % 3 - 1) << 16;
                        r >>= 2;
                        me->vel[1] = -0xC0000 - ((r & 3) << 16);
                        r >>= 2;
                        me->vel[2] = (r % 3 - 1) << 16;
                        break;
                    }
                }
            }
            e++;
        }
    }
    func_80032FF4(me->pos, me->vel);
    func_8001EB4C(me);
}
