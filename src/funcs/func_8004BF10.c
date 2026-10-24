#include "common.h"

typedef struct {
    u8 pad0[8];
    s32 unk8;
} Ent_8004BF10;

extern s32 D_8008A94C;
extern u8 D_8008B408[4];
extern char D_800107F8[];
extern char D_8008A950[];
void func_8005109C(s32);

void func_8004BF10(void) {
    Ent_8004BF10 *e;
    s32 v;
    u32 i;

    if (D_8008A94C == 0) {
        printf(D_800107F8, D_8008A950, 0x7A);
        exit(1);
    }
    e = (Ent_8004BF10 *) D_8008B408;
    for (i = 0; i < 2; i++) {
        v = e[i].unk8;
        if (v != 0) {
            func_8005109C(v);
            e[i].unk8 = 0;
        }
    }
    D_8008A94C = 0;
}
