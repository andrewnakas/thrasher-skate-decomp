#include "common.h"

typedef struct {
    u8 ch;
    u8 pad1[0xB];
    s32 width;
} Glyph;

typedef struct {
    u32 count;
    s32 pad4;
    Glyph *glyphs;
} Font;

s32 strlen(const char *);

u16 func_8002028C(u8 *str, Font *font, u8 scale) {
    u16 len;
    u16 w;
    u16 i;
    u16 j;
    u16 idx;
    u8 found;

    len = strlen(str);
    w = 0;
    for (i = 0; i < len; i++) {
        found = 0;
        idx = 0;
        for (j = 0; j < font->count && !found; j++) {
            if (str[i] == font->glyphs[j].ch) {
                found = 1;
                idx = j;
            }
        }
        if (found) {
            w = (u16) (font->glyphs[idx].width * scale) + 1 + w;
        }
    }
    return w;
}
