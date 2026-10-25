#include "common.h"

typedef struct {
    u8 pad[0x24];
    volatile s32 a;
    volatile s32 b;
    volatile s32 c;
} S_80033804;

void func_80033804(S_80033804 *p) {
    p->a = 0;
    p->b = 0;
    p->c = 0;
}
