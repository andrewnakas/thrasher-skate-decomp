#include "common.h"

typedef struct {
    s32 addr;
    s32 size;
} Smp_4F250;

typedef struct {
    u8 pad0[0x20];
    u32 count;
    Smp_4F250 *tab;
} Bank_4F250;

typedef struct {
    s32 flags;
    u8 pad4[4];
    s32 mark;
    s32 base;
} Slot_4F250;

typedef struct {
    u8 pad0[0xC];
    s32 size;
    u8 pad10[0x4000 - 0x10];
} Buf_4F250;

s32 SpuIsTransferCompleted(s32);
s32 SpuMalloc(s32);
void SpuRead(void *, u32);
void SpuSetTransferStartAddr(s32);
void VSync(s32);
void exit(s32);
s32 printf(const char *, ...);
void func_80034BD8(s32);
s32 func_80034C14(void);
void *func_80034C20(s32);
s32 func_800363F8(u8 *, s32, s32);
s32 func_8003663C(s32, void *, s32);
void func_800366D0(s32, s32, s32);
s32 func_800366F0(s32);
void func_80036758(s32);
u32 func_8004F5EC(Bank_4F250 *, s32, u16 *);
extern char D_80010888[];
extern s32 D_80082944[1];
extern s32 D_8008A984;
extern s32 D_8008A988;
extern s32 D_8008A998;
extern s32 D_8008A99C;
extern char D_8008A9A0[];
extern Slot_4F250 D_800B066C[];

u32 func_8004F250(u8 *name, s32 upload, u16 *id) {
    Buf_4F250 buf;
    s32 f;
    s32 mark;
    Bank_4F250 *hdr;
    Bank_4F250 *b;
    Slot_4F250 *e;
    u32 ret;
    u32 i;
    s32 total;
    u32 chunk;

    *id = 0xFFFF;
    f = func_800363F8(name, 1, 0);
    if (f != 0) {
        func_8003663C(f, &buf, 0x800);
        total = buf.size;
        func_800366D0(f, 0, 0);
        mark = func_80034C14();
        hdr = func_80034C20(total);
        if (hdr != NULL) {
            if (func_8003663C(f, hdr, total) != 0) {
                ret = func_8004F5EC(hdr, 0, id);
                if (ret == 0) {
                    e = &D_800B066C[*id];
                    e->mark = mark;
                    e->base = func_800366F0(f) << 11;
                    b = hdr;
                    if (upload) {
                        total = 0;
                        for (i = 0; i < b->count; i++) {
                            total += b->tab[i].size;
                        }
                        if (total != 0) {
                            total = (total + 0x3F) & ~0x3F;
                            upload = SpuMalloc(total);
                            if (upload == -1) {
                                printf(D_80010888, D_8008A9A0, 0xC9);
                                exit(1);
                            }
                            D_8008A99C += total;
                            D_8008A998 = 0x7EFF0 - D_8008A99C - D_80082944[-1];
                            i = 300;
                            while (SpuIsTransferCompleted(0) == 0 && --i != 0) {
                                VSync(0);
                            }
                            /* the game reuses the upload/hdr slots for addr/dst */
                            hdr = (Bank_4F250 *) upload;
                            func_800366D0(f, b->tab[0].addr, 0);
                            while (total != 0) {
                                chunk = 0x4000;
                                if ((u32) total < 0x4000) {
                                    chunk = total;
                                }
                                func_8003663C(f, &buf, 0x4000);
                                i = 300;
                                while (SpuIsTransferCompleted(0) == 0 && --i != 0) {
                                    VSync(0);
                                }
                                SpuSetTransferStartAddr((s32) hdr);
                                SpuRead(&buf, chunk);
                                i = 300;
                                while (SpuIsTransferCompleted(0) == 0 && --i != 0) {
                                    VSync(0);
                                }
                                total -= chunk;
                                hdr = (Bank_4F250 *) ((u8 *) hdr + chunk);
                            }
                            for (i = 0; i < b->count; i++) {
                                b->tab[i].addr = upload;
                                upload += b->tab[i].size;
                            }
                        }
                        D_8008A984 += b->count;
                        e->flags |= 2;
                    } else {
                        for (i = 0; i < b->count; i++) {
                            b->tab[i].addr += e->base;
                        }
                        D_8008A988 += i;
                    }
                    func_80036758(f);
                    return 0;
                }
            } else {
                ret = 2;
            }
            func_80034BD8(mark);
        } else {
            ret = 3;
        }
        func_80036758(f);
    } else {
        ret = 1;
    }
    return ret;
}
