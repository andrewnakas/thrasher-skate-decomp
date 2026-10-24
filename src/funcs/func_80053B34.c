#include "common.h"

extern void EnterCriticalSection(void);
extern void ExitCriticalSection(void);
extern u8 D_800B13AC[];
extern s32 D_8008B450;
extern void *D_8008A9F4;

typedef struct Node_80053B34 {
    u8 pad0[4];
    void *unk4;
    u8 pad8[4];
    s32 unkC;
    u8 pad10[0xC];
    s32 unk1C;
    struct Node_80053B34 *unk20;
} Node_80053B34;

void func_80053B34(void *a0) {
    Node_80053B34 *p;
    u8 *r;
    u32 i;

    EnterCriticalSection();

    for (p = (Node_80053B34 *) D_8008A9F4; p; p = p->unk20) {
        if (p->unk4 == a0) {
            p->unkC = 0;
            p->unk1C = 0;
        }
    }

    ExitCriticalSection();

    for (i = 0, r = D_800B13AC; i < 2; i++, r += 0x14) {
        if (a0 == (void *) r) {
            *(s32 *) (r + 4) = 0;
            D_8008B450 = i;
            break;
        }
    }
}
