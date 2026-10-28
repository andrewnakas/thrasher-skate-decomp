#include "common.h"

extern u8 D_8006F818[];

typedef struct {
    u32 count;
    u16 f4;
    u8 *arr;
    u8 *other;
} Rec_0078;

s32 func_80020078(u8 kind, s32 a1, s32 a2, Rec_0078 *rec, u16 arg5, u8 arg6) {
    u32 n = rec->count;
    u8 *arr = rec->arr;
    u8 *base = arr;
    s32 i;
    s32 idx = 0;
    u8 *q = D_8006F818;

    for (i = 0; i < n; i++) {
        if (arr[i * 0x10] == kind) {
            idx = i;
            break;
        }
    }

    *(u16 *) (q + 2) = 0;
    *(u16 *) (q + 4) = 0;
    *(u16 *) (q + 6) = *(u16 *) rec->other;
    *(u16 *) (q + 8) = *(u16 *) (base + idx * 0x10 + 4);
    *(u16 *) (q + 0xA) = *(u16 *) (base + idx * 0x10 + 8);
    *(u16 *) (q + 0xC) = *(u16 *) (base + idx * 0x10 + 0xC);
    *(u16 *) (q + 0xE) = rec->f4;
    *(u16 *) (q + 0x10) = arg5;
    func_80045D78((s16) a1, (s16) a2, arg6, arg6, q);
    return (*(u32 *) (base + idx * 0x10 + 0xC) * arg6) & 0xFFFF;
}
