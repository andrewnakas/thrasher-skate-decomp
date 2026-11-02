#include "common.h"

typedef struct Req_80053F44 {
    volatile u8 state;
    volatile u8 retries;
    u8 pad2[2];
    void *buf;
    u8 loc[4];
    volatile u32 size;
    volatile s32 offset;
    volatile u8 result[8];
    void (*volatile cb)(s32);
    struct Req_80053F44 *volatile next;
} Req_80053F44;

typedef struct Voice_80053F44 {
    u8 id;
    u8 pad1[3];
    s32 voice;
    s32 addr;
} Voice_80053F44;

typedef struct Stream_80053F44 {
    u16 flags;
    u8 state;
    u8 pad3;
    volatile u32 size;
    u8 pad8[0x34];
    Voice_80053F44 voices[2];
} Stream_80053F44;

extern Req_80053F44 *D_8008A9F4;
extern s32 D_8008A9FC;
/* D_8008A934 is read as D_8008A938[-1]: a symbol-minus-offset operand is not
   gp-relative under maspsx, giving the game's unsplit lui/lw pair. */
extern s32 D_8008A938[2];
extern u8 D_80010920[];
extern u8 D_8008AA00[];
extern Stream_80053F44 D_800B134C;
extern s32 D_800B139C[];
extern u8 D_800B146C[];
extern s8 D_800B1C5D[];

extern void func_8005CBD8(void (*)());
extern s32 func_8005CBEC(s32, u8 *, u8 *);
extern void func_8005CD28(s32, s32);
extern void func_8005CFA8(void *, s32);
extern void func_8005D00C(s32);
extern s32 func_8005D130(u8 *);
extern void func_8005D02C(s32, u8 *);
extern void SpuIsTransferCompleted(s32);
extern void SpuSetTransferStartAddr(s32);
extern void SpuRead(u8 *, s32);

void func_80053F44(u8 status, u8 *result) {
    u32 hdr[3];
    s32 err;
    s32 fatal;
    s32 addr;
    u32 n;
    u32 sz;

    func_8005CBD8(0);
    D_8008A9FC = D_8008A938[-1] * 10;
    if (D_8008A9F4->size != 0) {
        if (D_8008A9F4->result[0] & 0x10) {
            err = 1;
            fatal = err;
        } else {
            err = 0;
            fatal = err;
            if (status == 1) {
                func_8005CFA8(hdr, 3);
                func_8005D00C(err);
                addr = func_8005D130((u8 *) hdr);
                if (addr == func_8005D130(D_8008A9F4->loc)) {
                    func_8005D02C(func_8005D130(D_8008A9F4->loc) + 1, D_8008A9F4->loc);
                    n = D_8008A9F4->size;
                    if (n > 0x800) {
                        n = 0x800;
                    }
                    if (n != 0) {
                        if (n != 0x800) {
                            printf(D_80010920, D_8008AA00, 0x4A1);
                            exit(1);
                        }
                        func_8005CFA8(D_800B146C, 0x200);
                    }
                } else {
                    err = 1;
                }
            } else if (status == 5 || (D_8008A9F4->result[0] & 4)) {
                err = 1;
            }
        }
        if (!err) {
            {
                u32 m;
                Stream_80053F44 *st;
                st = &D_800B134C;
                m = D_8008A9F4->offset + 0x800;
                sz = ((u32 *) st)[1];
                if ((D_800B134C.flags & 0x200) ? (m == sz >> 1) : (m == sz)) {
                    D_800B1C5D[0] = 3;
                }
            }
            if (!(D_8008A9F4->state & 2)) {
                addr = D_800B134C.voices[0].addr + D_8008A9F4->offset;
                if (D_800B134C.flags & 0x200) {
                    D_8008A9F4->state |= 2;
                } else {
                    D_8008A9F4->offset += 0x800;
                }
            } else {
                addr = D_800B139C[0] + D_8008A9F4->offset;
                D_8008A9F4->state &= ~2;
                D_8008A9F4->offset += 0x800;
            }
            D_8008A9F4->size -= 0x800;
            SpuIsTransferCompleted(1);
            SpuSetTransferStartAddr(addr);
            SpuRead(D_800B146C, 0x800);
        } else {
            if (!fatal) {
                if (++D_8008A9F4->retries < 5) {
                    func_8005CBEC(2, D_8008A9F4->loc, 0);
                    goto restart;
                }
            }
            while (D_8008A9F4 != NULL) {
                if (D_8008A9F4->cb != NULL) {
                    D_8008A9F4->cb(1);
                }
                D_8008A9F4->state = 0;
                D_8008A9F4->size = 0;
                D_8008A9F4->cb = NULL;
                D_8008A9F4 = D_8008A9F4->next;
            }
            D_8008A9FC = 0;
            if (!fatal) {
                func_8005CD28(7, 0);
            }
            return;
        }
    }
    if (D_8008A9F4->size != 0) {
        func_8005CBD8(func_80053F44);
        return;
    }
    D_8008A9F4->state = 0;
    if (D_8008A9F4->cb != NULL) {
        D_8008A9F4->cb(0);
    }
    D_8008A9F4 = D_8008A9F4->next;
    if (D_8008A9F4 != NULL) {
        func_8005CBEC(2, D_8008A9F4->loc, 0);
    restart:
        func_8005CBD8(func_80053F44);
        func_8005CBEC(6, 0, (u8 *) D_8008A9F4->result);
        return;
    }
    func_8005CD28(7, 0);
    D_8008A9FC = 0;
}
