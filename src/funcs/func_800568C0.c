#include "common.h"

typedef struct {
    u8 pad0[0x63];
    u8 a;
    u8 pad64[6];
    u8 b;
    u8 c;
    u8 d;
    u8 pad6D[3];
} Voice_800568C0;

typedef struct {
    s32 val;
    u8 flag;
    u8 pad5[3];
    u8 name;
    u8 pad9[3];
} Src_800568C0;

typedef struct {
    u8 pad0[0xC];
    s32 val;
    u8 flag;
    u8 pad11[3];
} Opt_800568C0;

typedef struct {
    Opt_800568C0 opt[12][3];
    u8 pad2D0[0x4B8 - 0x2D0];
    s32 sel;
} Menu_800568C0;

extern Voice_800568C0 D_800B2428[];
extern Menu_800568C0 D_800B1F6C;
extern Src_800568C0 D_80082DC4[12][3];
extern u8 *D_80082F74[];
extern s16 D_8008B4D0;
extern s16 D_8008B4D2;
extern s16 D_8008B4D4;
extern s16 D_8008B4D6;

void func_8001651C(void *, u8 *);
void func_800309C4(s32, s32, s32, s32, s32);

void func_800568C0(void) {
    Menu_800568C0 *m = &D_800B1F6C;
    u32 v;
    s32 i;
    s32 j;

    for (v = 0; v < 2; v++) {
        D_800B2428[v].a = 1;
        D_800B2428[v].b = 0;
        D_800B2428[v].c = 1;
        D_800B2428[v].d = 0;
    }
    for (i = 0; i < 12; i++) {
        for (j = 0; j < 3; j++) {
            m->opt[i][j].val = D_80082DC4[i][j].val;
            m->opt[i][j].flag = D_80082DC4[i][j].flag;
            func_8001651C(&m->opt[i][j], D_80082F74[D_80082DC4[i][j].name]);
        }
    }
    m->sel = 0;
    {
        s16 vol = 100;
        D_8008B4D0 = vol;
        func_800309C4(0x3EA, 1, vol, 0, 0);
    }
    {
        s16 vol = 100;
        D_8008B4D2 = vol;
        func_800309C4(0x3EA, 1, vol, 0, 0);
    }
    D_8008B4D4 = 0;
    D_8008B4D6 = 0;
}
