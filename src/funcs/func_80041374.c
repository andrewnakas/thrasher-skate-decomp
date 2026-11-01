#include "common.h"

typedef struct {
    s32 a;
    s32 b;
    u8 pad8[0x2C];
} Slot_80041374;

typedef struct {
    u16 flags;          /* 0x00 */
    u8 pad2[0x10];
    u16 f12;            /* 0x12 */
    u8 pad14[0xC];
    Slot_80041374 slots[1]; /* 0x20 */
} Node_80041374;

typedef struct {
    s32 flags;          /* 0x00 */
    u8 pad4[2];
    u16 f6;             /* 0x06 */
    u8 pad8[6];
    u16 count;          /* 0x0E */
    Node_80041374 *first;   /* 0x10 */
    u8 pad14[0x10];
    u8 *tab;            /* 0x24 */
} Obj_80041374;

extern s32 D_8008B344;
extern s32 D_8008B348;
extern Obj_80041374 *D_8008B34C;
extern u8 *D_8008B350;
extern s32 D_8008B354;

extern void func_80042230(Obj_80041374 *, s32, s32);
extern void func_800416A8(Node_80041374 *);
extern Node_80041374 *func_80041538(Node_80041374 *);
extern void func_800403DC(Obj_80041374 *);
extern void func_80040594(Obj_80041374 *);
extern void func_8004095C(Obj_80041374 *);
extern void func_80042338(Obj_80041374 *);

void func_80041374(Obj_80041374 *o, s32 arg1, s32 flags) {
    Node_80041374 *n;
    s32 i;

    D_8008B348 = flags;
    D_8008B344 = arg1;
    D_8008B34C = o;
    if (flags & 1) {
        func_80042230(o, -0x381, 0);
    }
    D_8008B354 = -1;
    D_8008B34C = o;
    D_8008B350 = o->tab + 0x10;
    if (D_8008B348 & 0x10) {
        for (i = 0; i < o->count; i++) {
            n = *(Node_80041374 **) (o->tab + i * 16 + 0x10);
            if (n != 0) {
                if (!(n->flags & 1)) {
                    func_800416A8(n);
                    n->flags |= 1;
                }
                if (n->f12 != 0) {
                    n->flags &= ~2;
                }
            }
        }
    } else {
        n = o->first;
        do {
            n = func_80041538(n);
        } while (n != 0);
    }
    if (D_8008B348 & 8) {
        func_800403DC(o);
        func_80040594(o);
    }
    if (D_8008B348 & 4) {
        func_8004095C(o);
    }
    if (D_8008B348 & 0x20) {
        s32 j;
        Slot_80041374 *sl;

        n = o->first;
        for (j = 0; j < o->f6; j++) {
            sl = n->slots;
            sl[j].b = 0;
            sl[j].a = 0;
        }
    }
    if (o->flags & 2) {
        func_80042338(o);
    }
}
