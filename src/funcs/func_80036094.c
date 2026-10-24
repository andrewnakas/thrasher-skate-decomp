#include "common.h"

typedef struct {
    s32 unk0;
    u8 pad4[0x5C];
} Unk80036094;

extern Unk80036094 D_800A677C[];
extern u8 D_800A777C[];
extern s32 D_8008B130;
extern s32 D_8008B12C;
extern s32 D_8008B134;
s32 func_80036F24(void);
s32 CdInit(void);
void func_8005CB90(s32);
s32 func_800361F0(s32);
void *memset(void *, s32, u32);

s32 func_80036094(void) {
    s32 i;

    for (i = 0x13; i >= 0; i--) {
        D_800A677C[i].unk0 = 0;
    }
    memset(D_800A777C, 0, 0x780);
    D_8008B130 = 0;
    D_8008B12C = 0;
    D_8008B134 = 0;
    if (func_80036F24() != 0) {
        return 1;
    }
    if (CdInit() == 0) {
        return 1;
    }
    func_8005CB90(0);
    func_800361F0(1);
    return 0;
}
