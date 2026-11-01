#include "common.h"

typedef struct {
    s32 f0;
    u8 pad4[0x1C];
} Ent20_25544;

typedef struct {
    s32 f0;
    u8 pad4[0x24];
} Ent28_25544;

typedef struct {
    u32 count;
    u8 pad4[0xAF8];
    Ent20_25544 a[(0x1020 - 0xAFC) / 0x20];
    u8 pad1018[0x4];
    Ent28_25544 b[8];
} World_25544;

void func_80024720(void);
extern s32 D_8008A2BC;
extern s32 D_8008A2C8;
extern s32 D_8008A2CC;
extern s32 D_8008A2D0;
extern s32 D_8008A2D4;
extern s32 D_8008A2D8;
extern s32 D_8008A2DC;
extern s32 D_8008A2E0;
extern s32 D_8008A2E4;
extern s32 D_8008A2E8;
extern s32 D_8008A2EC;
extern s32 D_8008A2F0;
extern s32 D_8008A2F4;
extern s32 D_8008A2F8;
extern s32 D_8008A2FC;
extern s32 D_8008A300;
extern s32 D_8008A304;
extern s32 D_8008A308;
extern s32 D_8008AF3C[2];

void func_80025544(World_25544 *w) {
    u32 i;

    func_80024720();
    w->b[D_8008A2C8].f0 = 0x10000;
    w->b[D_8008A2D0].f0 = 0x10000;
    w->b[D_8008A2CC].f0 = 0x10000;
    w->b[D_8008A2D4].f0 = 0x10000;
    w->b[D_8008A2D8].f0 = 0x10000;
    w->b[D_8008A2DC].f0 = 0x10000;
    w->a[D_8008A300].f0 = 0x33333;
    w->a[D_8008A304].f0 = 0x100000;
    w->a[D_8008A308].f0 = 0x100000;
    w->a[D_8008A2E0].f0 = 0x100000;
    w->a[D_8008A2E4].f0 = 0x100000;
    w->a[D_8008A2E8].f0 = 0x100000;
    w->a[D_8008A2EC].f0 = 0x100000;
    w->a[D_8008A2F0].f0 = 0x100000;
    w->a[D_8008A2F4].f0 = 0x100000;
    w->a[D_8008A2F8].f0 = 0x100000;
    w->a[D_8008A2FC].f0 = 0x100000;
    for (i = 0; i < w->count; i++) {
    }
    D_8008AF3C[D_8008A2BC] = 0;
}
