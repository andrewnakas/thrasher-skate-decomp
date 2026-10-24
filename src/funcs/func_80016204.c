#include "common.h"

typedef struct {
    u8 pad[0xC];
    s32 unkC;
} MemBlock;

s32 func_80016248(MemBlock *);
s32 sprintf(char *, const char *, ...);

void func_80016204(MemBlock *arg0) {
    char buf[0x100];

    if (arg0->unkC != func_80016248(arg0)) {
        sprintf(buf, "ZMEMDMM: DMM memblock corrupt at %x\n", arg0);
    }
}
