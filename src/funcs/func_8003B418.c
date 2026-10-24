#include "common.h"

typedef struct {
    u8 pad0[0xE0];
    s32 cur;
    u32 ptr;
} Ent_8003B418;

extern Ent_8003B418 D_8008234C;
extern s32 D_8008A710;
extern void func_8003B3CC(void);
extern void func_80059D88(s32 v);
extern void VSync(s32 mode);
extern void func_8005A268(u32 p);
extern void func_8005A174(u32 p);

void func_8003B418(s32 v) {
    func_8003B3CC();
    if (v != 0) {
        func_80059D88(0);
        VSync(0);
    }
    func_8005A268(D_8008234C.ptr + 0x5C);
    func_8005A174(D_8008234C.ptr);
    D_8008A710 = 0;
}
