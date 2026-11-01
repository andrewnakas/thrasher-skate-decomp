#include "common.h"

typedef struct {
    s32 unk0;
    s32 state;
    s32 unk8;
} Chan_80035D2C;

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 busy;
    u8 type;
    u8 pad[4];
} Slot_80035D2C;

extern void func_80035BC0(u8 *, s32);
extern void func_80035C14(u8 *, s32);
extern void func_80035C9C(u8 *, s32);
extern Chan_80035D2C D_800A6294[];

void func_80035D2C(u8 *base, s32 port) {
    Slot_80035D2C *s;
    s32 off;
    s32 i;
    s32 ch;

    for (i = 0; i < 4; i++) {
        u8 type;

        s = &((Slot_80035D2C *) base)[i];
        ch = port * 4 + i;
        off = i * 8 + 2;
        type = s->type;
        if (s->busy == 0) {
            switch (type >> 4) {
                case 4:
                    func_80035BC0(base + off, ch);
                    break;
                case 2:
                    func_80035C14(base + off, ch);
                    break;
                case 7:
                    func_80035C9C(base + off, ch);
                    break;
                default:
                    D_800A6294[ch].state = -1;
                    break;
            }
        } else {
            D_800A6294[ch].state = -1;
        }
    }
}
