#include "common.h"

typedef struct Req_8003756C {
    s32 state;
    s32 f4;
    u32 remain;
    u32 off;
    u32 retries;
    u8 *dst;
    u8 loc[4];
    u8 result[8];
    void (*cb)(struct Req_8003756C *, s32, s32);
    s32 arg;
    struct Req_8003756C *next;
} Req_8003756C;

extern void func_80034D4C(void *, void *, s32);
extern void func_80045828(void);
extern void func_8005CBD8(void *);
extern s32 func_8005CBEC(s32, u8 *, u8 *);
extern void func_8005CD28(s32, s32);
extern void func_8005CFA8(void *, s32);
extern void func_8005D00C(s32);
extern void func_8005D02C(s32, void *);
extern s32 func_8005D130(void *);
extern s32 D_8008A578;
extern volatile s32 D_8008A590;
extern s32 D_8008A598;
extern Req_8003756C *D_8008B130;
extern s32 D_8008B134;
extern u8 D_800A6EFC[];

void func_8003756C(u8 intr) {
    u32 loc[3];
    Req_8003756C *r;
    s32 err;
    u32 n;
    s32 cmd;
    u32 off;

    func_80045828();
    func_8005CBD8(NULL);
    r = D_8008B130;
    D_8008A578 = D_8008A598 * 10;
    err = 0;
    if (r->state != 1) {
        goto done;
    }
    if (r->result[0] & 0x10) {
        err = 1;
        goto fail;
    }
    if (intr == 1) {
        func_8005CFA8(loc, 3);
        func_8005D00C(0);
        if (func_8005D130(loc) != func_8005D130(r->loc)) {
            goto fail;
        }
        func_8005D02C(func_8005D130(r->loc) + 1, r->loc);
        n = 0x800 - r->off;
        if (r->remain < n) {
            n = r->remain;
        }
        if (n != 0) {
            if (n == 0x800) {
                func_8005CFA8(r->dst, 0x200);
            } else {
                func_8005CFA8(D_800A6EFC, 0x200);
                D_8008A590 = func_8005D130(loc);
                func_8005D00C(0);
                func_80034D4C(r->dst, D_800A6EFC + r->off, n);
            }
            r->dst += n;
            off = r->off + n;
            r->off = off;
            r->remain -= n;
            if (off == 0x800) {
                r->off = 0;
            }
        }
    } else if (intr == 5 || (r->result[0] & 4)) {
    fail:
        r->state = 4;
    }
    if (r->state == 4) {
        if (err == 0 && ++r->retries < 3) {
            r->state = 1;
            func_8005CBEC(2, r->loc, NULL);
            func_8005CBD8(func_8003756C);
            cmd = 6;
            goto issue;
        }
    done:
        r->remain = 0;
    }
    if (r->remain != 0) {
        func_8005CBD8(func_8003756C);
        return;
    }
    *(s32 *) r = 0;
    r->f4 = 0;
    D_8008B134--;
    if (r->cb != NULL) {
        func_8005D00C(0);
        r->cb(r, r->arg, r->state);
    }
    if (err == 0) {
        r = r->next;
        D_8008B130 = r;
        if (r != NULL) {
            r->state = 1;
            func_8005CBEC(2, r->loc, NULL);
            func_8005CBD8(func_8003756C);
            cmd = 0x1B;
        issue:
            func_8005CBEC(cmd, NULL, r->result);
            return;
        }
        D_8008A578 = 0;
        func_8005CD28(7, 0);
        return;
    }
    while ((D_8008B130 = D_8008B130->next) != NULL) {
        D_8008B130->f4 = 0;
        if (D_8008B130->cb != NULL) {
            D_8008B130->cb(D_8008B130, D_8008B130->arg, 4);
        }
    }
    D_8008A578 = 0;
}
