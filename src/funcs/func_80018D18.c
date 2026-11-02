#include "common.h"

typedef struct {
    u8 field00;
    u8 field01;
    u8 width;
    u8 field03;
    u8 left;
    u8 field05;
    u8 right;
    u8 field07;
    u16 code;
} Glyph_80018D18;

typedef struct {
    u8 pad00[0x38];
    s32 *resource;
    u8 pad3C[0x10];
    u16 spacing;
    u16 pad4E;
} Owner_80018D18;

extern s32 D_8008AD88;
extern Owner_80018D18 *D_8008AD90;
extern s32 D_8008AD94;
extern void *func_80015E8C(s32);
extern void func_80015F10(s32);
extern u8 *func_80019518(s32 *);
extern void func_8001954C(s32 *);

s32 func_80018D18(s32 *resource, u8 *text) {
    s32 firstCode;
    u8 hadCache;
    Owner_80018D18 *owner;
    u8 *font;
    s32 direct;
    u16 width;
    u8 ch;
    s32 code;
    s32 count;
    Glyph_80018D18 *glyph;

    firstCode = 0;
    if (D_8008AD90 == NULL) {
        hadCache = 0;
        D_8008AD90 = func_80015E8C(D_8008AD94);
    } else {
        hadCache = 1;
    }
    owner = &D_8008AD90[D_8008AD88];
    if (resource == NULL) {
        resource = owner->resource;
    }
    font = func_80019518(resource);
    direct = 1;
    if (*(u16 *) font < 0x100U) {
        firstCode = *(u16 *) (font + 0x20);
    } else {
        direct = 0;
    }
    ch = *text;
    width = 0;
    if (ch >= 3U) {
        do {
            if (ch == 1) {
                ch = *++text;
                code = (ch - 2) * 0xFE;
                code += *++text - 2;
            } else if (ch == 0x7E) {
                text++;
                code = 0;
                if ((u32) (*text - 0x30) < 0xAU) {
                    do {
                        code = code * 10 + (*text++ - 0x30);
                    } while ((u32) (*text - 0x30) < 0xAU);
                }
                if (*text == 0x7E) {
                    text++;
                }
            } else {
                code = *text;
            }
lookup:
            if (direct != 0) {
                glyph = NULL;
                if (code >= (s32) firstCode &&
                    firstCode + *(u16 *) font >= code) {
                    glyph = (Glyph_80018D18 *)
                        (font + ((code - firstCode) * 10 + 0x18));
                }
            } else {
                count = *(u16 *) font;
                glyph = (Glyph_80018D18 *) (font + 0x18);
                if (count > 0) {
                    do {
                        if (glyph->code == code) {
                            count = -999;
                        } else {
                            glyph++;
                        }
                        count--;
                    } while (count > 0);
                }
                if (count >= -500) {
                    glyph = NULL;
                }
            }
            if (glyph == NULL) {
                if (code < 0x61) {
                    goto resolved;
                }
                if (code < 0x7B) {
                    code -= 0x20;
                    goto lookup;
                }
            }
resolved:
            if (glyph != NULL) {
                width += ((owner->spacing + (s8) glyph->left) +
                          glyph->width) + (s8) glyph->right;
            }
            text++;
            ch = *text;
        } while (ch >= 3U);
    }
    func_8001954C(resource);
    if (!hadCache) {
        D_8008AD90 = NULL;
        func_80015F10(D_8008AD94);
    }
    return width & 0xFFFF;
}
