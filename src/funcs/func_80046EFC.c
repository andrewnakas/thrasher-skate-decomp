#include "common.h"

extern u32 D_8008B3C0;
extern char D_800A5F84[];
extern char D_8008A898[];
extern char D_8008A8A8[];

s32 func_80036A78(u32, u32, u16);
s32 func_80036B18(u32);
void *func_80034C20(s32);
void func_80036BF4(u32, void *);
u16 func_8004691C(void *, u16, u16, u16, u32);
void func_80034BD8(void *);
char *strcat(char *, const char *);
s32 sprintf(char *, const char *, ...);

u16 func_80046EFC(u16 id, u16 x, u16 y, u16 z, u32 flags) {
    char buf[0x40];
    s32 size;
    void *mem;
    u16 r;

    if (func_80036A78(D_8008B3C0, id, 0) != 0) {
        return 0xFFFF;
    }
    size = func_80036B18(D_8008B3C0);
    if (size == 0 || (mem = func_80034C20(size)) == 0) {
        return 0xFFFF;
    }
    func_80036BF4(D_8008B3C0, mem);
    r = func_8004691C(mem, x, y, z, flags);
    func_80034BD8(mem);
    if (r == 0xFFFF) {
        strcat(D_800A5F84, D_8008A898);
        sprintf(buf, D_8008A8A8, id, id);
        strcat(D_800A5F84, buf);
    }
    return r;
}
