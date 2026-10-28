#include "common.h"

typedef struct {
    u8 type;   /* 0x00 */
    u8 unk1;   /* 0x01 */
    s16 unk2;  /* 0x02 */
    u8 pad4[4];
    u8 *unk8;  /* 0x08 */
    u8 *unkC;  /* 0x0C */
} Node_8002CE0C;

extern s16 D_8008AFC4[4];
extern s16 D_8008AFCC[3];
extern s32 D_8008B054;
extern s32 D_8008B058;
extern void func_8002CF58(Node_8002CE0C *);
extern void func_8002CE0C(Node_8002CE0C *);

void func_8002CE0C(Node_8002CE0C *n) {
    s32 v;
    s32 w;
    s32 sa;
    s32 sb;

    if (n == 0) {
        return;
    }
    if (n->type == 0x70) {
        v = *(s16 *) ((u8 *) D_8008AFC4 + n->unk1 * 2) + n->unk2;
        if (v > 0) {
            sa = 1;
        } else if (v < 0) {
            sa = -1;
        } else {
            sa = 0;
        }
        w = *(s16 *) ((u8 *) D_8008AFCC + n->unk1 * 2) + n->unk2;
        if (w > 0) {
            sb = 1;
        } else if (w < 0) {
            sb = -1;
        } else {
            sb = 0;
        }
        D_8008B054 = v;
        D_8008B058 = (s32) n;
        func_8002CF58(n);
        if (sa == 1) {
            if (sb == 1) {
                func_8002CE0C((Node_8002CE0C *) n->unkC);
                func_8002CE0C((Node_8002CE0C *) n->unk8);
            } else {
                func_8002CE0C((Node_8002CE0C *) n->unkC);
            }
        } else if (sa == -1) {
            if (sb == 1) {
                func_8002CE0C((Node_8002CE0C *) n->unk8);
                func_8002CE0C((Node_8002CE0C *) n->unkC);
            } else {
                func_8002CE0C((Node_8002CE0C *) n->unk8);
            }
        } else {
            func_8002CE0C((Node_8002CE0C *) n->unk8);
            if (sb != 1) {
                func_8002CE0C((Node_8002CE0C *) n->unkC);
            }
        }
    } else if (n->type == 0x6C) {
        func_8002CF58(n);
    }
}
