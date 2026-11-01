#include "common.h"

typedef struct {
    s8 unk0;
    s8 port;
    u16 flags;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 buf[0x10];
    u8 pad20[0xC];
} Chan_80034F14;

typedef struct {
    s32 used;
    Chan_80034F14 *ch;
    s8 status;
    u8 pad9[0xB];
} Port_80034F14;

extern void func_800358A8(void);
extern u16 D_8008B128;
extern Chan_80034F14 D_800A6084[];
extern Port_80034F14 D_800A6244[];

Chan_80034F14 *func_80034F14(void) {
    Chan_80034F14 *c;
    u8 i;
    u16 j;

    for (i = 0; i < 4; i++) {
        if (D_800A6244[i].used == 0) {
            break;
        }
    }
    if (i == 4) {
        return NULL;
    }
    c = D_800A6084;
    for (j = 0; j < 10; j++, c++) {
        if (c->port == -1) {
            break;
        }
    }
    if (j == 10) {
        return NULL;
    }
    c->unk0 = -1;
    c->port = i;
    c->flags = 0;
    c->unk4 = 0;
    c->unk8 = 0;
    c->unkC = 0;
    memset(c->buf, 0, 0x10);
    D_800A6244[i].used = 1;
    D_800A6244[i].ch = c;
    D_8008B128++;
    D_800A6244[i].status = -1;
    func_800358A8();
    if (D_800A6244[i].status == -1) {
        c->flags |= 1;
    }
    return c;
}
