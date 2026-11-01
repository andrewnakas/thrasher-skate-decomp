#include "common.h"

typedef struct {
    u16 flags;
    u8 state;
    u8 pad3;
    u32 size;
    u8 pad8[4];
    u32 pos;
    u8 pad10[0xC];
    u32 end;
    u8 pad20[0x20];
    s32 voice;
    u8 pad44[8];
    s32 voice2;
} Strm_80054354;

extern Strm_80054354 D_800B134C;
extern s32 D_800B1390[];

extern void SpuSetIRQ(s32);
extern void SpuSetIRQAddr(u32);
extern void SpuSetKey(s32, u32);

void func_80054354(void) {
    u32 size;
    u32 addr;
    u32 t;
    s32 left;
    u32 mask;

    SpuSetIRQ(0);
    if (D_800B134C.state == 4) {
        D_800B134C.pos += (D_800B134C.flags & 0x200) ? 0x1000 : 0x800;
        if (D_800B134C.pos >= D_800B134C.size) {
            D_800B134C.pos -= D_800B134C.size;
        }
        size = D_800B134C.size;
        if (D_800B134C.flags & 0x200) {
            size >>= 1;
            t = D_800B134C.pos >> 1;
        } else {
            t = D_800B134C.pos;
        }
        addr = t + 0x800;
        if (addr >= size) {
            addr -= size;
        }
        if (D_800B134C.flags & 0x1000) {
            if (D_800B134C.end > D_800B134C.pos) {
                left = D_800B134C.end - D_800B134C.pos;
            } else {
                left = D_800B134C.end + D_800B134C.size - D_800B134C.pos;
            }
            if (D_800B134C.flags & 0x200) {
                if (left <= 0x1000) {
                    goto set;
                }
            } else if (left <= 0x800) {
            set:
                addr = D_800B134C.end;
                D_800B134C.state = 6;
                if (D_800B134C.flags & 0x200) {
                    addr >>= 1;
                }
            }
        }
        SpuSetIRQAddr(D_800B1390[0] + addr);
        SpuSetIRQ(1);
        return;
    }
    if (D_800B134C.state == 6) {
        D_800B134C.state = 1;
    }
    mask = 1 << D_800B134C.voice;
    if (D_800B134C.flags & 0x200) {
        mask |= 1 << D_800B134C.voice2;
    }
    SpuSetKey(0, mask);
}
