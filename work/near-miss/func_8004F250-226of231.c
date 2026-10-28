#include "common.h"

extern s32 D_8008A984;
extern s32 D_8008A988;
extern s32 D_8008A998;
extern s32 D_8008A99C;
extern char D_8008A9A0[];
extern u8 D_80082940[0x10];
extern char D_80010888[];
extern u8 D_800B066C[];

extern s32 func_800363F8(s32, s32, s32);
extern s32 func_8003663C(s32, void *, s32);
extern s32 func_800366D0(s32, s32, s32);
extern s32 func_80034C14(void);
extern s32 func_80034C20(s32);
extern s32 func_8004F5EC(s32, s32, u16 *);
extern s32 func_800366F0(s32);
extern s32 func_80036758(s32);
extern s32 func_80034BD8(s32);
extern s32 SpuMalloc(s32);
extern s32 SpuIsTransferCompleted(s32);
extern void VSync(s32);
extern void SpuSetTransferStartAddr(s32);
extern void SpuRead(void *, s32);
extern s32 printf(char *, char *, s32);
extern void exit(s32);

typedef struct Node_8004F250 {
    s32 unk0;
    s32 unk4;
} Node_8004F250;

typedef struct Entry_8004F250 {
    u16 unk0;
    u8 pad2[0x1E];
    s32 unk20;
    Node_8004F250 *unk24;
} Entry_8004F250;

typedef struct Voice_8004F250 {
    s32 unk0;
    u8 pad4[4];
    s32 unk8;
    s32 unkC;
} Voice_8004F250;

s32 func_8004F250(s32 a0, s32 a1, u16 *a2) {
    u8 buf[0x4000];
    Entry_8004F250 *e;
    Voice_8004F250 *v;
    Node_8004F250 *node;
    s32 ret;
    s32 want;
    s32 got;
    s32 addr;
    s32 ptr;
    s32 handle;
    s32 val;
    s32 i;
    s32 wait;

    *a2 = 0xFFFF;
    handle = func_800363F8(a0, 1, 0);
    if (handle == 0) {
        ret = 1;
        return ret;
    }

    func_8003663C(handle, buf, 0x800);
    want = *(s32 *) (buf + 0xC);
    func_800366D0(handle, 0, 0);
    val = func_80034C14();
    got = func_80034C20(want);
    if (got == 0) {
        ret = 3;
        goto close;
    }
    if (func_8003663C(handle, (void *) got, want) == 0) {
        ret = 2;
        func_80034BD8(val);
        goto close;
    }
    ret = func_8004F5EC(got, 0, a2);
    if (ret != 0) {
        func_80034BD8(val);
        goto close;
    }

    v = (Voice_8004F250 *) &D_800B066C[(*a2) << 4];
    v->unk8 = val;
    v->unkC = func_800366F0(handle) << 11;
    e = (Entry_8004F250 *) got;

    if (a1 == 0) {
        i = 0;
        if ((u32) ret < (u32) e->unk20) {
            do {
                *(s32 *) ((u8 *) e->unk24 + i * 8) += v->unkC;
                i++;
            } while ((u32) i < (u32) e->unk20);
        }
        D_8008A988 += i;
        goto done;
    }

    i = 0;
    want = 0;
    if ((u32) ret < (u32) e->unk20) {
        node = e->unk24;
        do {
            want += node->unk4;
            node++;
            i++;
        } while ((u32) i < (u32) e->unk20);
    }

    if (want == 0) {
        goto fixup;
    }

    want = (want + 0x3F) & ~0x3F;
    ptr = SpuMalloc(want);
    if (ptr == -1) {
        printf(D_80010888, D_8008A9A0, 0xC9);
        exit(1);
    }
    addr = ptr;

    val = D_8008A99C + want;
    D_8008A99C = val;
    D_8008A998 = 0x7EFF0 - *(s32 *) D_80082940 - val;

    wait = 0x12C;
    do {
        if (SpuIsTransferCompleted(0)) {
            break;
        }
        if (--wait == 0) {
            break;
        }
        VSync(0);
    } while (1);

    func_800366D0(handle, e->unk24->unk0, 0);

    if (want != 0) {
        do {
            ret = 0x4000;
            if ((u32) want < 0x4000) {
                ret = want;
            }
            func_8003663C(handle, buf, 0x4000);
            wait = 0x12C;
            do {
                if (SpuIsTransferCompleted(0)) {
                    break;
                }
                if (--wait == 0) {
                    break;
                }
                VSync(0);
            } while (1);
            SpuSetTransferStartAddr(addr);
            SpuRead(buf, ret);
            wait = 0x12C;
            do {
                if (SpuIsTransferCompleted(0)) {
                    break;
                }
                if (--wait == 0) {
                    break;
                }
                VSync(0);
            } while (1);
            want -= ret;
            addr += ret;
        } while (want != 0);
    }

fixup:
    if (e->unk20 != 0) {
        i = 0;
        do {
            node = e->unk24 + i;
            node->unk0 = ptr;
            ptr += node->unk4;
            i++;
        } while ((u32) i < (u32) e->unk20);
    }
    D_8008A984 += e->unk20;
    v->unk0 |= 2;

done:
    func_80036758(handle);
    return 0;

close:
    func_80036758(handle);
    return ret;
}
