#include "common.h"

typedef struct {
    u8 magic[2];
    u8 type;
    u8 blocks;
    u8 title[0x40];
    u8 pad44[0x1C];
    u8 clut[0x20];
    u8 icon[3][0x80];
} McHdr_80037DC4;

extern void func_8001651C(u8 *, s32);
extern void func_80034D4C(void *, void *, s32);
extern s32 func_80037BB8(void);
extern u8 func_80037C20(u8 *, s32);
extern void func_80037CB4(u8 *, u8 *);
extern s32 func_800382C0(u32);
extern s32 MemCardDeleteFile(s32, u8 *);
extern s32 MemCardCreateFile(s32, u8 *, s32);
extern s32 MemCardOpen(s32, u8 *, s32);
extern s32 MemCardWriteData(void *, s32, s32);
extern void MemCardClose(void);
extern void MemCardSync(s32, s32, s32 *);
extern s32 D_8008A618;
extern u8 D_8008A61C[4];
extern s32 D_8008A63C;
extern s32 D_8008A640;
extern s32 D_8008A644;
extern u8 *D_8008A648;
extern u8 *D_8008A64C;
extern u8 *D_8008A650;
extern u8 D_8008B150[4];
extern s32 D_8008B188;
extern McHdr_80037DC4 D_800A7F2C;
extern u8 D_800A812C[0x80];

s32 func_80037DC4(s32 name, u8 *data, u32 size) {
    s32 bytes;
    u32 left;
    u32 n;
    s32 off;
    u8 *src;
    u8 *p;
    McHdr_80037DC4 *h;

    func_8001651C(D_8008B150, name);
    if (D_8008A618 == 0) {
        return 1;
    }
    bytes = func_800382C0(size);
    if (bytes == -1) {
        D_8008B188 = 7;
        return 1;
    }
    h = &D_800A7F2C;
    D_800A7F2C.magic[0] = 'S';
    h->magic[1] = 'C';
    h->type = 0x13;
    h->blocks = (bytes + 0x1FFF) / 0x2000;
    memset(h->pad44, 0, 0x1C);
    memset(h->title, 0, 0x40);
    func_80037CB4(D_8008A61C, h->title);
    func_80034D4C(h->clut, D_8008A648 + 0x14, 0x20);
    func_80034D4C(h->icon[0], D_8008A648 + 0x40, 0x80);
    func_80034D4C(h->icon[1], D_8008A64C + 0x40, 0x80);
    func_80034D4C(h->icon[2], D_8008A650 + 0x40, 0x80);
    if (func_80037BB8() != 0) {
        return 1;
    }
    D_8008B188 = MemCardDeleteFile(D_8008A63C + D_8008A640, D_8008B150);
    if (D_8008B188 != 0 && D_8008B188 != 5) {
        return 1;
    }
    D_8008B188 = MemCardCreateFile(D_8008A63C + D_8008A640, D_8008B150, h->blocks);
    if (D_8008B188 != 0) {
        return 1;
    }
    D_8008B188 = MemCardOpen(D_8008A63C + D_8008A640, D_8008B150, 2);
    if (D_8008B188 != 0) {
        return 1;
    }
    if (MemCardWriteData(h, 0, 0x200) == 0) {
        goto fail;
    }
    MemCardSync(0, 0, &D_8008B188);
    if (D_8008B188 != 0) {
        goto fail;
    }
    off = 0x200;
    left = size;
    src = data;
    while (left != 0) {
        n = 0x7F;
        p = D_800A812C;
        if (left < n) {
            n = left;
            memset(p, 0, 0x80);
        }
        if (left == size) {
            *(u32 *) D_800A812C = left;
            p += 4;
            n -= 4;
        }
        func_80034D4C(p, src, n);
        D_800A812C[0x7F] = func_80037C20(D_800A812C, 0x7F);
        if (MemCardWriteData(D_800A812C, off, 0x80) == 0) {
            goto fail;
        }
        MemCardSync(0, 0, &D_8008B188);
        off += 0x80;
        if (D_8008B188 != 0) {
            goto fail;
        }
        left -= n;
        src += n;
    }
    MemCardClose();
    MemCardSync(0, 0, &D_8008B188);
    if (D_8008B188 != 0) {
        return 1;
    }
    D_8008A644 = 0;
    return 0;
fail:
    MemCardClose();
    return 1;
}
