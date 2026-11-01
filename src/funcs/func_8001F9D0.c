#include "common.h"

typedef struct {
    s32 x, y, z;
} Vec_8001F9D0;

typedef struct {
    u16 flags;
    u8 pad2[0xE];
    Vec_8001F9D0 pos;
    u8 pad1C[0x20];
    u8 font;
    u8 bank;
    u8 glyphs[1];
} Text_8001F9D0;

typedef struct {
    u8 pad0[0x18];
    u8 *str;
    u8 font;
    u8 bank;
} Src_8001F9D0;

extern void func_8001EA78(void);
extern u8 func_8002050C(s32, u8);
extern void func_80011EF4(Vec_8001F9D0 *, Vec_8001F9D0 *);
extern s32 func_80020570(s32, u8 *, s32);

s32 func_8001F9D0(Text_8001F9D0 *t, Src_8001F9D0 *src) {
    Vec_8001F9D0 v;
    u8 *s;
    u8 *d;
    u8 bank;
    u8 c;

    func_8001EA78();
    s = src->str;
    bank = src->bank;
    d = t->glyphs;
    while ((c = *s++) != 0) {
        *d++ = func_8002050C(bank, c);
    }
    *d = 0xFF;
    t->bank = bank;
    t->font = src->font;
    v.x = t->pos.x;
    v.y = t->pos.y;
    v.z = t->pos.z;
    func_80011EF4(&v, &t->pos);
    t->flags |= 0x40;
    t->pos.x -= (func_80020570(bank, src->str, 10) / 2) << 16;
    return 0;
}
