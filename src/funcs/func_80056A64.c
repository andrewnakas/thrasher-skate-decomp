#include "common.h"

typedef struct {
    u8 pad0[0xC];
    u32 fC;
    u8 pad10[0x44 - 0x10];
    u32 f44[(0x61 - 0x44) / 4];
    u8 pad60;
    u8 f61;
    u8 f62;
    u8 f63;
    u8 pad64[0x70 - 0x64];
} Rec;

typedef struct {
    u32 val;
    u8 id;
    u8 pad5[3];
} Ent;

typedef struct {
    u8 pad0[0x10];
    u32 f10;
    Ent e[5];
} Hdr;

extern Rec D_800B2428[];
extern u8 D_8008B4DC;

s32 func_80056A3C(s32 idx);
Hdr *func_8001D0A0(s32);

void func_80056A64(u8 *count, s16 *out) {
    u32 buf[5];
    u32 lim;
    Hdr *h;
    s32 i;
    u8 c;

    lim = D_800B2428[D_8008B4DC].fC;
    h = func_8001D0A0(func_80056A3C(D_800B2428[D_8008B4DC].f61));
    *count = 0;
    for (i = 0; i < 5; i++) {
        if (D_800B2428[D_8008B4DC].f63 != 1) {
            buf[i] = h->e[i].val;
        } else {
            buf[i] = h->f10;
        }
    }
    for (i = 0; i < 5; i++) {
        if (lim >= buf[i]) {
            c = h->e[i].id;
            if (!((D_800B2428[D_8008B4DC].f44[c >> 5] >> (c & 0x1F)) & 1) && c != 0) {
                if (c != 0x13) {
                    out[*count] = h->e[i].id;
                } else {
                    switch (D_800B2428[D_8008B4DC].f62) {
                    case 0:
                    case 1:
                        out[*count] = 0x49;
                        break;
                    case 2:
                    case 3:
                        out[*count] = 0x4A;
                        break;
                    case 4:
                    case 5:
                    case 12:
                        out[*count] = 0x45;
                        break;
                    case 6:
                    case 7:
                        out[*count] = 0x46;
                        break;
                    case 8:
                    case 9:
                        out[*count] = 0x47;
                        break;
                    case 10:
                    case 11:
                        out[*count] = 0x48;
                        break;
                    }
                }
                *count += 1;
            }
        }
    }
}
