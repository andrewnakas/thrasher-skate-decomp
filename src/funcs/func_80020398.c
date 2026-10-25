#include "common.h"

extern u8 D_8008AED4;
extern u8 *D_8008AEE4[1];

typedef struct {
    u8 d[0x14];
} Blk_80020398;

typedef struct {
    u8 f0;
    s32 f4;
    s32 f8;
    s32 fC;
} Rec_80020398;

u8 *func_80034C20(s32);

s32 func_80020398(u8 *src, u8 *dst) {
    u8 *p;
    u32 size;
    u8 *b;
    u32 i;
    u8 idx;

    p = src;
    *(Blk_80020398 *) dst = *(Blk_80020398 *) p;
    size = *(u32 *) dst * 16;
    b = func_80034C20(size);
    p += 0xC;
    *(u8 **) (dst + 8) = b;
    if (b == NULL) {
        return 1;
    }
    memset(b, 0, size);
    for (i = 0; i < *(u32 *) dst; i++) {
        ((Rec_80020398 *) (*(u8 **) (dst + 8)))[i].f0 = *p;
        p += 1;
        ((Rec_80020398 *) (*(u8 **) (dst + 8)))[i].f4 = *p;
        p += 4;
        ((Rec_80020398 *) (*(u8 **) (dst + 8)))[i].f8 = *p;
        p += 4;
        ((Rec_80020398 *) (*(u8 **) (dst + 8)))[i].fC = *p;
        p += 4;
    }
    *(u8 *) (dst + 0x10) = 0;
    idx = D_8008AED4++;
    D_8008AEE4[idx] = dst;
    return 0;
}
