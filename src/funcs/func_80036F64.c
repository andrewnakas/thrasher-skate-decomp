#include "common.h"

/* CD stream window: set from the read callback, so re-read every time. */
extern volatile s32 D_8008B138;
extern volatile s32 D_8008B13C;
extern u32 D_8008A60C;
extern s32 D_8008A608;

extern s32 func_8005D130(u8 *);
extern void func_80034D4C(u32, s32, u32);
extern void func_8005D02C(s32, u8 *);

typedef struct {
    s32 f0;
    s32 f4;
    u32 len;            /* 0x08 */
    u32 off;            /* 0x0C */
    u8 pad10[4];
    u32 dst;            /* 0x14 */
    u8 ring[0xC];       /* 0x18 */
    void (*cb)(void *, s32, s32);   /* 0x24 */
    s32 arg;            /* 0x28 */
} Req_80036F64;

s32 func_80036F64(Req_80036F64 *s) {
    s32 pos;
    u32 off;
    u32 len;
    u32 rem;
    s32 lo;
    s32 hi;

    pos = func_8005D130(s->ring);
    if (pos < D_8008B138) {
        return 0;
    }
    if (D_8008B13C < pos) {
        return 0;
    }
    off = s->off;
    lo = D_8008B138;
    hi = D_8008B13C; /* read and dropped, as in the game */
    len = s->len;
    off += (pos - lo) << 11;
    rem = D_8008A60C - off;
    if (rem < len) {
        len = rem;
    }
    func_80034D4C(s->dst, D_8008A608 + off, len);
    s->len -= len;
    if (s->len != 0) {
        s->off = 0;
        s->dst += len;
        func_8005D02C(D_8008B13C + 1, s->ring);
        return 0;
    }
    s->f0 = 0;
    s->f4 = 0;
    if (s->cb != 0) {
        s->cb(s, s->arg, s->f0);
    }
    return 1;
}
