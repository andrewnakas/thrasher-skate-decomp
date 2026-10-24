#include "common.h"

typedef struct {
    u32 unk0;
    u16 unk4;
    u16 unk6;
} Ent_8003F9A4;

extern Ent_8003F9A4 D_800A964C[];

u32 func_8003F9A4(s32 a0) {
    Ent_8003F9A4 *e = D_800A964C;

    if (e->unk0 != 0) {
        do {
            if (e->unk4 == a0) {
                return e->unk0;
            }
            e++;
        } while (e->unk0 != 0);
    }
    return 0;
}
