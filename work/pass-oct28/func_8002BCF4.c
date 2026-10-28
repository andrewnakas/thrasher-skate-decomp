#include "common.h"

extern void func_8001DB74(void *);

void func_8002BCF4(u8 *a0) {
    u8 **slot;
    s32 i;

    i = *(u16 *) (a0 + 0x24);
    i--;
    slot = (u8 **) (*(u32 *) (a0 + 0x18) + 0xC);
    while (i != -1) {
        if (*slot != 0) {
            func_8001DB74(*slot);
            *slot = 0;
        }
        slot++;
        i--;
    }
}
