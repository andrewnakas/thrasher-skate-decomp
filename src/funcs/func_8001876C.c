#include "common.h"

typedef struct {
    u8 field00, field01;
    u8 width, height;
    u8 left, top, right, bottom;
    u16 code;
} Glyph_8001876C;

typedef struct {
    u8 pad00[0x38];
    s32 *resource;
    volatile u32 field3C;
    u16 flags;
    u16 pad42;
    u32 field44;
    u32 color;
    u16 spacing;
    u16 pad4E;
} Owner_8001876C;

extern s16 D_8008AD74, D_8008AD76, D_8008AD78, D_8008AD7A;
extern s32 D_8008AD88;
extern Owner_8001876C *D_8008AD90;
extern s32 D_8008AD94;
extern void *func_80015E8C(s32);
extern void func_80015F10(s32);
extern u8 *func_80019518(s32 *);
extern void func_8001954C(s32 *);
extern void func_80038864(u32, u8, s32, s16, s32, s32, s32);
extern void func_80039480(u8 *, Glyph_8001876C *, s32, u32, u32, s32, s32, u16, u16);

void func_8001876C(u8 *text, s16 x, u16 y) {
    u16 savedY;
    u8 hadCache;
    s32 firstCode;
    Owner_8001876C *owner;
    s32 *resource;
    u8 *font;
    s32 direct;
    s32 signedY;
    s32 code;
    s32 count;
    Glyph_8001876C *glyph;
    u8 *drawFont;
    u16 drawField;
    u8 ch;
    s16 totalWidth, totalHeight;
    s16 clipX, clipWidth, clipHeight;
    u16 clipY;
    s32 mode;
    u32 style, color;
    u16 flags;

    firstCode = 0;
    savedY = y;
    if (D_8008AD90 == NULL) {
        hadCache = 0;
        D_8008AD90 = func_80015E8C(D_8008AD94);
    } else {
        hadCache = 1;
    }
    owner = &D_8008AD90[D_8008AD88];
    resource = owner->resource;
    if (resource != NULL) {
        font = func_80019518(resource);
        direct = 1;
        if (*(u16 *) font < 0x100U) {
            firstCode = *(u16 *) (font + 0x20);
        } else {
            direct = 0;
        }
        ch = *text;
        if (ch >= 3U) {
            signedY = (s16) savedY;
            while (1) {
                if (x >= D_8008AD78) {
                    goto text_done;
                }
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
                    if (code >= firstCode && firstCode + *(u16 *) font >= code) {
                        glyph = (Glyph_8001876C *)
                            (font + ((code - firstCode) * 10 + 0x18));
                    }
                } else {
                    count = *(u16 *) font;
                    glyph = (Glyph_8001876C *) (font + 0x18);
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
                    mode = 0;
                    if (!(owner->flags & 1)) {
                        totalWidth = ((s8) glyph->left + glyph->width) + (s8) glyph->right;
                        clipWidth = totalWidth;
                        totalHeight = ((s8) glyph->top + glyph->height) + (s8) glyph->bottom;
                        clipHeight = totalHeight;
                        if (glyph->width < totalWidth && totalHeight > glyph->height) {
                            clipY = savedY;
                            clipX = x;
                            if (x < D_8008AD74) {
                                clipWidth = totalWidth - ((u16) D_8008AD74 - x);
                                clipX = (u16) D_8008AD74;
                            }
                            if (D_8008AD78 < clipX + clipWidth) {
                                clipWidth = (u16) D_8008AD78 - clipX;
                            }
                            if (signedY < D_8008AD76) {
                                clipHeight = totalHeight - ((u16) D_8008AD76 - clipY);
                                clipY = (u16) D_8008AD76;
                            }
                            if (D_8008AD7A < (s16) clipY + clipHeight) {
                                clipHeight = (u16) D_8008AD7A - clipY;
                            }
                            if (clipWidth > 0 && clipHeight > 0) {
                                func_80038864(owner->color, 0, 0, clipX, (s16) clipY,
                                    clipX + clipWidth, (s16) clipY + clipHeight);
                            }
                        }
                        mode = 0;
                    }
                    color = mode;
                    flags = owner->flags;
                    style = mode;
                    if (flags & 2) {
                        mode = 1;
                    } else if (flags & 4) {
                        mode = 2;
                        color = 0;
                        if (!(flags & 1)) {
                            color = owner->color;
                        }
                        style = owner->field44;
                    } else if (flags & 1) {
                        mode = 3;
                        color = 0;
                    }
                    drawFont = font;
                    drawField = owner->field3C;
                    func_80039480(drawFont, glyph, mode, style, color,
                        x + (s8) glyph->left, signedY + (s8) glyph->top,
                        *(u16 *) (font + 0x14), drawField);
                    x += ((s8) glyph->left + (owner->spacing + glyph->width)) +
                         (s8) glyph->right;
                }
                text++;
                ch = *text;
                if (ch < 3U) {
                    break;
                }
            }
        }
text_done:
        func_8001954C(resource);
    }
    if (!hadCache) {
        D_8008AD90 = NULL;
        func_80015F10(D_8008AD94);
    }
}
