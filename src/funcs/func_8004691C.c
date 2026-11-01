#include "common.h"

typedef struct {
    s16 x, y, w, h;
} Rect4691C;

typedef struct {
    u8 pad0[8];
    u32 w;          /* 0x08 */
    u16 h;          /* 0x0C */
    u8 padE[0x11 - 0xE];
    u8 bpp;         /* 0x11 */
    u8 pad12[0x14 - 0x12];
    u8 *pixels;     /* 0x14 */
    u8 pad18[0x420 - 0x18];
} Img4691C;

typedef struct {
    u16 tpage;
    u16 clut;
    u8 pad4[0xC];
} Tex4691C;

extern s32 D_8008A7F8;
extern s32 D_8008A800;
extern char D_8008A804[];
extern char D_8008A820[];
extern char D_8008A83C[];
extern char D_8008A854[];
extern char D_8008A86C[];
extern char D_8008A880[];
extern u16 D_8008B3B4;
extern u16 D_8008B3BC;
extern s16 D_8008B3BE;
extern char D_800A5F84[];
extern Tex4691C D_800AB794[];

extern void func_80034BD8(void *);
extern void *func_80034C20(s32);
extern void func_8003AE98(Rect4691C *, void *, s32);
extern u32 func_8004683C(u16, u16, u16);
extern void func_80047268(s32);
extern s16 func_80047414(Tex4691C *);
extern s16 func_80047454(Tex4691C *);
extern void func_80047494(Tex4691C *, s16);
extern void func_800474A4(Tex4691C *, s16);
extern void func_800476FC(Tex4691C *, s16);
extern void func_80047780(Tex4691C *, s16);
extern void func_80047834(Rect4691C *, Img4691C *, void *, s32);
extern void func_80047A00(Img4691C *);
extern void func_80047A08(Img4691C *);
extern s32 func_8004836C(s32, Img4691C *, u8 *);
extern s32 func_800484B4(s16, s32, u8 *, Rect4691C *);
extern s32 func_80048598(s16, s16, u8 *, Rect4691C *);
extern void func_8004869C(u8 *, s32);
extern s32 func_8004966C(u16 *, u16 *, u16 *, u16, u16);
extern int sprintf(char *, const char *, ...);

#define getTPage(tp, abr, x, y) \
    (((tp) << 7) | ((abr) << 5) | (((y) & 0x100) >> 4) | (((x) & 0x3FF) >> 6) | (((y) & 0x200) << 2))
#define getClut(x, y) (((y) << 6) | (((x) >> 4) & 0x3F))

u16 func_8004691C(s32 arg0, u16 x, u16 y, u16 z, u32 flags) {
    Img4691C img;
    u8 pal[0x400];
    Rect4691C r;
    Rect4691C r2;
    u32 div;
    s32 mode;
    s16 ncol;
    u16 id;
    Tex4691C *e;
    void *buf;
    s32 abr;

    D_8008A7F8 = flags & 0x80000000;
    buf = NULL;
    if (!(flags & 0x400000)) {
        if (x >= D_8008A800 && x != 0xFF) {
            sprintf(D_800A5F84, "Texture page out of range: page=%d", x);
            return 0xFFFF;
        }
    }
    func_80047A00(&img);
    if (func_8004836C(arg0, &img, pal) != 0) {
        sprintf(D_800A5F84, D_8008A804);
        return 0xFFFF;
    }
    if (img.bpp == 24) {
        sprintf(D_800A5F84, D_8008A820);
        return 0xFFFF;
    }
    if (img.bpp == 4) {
        div = 4;
        mode = 0;
    } else if (img.bpp == 8) {
        div = 2;
        mode = 1;
    } else {
        div = 1;
        mode = 2;
    }
    ncol = 1 << img.bpp;
    id = D_8008B3B4++;
    abr = id;
    e = &D_800AB794[abr];
    if (!(flags & 0x20000000)) {
        if (img.w & (16 / img.bpp - 1)) {
            sprintf(D_800A5F84, D_8008A83C);
            return 0xFFFF;
        }
        abr = (flags >> 25) & 3;
        if (!(flags & 0x800000)) {
            if (func_8004966C(&x, &y, &z, ((img.w + div - 1) / div) * 2, img.h) != 0) {
                sprintf(D_800A5F84, D_8008A854);
                return 0xFFFF;
            }
            r.x = func_8004683C(x, y, z);
            r.y = func_8004683C(x, y, z) >> 16;
        } else {
            r.x = y;
            r.y = z;
        }
        r.w = (img.w + div - 1) / div;
        r.h = img.h;
        if (D_8008A7F8 != 0) {
            buf = func_80034C20(r.w * (r.h / 2));
            func_80047834(&r, &img, buf, 16 / (s32)div);
        }
        func_80047494(e, r.x);
        func_800474A4(e, r.y);
        e->tpage = getTPage(mode, abr, func_80047414(e), func_80047454(e));
        func_800476FC(e, img.w);
        func_80047780(e, img.h);
        func_80047268(id);
    } else {
        abr = 0;
        func_80047494(e, 0);
        func_800474A4(e, 0);
        e->tpage = getTPage(mode, abr, func_80047414(e), func_80047454(e));
        func_800476FC(e, 8);
        func_80047780(e, 8);
        func_80047268(id);
    }
    func_8004869C(pal, 0x100);
    if (!(flags & 0x10000000)) {
        if (flags & 0x8000000) {
            if (func_80048598(ncol, flags, pal, &r2) == 0) {
                sprintf(D_800A5F84, D_8008A86C);
                return 0xFFFF;
            }
        } else if (!(flags & 0x400000)) {
            if (func_800484B4(ncol, 1, pal, &r2) == 0) {
                sprintf(D_800A5F84, D_8008A880);
                return 0xFFFF;
            }
        } else {
            r2.w = ncol;
            r2.h = 1;
            r2.x = (x & 0x3F) * 16;
            r2.y = x >> 6;
        }
        func_8003AE98(&r2, pal, 0);
        D_8008B3BE = ncol;
        D_8008B3BC = e->clut = getClut(r2.x, r2.y);
    } else if (flags & 0x1000000) {
        e->clut = D_8008B3BC;
    } else {
        e->clut = getClut(r2.x, r2.y);
    }
    if (!(flags & 0x20000000)) {
        if (D_8008A7F8 != 0) {
            func_8003AE98(&r, buf, 1);
            func_80034BD8(buf);
        } else {
            func_8003AE98(&r, img.pixels, 1);
        }
    }
    func_80047A08(&img);
    return id;
}
