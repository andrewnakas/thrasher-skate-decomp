#include "common.h"

typedef struct {
    s32 f0;
    u8 pad[0x1BC];
} Rec;

extern s32 D_80089F44;
extern Rec *D_80089F48;
extern s32 D_80089F4C;

void *func_80034C20(s32);

void func_80011F84(void) {
    s32 i;

    D_80089F48 = (Rec *)func_80034C20(D_80089F44 * 448);
    memset(D_80089F48, 0, D_80089F44 * 448);
    for (i = 0; i < D_80089F44; i++) {
        D_80089F48[i].f0 = 0;
    }
    D_80089F4C = 0;
}
