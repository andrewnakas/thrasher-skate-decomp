#include "common.h"

typedef struct {
    u32 v;
    u8 pad[0x1C];
} SlotA_80025004;

typedef struct {
    u32 v;
    u8 pad[0x24];
} SlotB_80025004;

typedef struct {
    u8 pad0[0xAFC];
    SlotA_80025004 a[41];
    u8 pad1[4];
    SlotB_80025004 b[4];
} Obj_80025004;

extern u32 D_8008AF34[2];
extern u32 D_8008A2BC;
extern u32 D_8008A2D8;
extern u32 D_8008A2DC;
extern u32 D_8008A2E0;
extern u32 D_8008A2E4;
extern u32 D_8008A2E8;
extern u32 D_8008A2EC;
extern void func_80024720();

void func_80025004(Obj_80025004 *p) {
    func_80024720();
    p->a[D_8008A2E0].v = 0x100000;
    p->a[D_8008A2E4].v = 0x100000;
    p->a[D_8008A2E8].v = 0x100000;
    p->a[D_8008A2EC].v = 0x100000;
    p->b[D_8008A2D8].v = 0x10000;
    p->b[D_8008A2DC].v = 0x10000;
    D_8008AF34[D_8008A2BC] = 0;
}
