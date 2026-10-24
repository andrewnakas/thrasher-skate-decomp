#include "common.h"

typedef struct {
    u8 pad[0x50];
    s32 unk50;
} Rec_800503B0;

extern u8 D_800B0F6C[];
extern u8 D_800B10EC[];
extern u8 D_800B114C[];
extern u8 D_800B124C[];
extern u8 D_800B076C[];
extern s32 D_8008B440;
extern s32 D_8008B444;
extern s32 D_8008B448;
extern s32 D_8008B44C;
extern s32 D_8008A9CC;
extern s32 D_8008B43C;
extern s32 D_8008A9C8;

s32 func_800522A4(s32);
s32 func_800522D4(s32);
s32 func_80052380(s32);
s32 func_80066DAC(s32);
void func_80067064(s32 (*)(s32));
void func_80067088(s32 (*)(s32));
void func_800670AC(s32 (*)(s32));

s32 func_800503B0(void) {
    u32 j;
    u32 o;
    u32 i;
    s32 k;

    D_8008B440 = func_80066DAC(0);
    *(s32 *) D_8008B440 = 0x1000;
    func_80067064(func_800522A4);
    func_80067088(func_800522D4);
    func_800670AC(func_80052380);
    memset(D_800B0F6C, 0, 0x180);
    j = 0;
    k = -1;
    o = 0;
    do {
        i = 0;
        do {
            ((Rec_800503B0 *) (D_800B0F6C + o + i * 0xC))->unk50 = k;
            i++;
        } while (i < 3);
        j++;
        o += 0x60;
    } while (j < 4);
    for (j = 0; j < 0x18; j++) {
        *(s32 *) (D_800B10EC + j * 4) = 0;
    }
    D_8008B444 = 0;
    memset(D_800B114C, 0, 0x100);
    D_8008B448 = 0;
    memset(D_800B124C, 0, 0x100);
    D_8008B44C = 0;
    memset(D_800B076C, 0, 0x800);
    D_8008A9CC = 0;
    D_8008B43C = 0;
    D_8008A9C8 = 1;
    return 0;
}
