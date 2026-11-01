#include "common.h"

typedef struct {
    u16 rate;
    u8 unk2;
    u8 pad3;
    s32 f4;
    s32 f8;
    s32 fC;
} Slot_80051E14;

typedef struct {
    u32 f0;
    s32 f4;
} Cfg_80051E14;

extern Slot_80051E14 D_800B114C[16];
extern s32 D_8008B448;

s32 func_80036324(void);
void func_800363B8(s32 a, s32 b, s32 c);

Slot_80051E14 *func_80051E14(Cfg_80051E14 *cfg, u32 flags) {
    Slot_80051E14 *slot;
    Slot_80051E14 *p;
    s32 i;

    slot = 0;
    i = D_8008B448;
    for (;;) {
        p = &D_800B114C[i];
        if (p->f4 == 0) {
            D_8008B448 = i + 1;
            if (D_8008B448 == 16) {
                D_8008B448 = 0;
            }
            slot = p;
            break;
        }
        i++;
        if (i == 16) {
            i = 0;
        }
        if (i == D_8008B448) {
            break;
        }
    }

    if (slot == 0) {
        return 0;
    }
    slot->f8 = 0;
    slot->f4 = cfg->f4;
    slot->fC = func_80036324();
    if (slot->fC == 0) {
        slot->f4 = 0;
        goto fail;
    }
    func_800363B8(slot->fC, cfg->f0 >> 11, cfg->f4);
    if (flags & 0x40) {
        slot->rate = 0xAC44;
    } else if (flags & 8) {
        slot->rate = 0x2B11;
    } else if (flags & 0x10) {
        slot->rate = 0x3E80;
    } else {
        slot->rate = 0x5622;
    }
    if (flags & 0x100) {
        slot->unk2 = 2;
    } else {
        slot->unk2 = 1;
    }
    return slot;
fail:
    return 0;
}
