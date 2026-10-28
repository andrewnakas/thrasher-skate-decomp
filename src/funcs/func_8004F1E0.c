#include "common.h"

/* Two-byte lookup rows. */
typedef struct {
    u8 f0;              /* 0x0 */
    u8 f1;              /* 0x1 */
} T_8004F1E0_ent;

extern T_8004F1E0_ent D_800B03C4[];
extern u8 D_800AFCA4[];

u8 *func_8004F1E0(s32 arg0) {
    T_8004F1E0_ent *base;
    u32 idx;
    T_8004F1E0_ent *ent;
    u8 *p;

    idx = arg0 & 0xFF;
    p = NULL;
    if (idx < 0x40) {
        base = D_800B03C4;
        ent = &base[idx];
        if (ent->f0 != 0 && ent->f1 != 0xFF && ent->f1 < 0x18) {
            p = D_800AFCA4 + ent->f1 * 0x4C;
        }
    }
    return p;
}
