#include "common.h"

extern u8 D_8008A8B4;

s32 func_800363F8(void *, s32, s32);
s32 func_800367F4(s32);
void func_80036758(s32);
s32 func_8003663C(s32, s32, s32);
void *func_80034C20(s32);
void func_80034BD8(void *);
s32 func_8004813C(void *);
s32 func_80047C94(void *, s32, s32);
s32 func_80047B28(void *, s32, s32);
s32 func_80047EF0(void *, s32, s32);

s32 func_80048208(void *name, s32 a1, s32 a2) {
    s32 ret = 1;
    s32 h;
    s32 size;
    void *buf;
    s32 type;

    h = func_800363F8(name, ret, 0);
    if (h == 0) {
        return ret;
    }
    size = func_800367F4(h);
    buf = func_80034C20(size);
    if (buf == NULL) {
        func_80036758(h);
        return 1;
    }
    func_8003663C(h, (s32) buf, size);
    func_80036758(h);
    type = func_8004813C(buf);
    h = (s32) buf;
    if (type == 0) {
        return 1;
    }
    switch (type) {
    case 1:
        D_8008A8B4 = 0;
        ret = func_80047C94((void *) h, a1, a2);
        break;
    case 5:
        D_8008A8B4 = 1;
        ret = func_80047C94((void *) h, a1, a2);
        break;
    case 2:
        ret = func_80047B28((void *) h, a1, a2);
        break;
    case 4:
        ret = func_80047EF0((void *) h, a1, a2);
        break;
    case 3:
        break;
    }
    func_80034BD8(buf);
    return ret;
}
