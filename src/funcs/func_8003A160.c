#include "common.h"

extern u8 D_800A8404[];
extern void func_8004862C();

typedef struct Rec_8003A160 {
    u16 unk0;
    u16 unk2;
    s16 unk4;
    u16 pad6;
} Rec_8003A160;

void func_8003A160(u8 a0) {
    u8 *b = D_800A8404;
    Rec_8003A160 *r;

    r = (Rec_8003A160 *) (b + (a0 & 0xFF) * 8);

    func_8004862C((((r->unk2 << 6) | ((r->unk0 >> 4) & 0x3F)) & 0xFFFF), r->unk4);
    r->unk4 = 0;
}
