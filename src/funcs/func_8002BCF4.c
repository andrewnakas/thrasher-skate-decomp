#include "common.h"

typedef struct {
    u8 pad0[0xC];
    s32 handle;
} Slot10;

typedef struct {
    u8 pad0[0x18];
    Slot10 *slots;
    u8 pad1C[0x8];
    u16 count;
} SlotOwner;

void func_8001DB74(s32);

void func_8002BCF4(SlotOwner *arg0) {
    Slot10 *s;
    s32 n;

    n = arg0->count;
    s = arg0->slots;
    while (--n != -1) {
        if (s->handle != 0) {
            func_8001DB74(s->handle);
            s->handle = 0;
        }
        s++;
    }
}
