#include "common.h"

typedef struct {
    u8 pad0[0x18];
    u32 t_addr;
    u8 pad1C[0x30 - 0x1C];
    u32 s_addr;
    u32 s_size;
} Hdr_8003A5A4;

extern Hdr_8003A5A4 *D_8008A6B0;
extern char D_8008A6B4[];
extern char D_8008A6C4[];
extern s32 func_800363F8(char *name, s32 a, s32 b);
extern s32 func_8003663C(s32 a, s32 b, s32 c);
extern u32 func_80034C14(void);
extern s32 func_800367F4(s32 a);
extern void func_80036758(s32 a);
extern s32 func_8005CB70(void);
extern void func_8005A760(void *p);
extern void func_8005A234(void *p);
extern s32 ReadGeomScreen(void);
extern void ReadGeomOffset(s32 *x, s32 *y);
extern void func_80037D50(void);
extern void SpuQuit(void);
extern void func_8005ED48(void);
extern void func_80059AB0(s32 a);
extern void func_800594FC(void);
extern void EnterCriticalSection(void);
extern void Exec(void *p, s32 a, s32 b);
extern void func_8005952C(void);
extern void func_8005CB04(s32 a);
extern void func_800361F0(s32 a);
extern void func_80037D10(void);
extern void func_8005ED28(void);
extern void SpuStart(void);
extern void SetGeomOffset(s32 x, s32 y);
extern void SetGeomScreen(s32 a);
extern void SetDefDispEnv(void *p, s32 a, s32 b, s32 c, s32 d);
extern void SetDefDrawEnv(void *p, s32 a, s32 b, s32 c, s32 d);
extern void func_8005A268(void *p);
extern void func_8005A174(void *p);
extern void func_80059CF0(s32 a);
extern s32 printf(const char *fmt, ...);

s32 func_8003A5A4(char *name) {
    u8 draw1[0x5C];
    u8 disp1[0x14];
    u8 draw2[0x5C];
    u8 disp2[0x14];
    s32 x;
    s32 y;
    s32 r;
    s32 screen;
    Hdr_8003A5A4 *h;

    r = func_800363F8(name, 1, 0);
    if (r == 0) {
        printf(D_8008A6B4, name);
        return 0;
    }
    if (func_8003663C(r, (s32) D_8008A6B0, 0x800) == 0) {
        goto fail;
    }
    h = D_8008A6B0;
    h->s_addr = 0x801FD000;
    h->s_size = 0;
    if (h->t_addr < func_80034C14()) {
        printf("PsxMovie: Execution address too low: ExecAddr=%x, MemBase=%x\n", D_8008A6B0->t_addr, func_80034C14());
        return 0;
    }
    if (func_8003663C(r, D_8008A6B0->t_addr, func_800367F4(r) - 0x800) == 0) {
        goto fail;
    }
    func_8005CB70();
    func_80036758(r);
    func_8005A760(disp1);
    func_8005A234(draw1);
    screen = ReadGeomScreen();
    ReadGeomOffset(&x, &y);
    func_80037D50();
    SpuQuit();
    func_8005ED48();
    func_80059AB0(1);
    func_800594FC();
    EnterCriticalSection();
    Exec((u8 *) D_8008A6B0 + 0x10, 1, 0);
    func_8005952C();
    func_8005CB04(0);
    func_800361F0(1);
    func_80037D10();
    func_8005ED28();
    SpuStart();
    SetGeomOffset(x, y);
    SetGeomScreen(screen);
    SetDefDispEnv(disp2, 0, 0, 0, 0);
    SetDefDrawEnv(draw2, 0, 0, 0, 0);
    func_8005A268(disp2);
    func_8005A174(draw2);
    func_8005A268(disp1);
    func_8005A174(draw1);
    func_80059CF0(1);
    return D_8008A6B0->t_addr;
fail:
    printf(D_8008A6C4, name);
    func_80036758(r);
    return 0;
}
