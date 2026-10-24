#include "common.h"

typedef struct {
    u16 unk0;
    u16 unk2;
    u32 unk4;
    u32 unk8;
    s32 unkC;
    u16 unk10;
} Ent_8003AB50;

extern Ent_8003AB50 *D_8008B208;
extern u32 func_80034C20(u32 size);
extern void *memset(void *p, s32 c, u32 n);

Ent_8003AB50 *func_8003AB50(s16 a, u16 b, s32 c, s16 d) {
    Ent_8003AB50 *e;
    u32 size;

    e = D_8008B208;
    size = b << 2;
    D_8008B208 = e + 1;
    e->unk4 = func_80034C20(size);
    e->unk8 = func_80034C20(size);
    memset((void *) e->unk4, 0, size);
    memset((void *) e->unk8, 0, size);
    e->unk2 = b;
    e->unk0 = a;
    e->unkC = c;
    e->unk10 = d;
    return e;
}
