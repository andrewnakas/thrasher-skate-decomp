#include "common.h"

typedef struct {
    u8 pad[0xC];
    s32 w;
} Glyph;

typedef struct {
    u8 pad[8];
    Glyph *glyphs;
} Font;

extern Font *func_800204F4(s32);
extern u8 func_8002050C(s32, u8);

s32 func_80020570(s32 font, u8 *s, s32 spacing) {
    u8 c;
    Font *f;
    s32 w;

    f = func_800204F4(font);
    w = -spacing;
    while ((c = *s++) != 0) {
        c = func_8002050C(font, c);
        w += f->glyphs[c].w + spacing;
    }
    return w;
}
