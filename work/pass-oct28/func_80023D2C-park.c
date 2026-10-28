#include "common.h"

typedef struct V3_80023D2C {
    s32 x;
    s32 y;
    s32 z;
} V3_80023D2C;

typedef struct S_80023D2C_Obj {
    u8 pad0[0x38];
    s32 unk38;
    u8 pad3C[8];
    V3_80023D2C unk44;
    u8 pad50[0xC];
    V3_80023D2C unk5C;
} S_80023D2C_Obj;

typedef struct S_80023D2C {
    s32 unk0;
    s32 unk4;
    S_80023D2C_Obj *unk8;
    S_80023D2C_Obj *unkC;
    s32 unk10;
    u8 *unk14;
    u8 *unk18;
    s32 unk1C;
} S_80023D2C;

extern s32 func_8003353C(u8 *a0, u8 *a1);
extern s32 func_80032C28(s32 a0);
extern void func_800330A4(V3_80023D2C *v);
extern void func_800331FC(V3_80023D2C *v, s32 s);
extern void func_80032FF4(V3_80023D2C *dst, V3_80023D2C *src);

void func_80023D2C(S_80023D2C *p) {
    V3_80023D2C d;
    V3_80023D2C t;
    s32 s;
    s32 r;

    s = p->unk4;
    r = func_8003353C(p->unk14 + 0x10, p->unk18 + 4);
    if (-r > 0) {
        s += func_80032C28(p->unk1C);
    }

    d.x = p->unk8->unk44.x - p->unkC->unk44.x;
    d.y = p->unk8->unk44.y - p->unkC->unk44.y;
    d.z = p->unk8->unk44.z - p->unkC->unk44.z;
    func_800330A4(&d);
    func_800331FC(&d, p->unk10);

    t = d;
    func_80032FF4(&t, &p->unkC->unk44);
    func_800331FC(&t, s);
    func_80032FF4(&p->unk8->unk5C, &t);

    t.x = p->unk8->unk44.x - d.x;
    t.y = p->unk8->unk44.y - d.y;
    t.z = p->unk8->unk44.z - d.z;
    func_800331FC(&t, s);
    func_80032FF4(&p->unkC->unk5C, &t);

    p->unk8->unk38 += s;
    p->unkC->unk38 += s;
}
