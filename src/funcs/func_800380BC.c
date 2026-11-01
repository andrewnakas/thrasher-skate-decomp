#include "common.h"

extern s32 D_8008A618;
extern s32 D_8008A63C;
extern s32 D_8008A640;
extern s32 D_8008B188;
extern u8 D_8008B150[8];
extern u8 D_800A7F2C[];
extern u8 D_800A812C[];

void func_8001651C(u8 *, u8 *);
s32 func_80037BB8(void);
s32 MemCardOpen(s32, u8 *, s32);
s32 MemCardReadData(u8 *, s32, s32);
s32 MemCardSync(s32, s32 *, s32 *);
void MemCardClose(void);
void func_80034D4C(u8 *, u8 *, s32);
s32 func_80037C20(u8 *, s32);

s32 func_800380BC(u8 *name, u8 *dst, s32 maxlen) {
    s32 off;
    s32 remaining;
    s32 blk;
    s32 try;
    s32 n;
    s32 len;
    u8 *buf;
    u8 *out;

    func_8001651C(D_8008B150, name);
    if (D_8008A618 == 0) {
        goto fail_ret;
    }
    if (func_80037BB8() != 0) {
        return 1;
    }
    D_8008B188 = MemCardOpen(D_8008A63C + D_8008A640, D_8008B150, 1);
    if (D_8008B188 != 0) {
        return 1;
    }
    if (MemCardReadData(D_800A7F2C, 0, 0x200) == 0) {
        MemCardClose();
        goto fail_ret;
    }
    MemCardSync(0, 0, &D_8008B188);
    if (D_8008B188 != 0) {
        MemCardClose();
        goto fail_ret;
    }
    off = 0x200;
    out = dst;
    remaining = 1;
    blk = 0;
    do {
        try = 0;
    retry:
        buf = D_800A812C;
        len = 0x80;
        if (MemCardReadData(buf, off, len) == 0) {
            goto fail;
        }
        MemCardSync(0, 0, &D_8008B188);
        if (D_8008B188 != 0) {
            goto fail;
        }
        off += 0x80;
        n = 0x7F;
        if (blk == 0) {
            remaining = *(s32 *) D_800A812C;
            buf += 4;
            if (maxlen < remaining) {
                remaining = maxlen;
            }
            n = 0x7B;
        }
        if (remaining < 0x7F) {
            n = remaining;
        }
        func_80034D4C(out, buf, n);
        if ((u8) func_80037C20(D_800A812C, 0x7F) == D_800A812C[0x7F]) {
            goto ok;
        }
        off -= len;
        if (++try < 2) {
            goto retry;
        }
    fail:
        MemCardClose();
        goto fail_ret;
    ok:
        remaining -= n;
        out += n;
        blk++;
    } while (remaining > 0);
    MemCardClose();
    MemCardSync(0, 0, &D_8008B188);
    if (D_8008B188 == 0) {
        return 0;
    }
fail_ret:
    return 1;
}
