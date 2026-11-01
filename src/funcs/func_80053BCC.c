#include "common.h"

typedef struct Req_80053BCC {
    u8 unk0;
    u8 pad1[3];
    void *buf;
    u8 loc[4];
    u32 size;
    s32 dest;
    u8 result[8];
    s32 unk1C;
    struct Req_80053BCC *next;
} Req_80053BCC;

typedef struct Buf_80053BCC {
    s32 base;
    u32 end;
    u8 pad8[4];
    s32 sector;
    u32 pos;
} Buf_80053BCC;

extern Req_80053BCC *D_8008A9F4;
extern s32 D_8008A9FC;
/* D_8008A934 is read as D_8008A938[-1]: a symbol-minus-offset operand is not
   gp-relative under maspsx, giving the game's unsplittable lui/lw pair. */
extern s32 D_8008A938[2];
extern u8 D_80010920[];
extern u8 D_8008AA00[];

extern void EnterCriticalSection(void);
extern void ExitCriticalSection(void);
extern Req_80053BCC *func_80053EA8(void);
extern void func_8005D02C(s32, u8 *);
extern s32 func_8005CE5C(s32, s32, u8 *);
extern s32 func_8005CBEC(s32, u8 *, u8 *);
extern void func_8005CBD8(void (*)());
extern void func_80053F44();

s32 func_80053BCC(Buf_80053BCC *b, s32 dest, u32 len, s32 arg3, u32 *outSize, Req_80053BCC **outReq) {
    u8 mode[8];
    u8 status[8];
    Req_80053BCC *r;
    Req_80053BCC *p;
    u32 n;
    u32 sectors;
    u32 bytes;
    s32 ret;

    *outReq = NULL;
    *outSize = 0;
    n = b->end - b->pos;
    ret = 0;
    if (len < n) {
        n = len;
    }
    len = n;
    if (len == 0) {
        goto end;
    }
    EnterCriticalSection();
    r = func_80053EA8();
    *outReq = r;
    if (r == NULL) {
        printf(D_80010920, D_8008AA00, 0x42A);
        exit(1);
    }
    func_8005D02C(b->base + b->sector, r->loc);
    (*outReq)->buf = b;
    (*outReq)->dest = dest;
    (*outReq)->size = len;
    (*outReq)->unk1C = arg3;
    sectors = len >> 11;
    if (sectors == 0) {
        sectors = 1;
    }
    bytes = sectors << 11;
    *outSize = bytes;
    b->pos += bytes;
    b->sector += sectors;
    if (D_8008A9F4 != NULL) {
        p = D_8008A9F4;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = *outReq;
        ExitCriticalSection();
        ret = 2;
    } else {
        D_8008A9F4 = *outReq;
        ExitCriticalSection();
        if (func_8005CE5C(1, 0, status) != 0 && !(status[0] & 0x10)) {
            mode[0] = 0xA0;
            if (func_8005CBEC(0xE, mode, 0) == 0) {
                printf(D_80010920, D_8008AA00, 0x442);
                exit(1);
            }
            if (func_8005CBEC(2, (*outReq)->loc, 0) == 0) {
                printf(D_80010920, D_8008AA00, 0x444);
                exit(1);
            }
            func_8005CBD8(func_80053F44);
            if (func_8005CBEC(6, 0, (*outReq)->result) == 0) {
                printf(D_80010920, D_8008AA00, 0x447);
                exit(1);
            }
            D_8008A9FC = D_8008A938[-1] * 10;
            ret = 3;
        } else {
            *outSize = 0;
            ret = 1;
            (*outReq)->unk0 = 0;
            b->pos -= bytes;
            b->sector -= sectors;
            *outReq = NULL;
            D_8008A9F4 = NULL;
        }
    }
end:
    return ret;
}
