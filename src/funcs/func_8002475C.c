#include "common.h"

typedef struct {
    s32 x, y, z;
} Vec_8002475C;

typedef struct {
    s16 active;
    s16 timer;
    u8 pad4[0x40];
    Vec_8002475C pos;
    Vec_8002475C prev;
    u8 pad5C[0xC];
    Vec_8002475C dir;
    u8 pad74[0x18];
} Part_8002475C;

typedef struct {
    s32 count;
    Part_8002475C parts[34];
    u8 pad[0x80];
    Vec_8002475C home;
    u8 pad1328[4];
    s32 reset;
} Body_8002475C;

typedef struct {
    u8 pad0[0x18];
    s16 a, b, c, d;
} Ctl_8002475C;

extern s32 D_8008A2BC;
extern s32 D_8008AF6C[2];

extern void func_80012238(Ctl_8002475C *);
extern void func_80023ECC(Body_8002475C *, Ctl_8002475C *);
extern void func_800331FC(Vec_8002475C *, s32);
extern void func_80024720(Body_8002475C *);
extern void func_80025004(Body_8002475C *, Ctl_8002475C *);
extern void func_80024D6C(Body_8002475C *, Ctl_8002475C *);
extern void func_80025544(Body_8002475C *, Ctl_8002475C *);

void func_8002475C(Body_8002475C *b, Ctl_8002475C *c, s32 unused, Vec_8002475C *dir) {
    s32 i;

    func_80012238(c);
    func_80023ECC(b, c);
    for (i = 0; i < b->count; i++) {
        b->parts[i].dir.x = dir->x;
        b->parts[i].dir.y = dir->y;
        b->parts[i].dir.z = dir->z;
        func_800331FC(&b->parts[i].dir, 0x8000);
        b->parts[i].timer = 0;
        b->parts[i].active = 1;
        b->parts[i].prev.x = b->parts[i].pos.x;
        b->parts[i].prev.y = b->parts[i].pos.y;
        b->parts[i].prev.z = b->parts[i].pos.z;
    }
    func_80024720(b);
    b->home.x = b->parts[0].pos.x;
    b->home.y = b->parts[0].pos.y;
    b->home.z = b->parts[0].pos.z;
    c->b = 0;
    c->c = 0;
    c->d = 0;
    c->a = 0;
    b->reset = 1;
    func_80025004(b, c);
    func_80024D6C(b, c);
    func_80025544(b, c);
    D_8008AF6C[D_8008A2BC] = 0;
}
