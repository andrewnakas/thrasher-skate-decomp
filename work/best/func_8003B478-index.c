#include "common.h"

/* one 0x70-byte display record inside D_8008234C */
typedef struct {
    u8 pad0[2];
    s16 f2;
    s16 f4;
    s16 f6;
    u8 pad8[2];
    s16 fA;
    u8 padC[0xC];
    u8 f18;
    u8 pad19[0x45];
    s16 f5E;
    s16 f60;
    s16 f62;
    u8 pad64[8];
    u8 f6C;
    u8 pad6D[3];
} REC_8003B478;

extern REC_8003B478 D_8008234C[];
extern u32 D_8008B248;
extern u32 D_8008B24C;
extern void func_8003B854(void);
extern void func_8003B5D8(s32 a0, s32 a1);
extern void VSync(s32 a0);
extern void func_8005A268(s32 a0);
extern void func_8005A174(s32 a0);

u32 func_8003B478(s32 a0, s32 a1) {
    s32 upright = a1 < 0x101;
    s32 one = 1;
    s32 top = 0x100;
    s32 i;
    u8 *p;
    u32 prev;

    prev = *(u16 *) &D_8008B248 | ((u32) (*(u16 *) &D_8008B24C) << 16);
    D_8008B248 = a0;
    D_8008B24C = a1;
    for (i = 0; i < 2; i++) {
        REC_8003B478 *rec = &D_8008234C[i];

        rec->f4 = a0;
        rec->f6 = a1;
        rec->f60 = a0;
        rec->f62 = a1;
        if (upright) {
            rec->f18 = one;
            if (i == 0) {
                rec->f2 = 0;
            } else {
                rec->f2 = top;
            }
            rec->fA = rec->f2;
            if (i == 0) {
                rec->f5E = top;
            } else {
                rec->f5E = 0;
            }
            rec->f6C = 0;
        } else {
            rec->f18 = 0;
            rec->f2 = 0;
            rec->fA = 0;
            rec->f5E = 0;
            rec->f6C = one;
        }
    }
    func_8003B854();
    func_8003B5D8(a0 >> 1, a1 >> 1);
    VSync(0);
    p = (u8 *) D_8008234C;
    func_8005A268(*(s32 *) (p + 0xE4) + 0x5C);
    func_8005A174(*(s32 *) (p + 0xE4));
    return prev;
}
