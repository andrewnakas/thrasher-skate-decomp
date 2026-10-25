#include "common.h"

extern s32 D_8008A2BC;
extern u16 D_8008A2C0[4];

extern void func_800337C4(void *);
extern void func_80033DB0(void *, void *);
extern void func_80025898(void *, void *, void *);

void func_80025988(u8 *a0, u8 *a1) {
    u8 work[0x30];
    u16 hdr[3];

    memset(hdr, 0, 6);
    hdr[0] = D_8008A2C0[D_8008A2BC];
    func_800337C4(work);
    func_80033DB0(work, hdr);
    func_80025898(a0, a1, work);
}
