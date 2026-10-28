#include "common.h"

extern u8 *D_8008AEC4;

typedef struct {
    u32 w[0x11];
} Rec;

s32 func_8001D804(u16 idx, u8 *src) {
    u32 n = (u32) idx & 0xFFFF;
    u8 *base = D_8008AEC4;
    u8 *dst = (u8 *) (n * 0x44 + (u32) base);

    *(Rec *) dst = *(Rec *) src;
    return 0;
}
