#include "common.h"

typedef struct {
    s32 unk0;
    u8 pad4[0x5C];
} Unk80036120;

extern Unk80036120 D_800A677C[];
extern s32 D_8008A598;
extern s32 D_8008A578;
extern s32 D_8008B130;
extern s32 D_8008B12C;
void VSync(s32);
void func_8005CBD8(s32);
s32 func_8005CBEC(s32, s32, s32);
void func_80033F1C(void);

void func_80036120(void) {
    s32 i;

    D_8008A578 = D_8008A598 * 10;
    while (D_8008B130 != 0) {
        if (--D_8008A578 == 0) {
            break;
        }
        VSync(0);
    }
    if (D_8008B130 != 0) {
        D_8008B130 = 0;
        D_8008B12C = 0;
        func_8005CBD8(0);
        func_8005CBEC(7, 0, 0);
    }
    for (i = 0; i < 0x14; i++) {
        if (D_800A677C[i].unk0 != 0) {
            D_800A677C[i].unk0 = 0;
        }
    }
    func_80033F1C();
}
