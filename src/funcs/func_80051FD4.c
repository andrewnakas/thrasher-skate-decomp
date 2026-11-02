/* a4 r5: voice slot address spelled D_8008B440 + (v << 4) (the * 16 form gives off+D operand order). */
#include "common.h"

typedef struct Node_80051FD4 {
    u8 *f0;
    u8 pad4[4];
    struct Node_80051FD4 *next;
} Node_80051FD4;

typedef struct {
    s32 voice;
    u8 pad4[8];
} Chan_80051FD4;

typedef struct {
    u16 flags;
    u8 state;
    u8 pad3;
    s32 f4;
    u8 *buf;
    u32 size;
    u8 pad10[4];
    u32 pos;
    u8 pad18[0xC];
    u32 stop;
    u16 f28;
    u16 timer;
    Node_80051FD4 list;
    u8 pad38[0x14];
    Chan_80051FD4 ch[2];
} Strm_80051FD4;

typedef struct {
    u8 pad0[8];
    u8 state;
    u8 pad9[3];
    s32 fC;
    u8 pad10[4];
    u8 *addr;
} Voice_80051FD4;

extern void func_80034BD8();
extern void func_80051AE4(Node_80051FD4 *);
extern void func_80051F3C(u8 *);
extern u8 *D_8008B440;
extern u8 D_800B076C[];

void func_80051FD4(Strm_80051FD4 *a) {
    u32 stereo;
    s32 step;
    s32 v0;
    s32 v1;
    u32 pos;
    u32 e;
    u32 q;
    u32 i;
    s32 d;
    u8 *p;
    Strm_80051FD4 *c;
    Node_80051FD4 *n;
    Node_80051FD4 *next;

    stereo = (a->flags >> 8) & 1;
    step = 0x800;
    if (stereo) {
        step = 0x1000;
    }
    a->timer--;
    if (a->timer != 0) {
        return;
    }
    v0 = a->ch[0].voice;
    v1 = a->ch[1].voice;
    if (a->state == 3 || a->state == 4) {
        if (a->state == 3) {
            a->pos = 0;
            a->state = 4;
        } else {
            pos = a->pos + step;
            a->pos = pos;
            if (pos >= a->size) {
                a->pos = pos - a->size;
            }
        }
        i = 0;
        p = a->buf + a->pos;
        do {
            if (p[1] == 0) {
                ((Voice_80051FD4 *) (D_8008B440 + (a->ch[i].voice << 4)))->addr = p;
            } else {
                ((Voice_80051FD4 *) (D_8008B440 + (a->ch[i].voice << 4)))->addr = D_800B076C;
            }
            ((Voice_80051FD4 *) (D_8008B440 + (a->ch[i].voice << 4)))->state = 6;
            i++;
            p += 0x800;
        } while (i <= stereo);
        if (a->flags & 0x1000) {
            e = a->stop;
            q = a->pos;
            if (q < e) {
                d = e - q;
            } else {
                d = e + a->size - q;
            }
            if (stereo) {
                if (d < 0x1001) {
                    goto set5;
                }
            } else if (d < 0x801) {
            set5:
                a->state = 5;
            }
        }
    } else {
        switch (a->state) {
        case 5:
            a->state = 6;
            break;
        case 6:
            if (a->flags & 2) {
                n = &a->list;
                if (!(a->flags & 0x4000)) {
                    func_80034BD8(a->f4);
                }
                while (n != NULL) {
                    next = n->next;
                    func_80051F3C(n->f0);
                    func_80051AE4(n);
                    n = next;
                }
                a->state = 8;
                ((Voice_80051FD4 *) (D_8008B440 + (v0 << 4)))->fC = 0;
                ((Voice_80051FD4 *) (D_8008B440 + (v0 << 4)))->state = 2;
                if (stereo) {
                    ((Voice_80051FD4 *) (D_8008B440 + (v1 << 4)))->fC = 0;
                    ((Voice_80051FD4 *) (D_8008B440 + (v1 << 4)))->state = 2;
                }
            } else {
                a->state = 0;
            }
            break;
        case 8:
            ((Voice_80051FD4 *) (D_8008B440 + (v0 << 4)))->fC = 0;
            ((Voice_80051FD4 *) (D_8008B440 + (v0 << 4)))->state = 2;
            if (stereo) {
                ((Voice_80051FD4 *) (D_8008B440 + (v1 << 4)))->fC = 0;
                ((Voice_80051FD4 *) (D_8008B440 + (v1 << 4)))->state = 2;
            }
            break;
        }
        ((Voice_80051FD4 *) (D_8008B440 + (v0 << 4)))->addr = D_800B076C;
        if (stereo) {
            ((Voice_80051FD4 *) (D_8008B440 + (v1 << 4)))->addr = D_800B076C;
        }
    }
    a->timer = a->f28;
}
