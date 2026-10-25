#include "common.h"

extern s32 func_80019630(u32);
extern s32 func_80017740(u32, s32);
extern s32 func_8001794C(u32, s32);
extern s32 func_80018118(u32, s32);
extern s32 func_8001974C(u32, s32);

s32 func_80019570(u16 id) {
    s32 r;
    u16 t;

    r = func_80019630(id);
    if (r != 0) {
        return r;
    }
    t = id & 0xE000;
    if (t == 0) {
        return func_80017740(id, 0);
    }
    if (t == 0x4000 || t == 0x6000 || t == 0xC000) {
        return func_8001794C(id, 0);
    }
    if (t == 0x8000) {
        return func_80018118(id, 0);
    }
    if (t == 0xA000) {
        return func_8001974C(id, 0);
    }
    return 0;
}
