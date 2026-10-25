#include "common.h"

typedef struct {
    u8 pad0[0x608];
    s16 f608;
    u8 pad1[0x8A];
    s16 f694;
} S_80024D6C;

extern s32 D_8008A2BC;
extern s32 D_8008AF44;
extern s32 D_8008AF74;
extern void func_80024720(void);

void func_80024D6C(S_80024D6C *self) {
    s32 idx;

    func_80024720();
    idx = D_8008A2BC;
    self->f608 = 1;
    self->f694 = 1;
    (&D_8008AF44)[idx] = 0;
    (&D_8008AF74)[idx] = 0;
}
