#include "common.h"

typedef struct {
    u8 pad0[4];
    s32 unk4;
    s32 unk8;
    u16 unkC;
    u16 padE;
} Rec_8005853C;

extern s32 D_8008B4E8;
extern s32 D_8008AC5C;
extern void func_8005757C(void);
extern Rec_8005853C *func_80057E5C(s32 a0);
extern void func_800168AC(void);
extern s32 func_800BB758(void);

s32 func_8005853C(void) {
    u32 i;

    func_8005757C();

    for (i = 0; i < 2; i++) {
        Rec_8005853C *r = func_80057E5C(i);

        if (r->unk8 & ~0x300) {
            r->unkC = 0x14;
        } else if (r->unkC != 0) {
            r->unkC = r->unkC - 1;
        } else {
            s32 t = 0;

            r->unk8 = r->unk4 & 0xF;
            if ((r->unk4 & 0x300) == 0) {
                t = 3;
            }
            r->unkC = t;
        }
    }

    if (D_8008B4E8 != 0) {
        func_800168AC();
        return 0;
    }

    if (func_800BB758() != 0) {
        return 1;
    }

    D_8008AC5C++;
    return 0;
}
