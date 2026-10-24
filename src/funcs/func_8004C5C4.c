#include "common.h"

typedef struct {
    u8 pad0[8];
    s32 unk8;
} Ent_8004C5C4;

typedef struct Ent2_8004C5C4 {
    u8 unk0;
    u8 pad1[7];
    struct Ent2_8004C5C4 *unk8;
} Ent2_8004C5C4;

extern u8 D_8008B408[4];
extern Ent2_8004C5C4 *D_8008B424;
extern s32 D_8008B428;
s32 func_80051574(s32, s32 *);
void func_80051728(s32);

s32 func_8004C5C4(u8 id) {
    Ent_8004C5C4 *e;
    Ent2_8004C5C4 *p;
    s32 t;

    e = &((Ent_8004C5C4 *) D_8008B408)[id];
    func_80051574(e->unk8, &t);
    if (t != 1) {
        func_80051728(e->unk8);
        p = D_8008B424;
        D_8008B428 = 1;
        if (p != 0) {
            do {
                p->unk0 = 0xFF;
                p = p->unk8;
            } while (p != 0);
        }
        D_8008B424 = 0;
        D_8008B428 = 0;
    }
    return 0;
}
