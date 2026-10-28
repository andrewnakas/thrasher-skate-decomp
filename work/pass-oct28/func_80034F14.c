#include "common.h"

typedef struct {
    s32 unk0; /* 0x00 */
    u8 *unk4; /* 0x04 */
    s8 unk8;  /* 0x08 */
    u8 pad9[0xB];
} Bank_80034F14;

typedef struct {
    s8 unk0;   /* 0x00 */
    u8 unk1;   /* 0x01 */
    u16 unk2;  /* 0x02 */
    s32 unk4;  /* 0x04 */
    s32 unk8;  /* 0x08 */
    s32 unkC;  /* 0x0C */
    u8 pad10[0x1C];
} Slot_80034F14;

extern u8 D_800A6244[];
extern Slot_80034F14 D_800A6084[10];
extern u16 D_8008B128;
extern void *memset(void *, s32, u32);
extern void func_800358A8(void);

u8 *func_80034F14(void) {
    Bank_80034F14 *bank;
    Slot_80034F14 *slot;
    u32 i;
    u32 j;

    for (i = 0; i < 4; i++) {
        if (*(u32 *) (D_800A6244 + (i & 0xFF) * 20) == 0) {
            break;
        }
    }
    if (i == 4) {
        return 0;
    }
    slot = D_800A6084;
    for (j = 0; j < 0xA; j++) {
        if (slot->unk1 == -1) {
            break;
        }
        slot++;
    }
    if (j == 0xA) {
        return 0;
    }
    slot->unk0 = -1;
    slot->unk1 = i;
    slot->unk2 = 0;
    slot->unk4 = 0;
    slot->unk8 = 0;
    slot->unkC = 0;
    memset((u8 *) slot + 0x10, 0, 0x10);
    bank = (Bank_80034F14 *) (D_800A6244 + (i & 0xFF) * 20);
    D_8008B128 = D_8008B128 + 1;
    bank->unk0 = 1;
    bank->unk4 = (u8 *) slot;
    bank->unk8 = -1;
    func_800358A8();
    if (bank->unk8 == -1) {
        slot->unk2 |= 1;
    }
    return (u8 *) slot;
}
