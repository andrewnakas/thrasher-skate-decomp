#include "common.h"

typedef struct {
    u8 pad0[8];
    s32 unk8;
} Ent_8004C2C8;

typedef struct Ent2_8004C2C8 {
    u8 unk0;
    u8 pad1[7];
    struct Ent2_8004C2C8 *unk8;
} Ent2_8004C2C8;

extern u8 D_8008B408[4];
extern Ent2_8004C2C8 *D_8008B424;
extern s32 D_8008B428;
extern char D_800107F8[];
extern char D_8008A950[];
void func_8005109C(s32);

void func_8004C2C8(u8 id) {
    Ent_8004C2C8 *e;
    Ent2_8004C2C8 *p;
    Ent2_8004C2C8 *prev;

    e = &((Ent_8004C2C8 *) D_8008B408)[id];
    if (e->unk8 == 0) {
        printf(D_800107F8, D_8008A950, 0x11B);
        exit(1);
    }
    func_8005109C(e->unk8);
    e->unk8 = 0;
    p = D_8008B424;
    D_8008B428 = 1;
    prev = 0;
    if (p != 0) {
        do {
            if (p->unk0 == id) {
                if (prev != 0) {
                    prev->unk8 = p->unk8;
                } else {
                    D_8008B424 = p->unk8;
                }
                p->unk0 = 0xFF;
            }
            prev = p;
            p = p->unk8;
        } while (p != 0);
    }
    D_8008B428 = 0;
}
