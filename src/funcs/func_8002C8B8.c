#include "common.h"

typedef struct {
    u16 unk0;
    u16 unk2;
    u32 unk4;
} R_8002C8B8;

typedef struct L_8002C8B8 {
    u8 pad0[0x4C];
    u8 *unk4C;
    u8 pad50[2];
    u16 unk52;
    u8 pad54[0x40];
    struct L_8002C8B8 *unk94;
} L_8002C8B8;

typedef struct {
    u32 unk0;
    u16 unk4;
    u16 unk6;
} O_8002C8B8;

extern L_8002C8B8 *D_800A4F04[3];

void func_80034C8C(O_8002C8B8 *, u32);

void func_8002C8B8(O_8002C8B8 *o) {
    L_8002C8B8 *l;
    R_8002C8B8 *r;
    u8 *p;
    s32 n;
    s32 i;
    s32 j;

    o->unk6 = o->unk0;
    r = (R_8002C8B8 *) ((u8 *) o + o->unk6);
    i = 0;

    for (l = D_800A4F04[0]; l != 0; l = l->unk94, i++) {
        n = l->unk52;
        p = l->unk4C;

        j = 0;
        if (n > 0) {
            do {
                if (p[3] != 0) {
                    func_80034C8C(o, o->unk0 += 8);
                    o->unk4++;
                    r->unk0 = i;
                    r->unk2 = j;
                    r->unk4 = *(u32 *) p;
                    r++;
                }
                j++;
                p += p[2];
            } while (--n > 0);
        }
    }
}
