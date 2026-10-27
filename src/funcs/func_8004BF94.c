#include "common.h"

typedef struct {
    u8 pad0[8];
    s32 unk8;
} Ent_8004BF94;

typedef struct Ent2_8004BF94 {
    u8 unk0;
    u8 pad1[3];
    s32 unk4;
    struct Ent2_8004BF94 *unk8;
} Ent2_8004BF94;

extern s32 D_8008A94C;
extern Ent2_8004BF94 *D_8008B424;
extern s32 D_8008B428;
extern u8 D_8008B408[4];
s32 func_80051574(s32, s32 *);
void func_8004C798(u8, s32);

s32 func_8004BF94(void) {
    Ent_8004BF94 *e;
    s32 t;
    u32 i;
    s32 one;

    if (D_8008A94C == 0) {
        return 0;
    }
    if (D_8008B428 != 0) {
        return 0;
    }
    if (D_8008B424 != 0) {
        i = 0;
        one = 1;
        e = (Ent_8004BF94 *) D_8008B408;
        do {
            if (e->unk8 != 0) {
                func_80051574(e->unk8, &t);
                if (t != one) {
                    return 0;
                }
            }
            i++;
            e = (Ent_8004BF94 *) ((u8 *) e + 12);
        } while (i < 2);
        func_8004C798(D_8008B424->unk0, D_8008B424->unk4);
        D_8008B424->unk0 = 0xFF;
        D_8008B424 = D_8008B424->unk8;
    }
    return 0;
}
