#include "common.h"

extern s32 D_8008A2BC;
extern s32 D_8008AF6C[];

void func_8002475C(u8 *a0, u8 *a1, s32 a2, u8 *a3) {
    s32 i;
    u8 *rec;

    func_80012238(a1);
    func_80023ECC(a0, a1);

    i = 0;
    rec = a0;
    while (i < *(s32 *) a0) {
        *(u32 *) (rec + 0x6C) = *(u32 *) (a3 + 0);
        *(u32 *) (rec + 0x70) = *(u32 *) (a3 + 4);
        *(u32 *) (rec + 0x74) = *(u32 *) (a3 + 8);
        func_800331FC(rec + 0x6C, 0x8000);
        *(u16 *) (rec + 6) = 0;
        *(u16 *) (rec + 4) = 1;
        *(u32 *) (rec + 0x54) = *(u32 *) (rec + 0x48);
        *(u32 *) (rec + 0x58) = *(u32 *) (rec + 0x4C);
        *(u32 *) (rec + 0x5C) = *(u32 *) (rec + 0x50);
        i++;
        rec += 0x8C;
    }

    func_80024720(a0);
    *(u32 *) (a0 + 0x131C) = *(u32 *) (a0 + 0x48);
    *(u32 *) (a0 + 0x1320) = *(u32 *) (a0 + 0x4C);
    *(u32 *) (a0 + 0x1324) = *(u32 *) (a0 + 0x50);
    *(u16 *) (a1 + 0x1A) = 0;
    *(u16 *) (a1 + 0x1C) = 0;
    *(u16 *) (a1 + 0x1E) = 0;
    *(u16 *) (a1 + 0x18) = 0;
    *(u32 *) (a0 + 0x132C) = 1;
    func_80025004(a0, a1);
    func_80024D6C(a0, a1);
    func_80025544(a0, a1);

    D_8008AF6C[D_8008A2BC] = 0;
}
