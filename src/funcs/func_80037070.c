#include "common.h"

typedef struct Req_80037070 {
    volatile s32 state;
    s32 file;
    u32 remain;
    u32 off;
    u32 retries;
    u8 *dst;
    u8 loc[4];
    u8 result[8];
    void *cb;
    s32 arg;
    struct Req_80037070 *next;
} Req_80037070;

typedef struct {
    u8 pad0[0xC];
    u32 size;
    u8 pad10[0xC];
    u32 pos;
    u8 pad20[0x40];
} File_80037070;

extern s32 func_80036F58();
extern s32 func_80036F64(Req_80037070 *);
extern void func_8003756C();
extern s32 func_80037884(Req_80037070 *);
extern s32 func_8005CAE8(void);
extern void func_8005CBD8(void *);
extern s32 func_8005CBEC(s32, u8 *, u8 *);
extern s32 func_8005CE5C(s32, s32, u8 *);
extern void func_8005D02C(s32, void *);
extern s32 func_8005D130(void *);
extern void EnterCriticalSection(void);
extern void ExitCriticalSection(void);
extern void VSync(s32);
extern void printf(const char *, ...);
extern s32 D_8008A578;
extern s32 D_8008A598;
extern s32 D_8008A608;
extern u32 D_8008A60C;
extern volatile s32 D_8008A610;
extern s32 D_8008B12C;
extern Req_80037070 *D_8008B130;
extern s32 D_8008B134[1];
extern volatile s32 D_8008B138;
extern s32 D_8008B13C;
extern Req_80037070 *volatile D_8008B140;
extern s32 D_8008B144;
extern File_80037070 D_800A671C[];
extern Req_80037070 D_800A777C[];

s32 func_80037070(s32 file, s32 dst, u32 len, void *cb, s32 arg, s32 *outLen, Req_80037070 **outReq) {
    u8 status[8];
    u8 mode[8];
    s32 got;
    u32 i;
    Req_80037070 *r;
    File_80037070 *f;
    Req_80037070 *p;
    Req_80037070 *q;
    u32 n;
    s32 off;

    if ((func_8005CAE8() & 0xA0) != 0xA0) {
        mode[0] = 0xA0;
        if (func_8005CBEC(0xE, mode, NULL) != 0) {
            VSync(0);
            VSync(0);
            VSync(0);
            VSync(0);
        }
    }
    i = 0;
    while (D_8008A610 != 0) {
        if (D_8008A598 * 10 < i++) {
            printf("Breaking out of wait read ahead buffer - Should never happen\n");
            break;
        }
        VSync(0);
    }
    r = NULL;
    f = &D_800A671C[file];
    *outReq = NULL;
    *outLen = 0;
    n = f->size - f->pos;
    i = 0;
    if (len < n) {
        n = len;
    }
    len = n;
    if (len != 0) {
    EnterCriticalSection();
    i = D_8008B12C;
    off = i * sizeof(Req_80037070);
    while (1) {
        p = (Req_80037070 *) ((u8 *) D_800A777C + off);
        if (p->file == 0) {
            r = p;
            p->retries = 0;
            r->next = NULL;
            if (++D_8008B12C == 40) {
                D_8008B12C = 0;
            }
            break;
        }
        i++;
        off += sizeof(Req_80037070);
        if (i == 40) {
            off = 0;
            i = 0;
        }
        if (i == D_8008B12C) {
            break;
        }
    }
    *outReq = r;
    if (r != NULL) {
    func_8005D02C(func_8005D130(f) + (f->pos >> 11), r->loc);
    r->file = file;
    r->dst = (u8 *) dst;
    r->remain = len;
    r->off = f->pos & 0x7FF;
    r->cb = cb;
    r->arg = arg;
    *outLen += len;
    f->pos += len;
    D_8008B134[0]++;
    q = D_8008B130;
    if (q != NULL) {
        while (q->next != NULL) {
            q = q->next;
        }
        q->next = r;
        r->state = 2;
        i = r->state;
        ExitCriticalSection();
        return i;
    }
    if (file != D_8008B144) {
        if (func_80037884(r) != 0 || (D_8008A608 != 0 && D_8008A610 == 0 && func_80036F64(r) != 0)) {
            D_8008B134[0]--;
            ExitCriticalSection();
            return 0;
        }
    }
    i = 1;
    D_8008B130 = r;
    r->state = i;
    ExitCriticalSection();
    if (D_8008A608 != 0 && D_8008A610 == 0 && D_8008B134[0] == i) {
        File_80037070 *d = &D_800A671C[D_8008B144];

        *d = *f;
        d->pos = (d->pos + 0x800) & ~0x7FF;
        func_80037070(D_8008B144, D_8008A608, D_8008A60C, func_80036F58, 0, &got, &D_8008B140);
        D_8008A610 = 1;
        D_8008B140->remain = (got + 0x7FF) & ~0x7FF;
        D_8008B138 = func_8005D130(D_8008B140->loc);
        D_8008B13C = D_8008B138 + (D_8008B140->remain >> 11) - 1;
    }
    if (func_8005CE5C(1, 0, status) != 0 && !(status[0] & 0x10) && func_8005CBEC(2, r->loc, NULL) != 0) {
        func_8005CBD8(func_8003756C);
        if (func_8005CBEC(6, NULL, r->result) != 0) {
            D_8008A578 = D_8008A598 * 10;
            return 1;
        }
    }
    *outLen = 0;
    f->pos -= len;
    r->file = 0;
    *outReq = NULL;
    D_8008B130 = NULL;
    i = 4;
    } else {
    i = 4;
    }
    }
    return i;
}
