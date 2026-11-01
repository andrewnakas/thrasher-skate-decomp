#include "common.h"

typedef struct {
    s32 m[12];
} Mat25B90;

typedef struct {
    u8 pad0[0x38];
    u8 *unk38;
} Arg25B90;

extern s32 D_8008A2BC;
extern s32 D_8008AF34[2];
extern s32 D_8008AF3C[2];
extern s32 D_8008AF44[2];
extern s32 D_8008AF4C[2];
extern s32 D_8008AF54[2];
extern s32 D_8008AF5C[2];
extern s32 D_8008AF64[2];
extern Mat25B90 D_8009CD30;
extern Mat25B90 D_8009CD60;
extern Mat25B90 D_8009CD90;
extern Mat25B90 D_8009CDC0;
extern Mat25B90 D_8009CDF0;

extern void func_80012214(Arg25B90 *, s32 *);
extern void func_80014764(Arg25B90 *, s32);
extern void func_80023004(u8 *);
extern void func_80024720(u8 *);
extern void func_80024B14(u8 *, Arg25B90 *);
extern void func_80024E0C(u8 *, Arg25B90 *);
extern void func_80025004(u8 *, Arg25B90 *);
extern void func_800250B4(u8 *, Arg25B90 *);
extern void func_80025544(u8 *, Arg25B90 *);
extern void func_800256EC(u8 *, Arg25B90 *);
extern void func_800257A0(u8 *, Arg25B90 *);
extern void func_80025988(u8 *, Arg25B90 *);
extern void func_80025A8C(u8 *, Arg25B90 *);
extern void func_8002635C(u8 *, s32, s32, s32, s32, Mat25B90 *);
extern void func_80026478(u8 *, s32, s32, Mat25B90 *, Mat25B90 *);
extern void func_8002673C(u8 *, s32, s32, Mat25B90 *, Mat25B90 *, s32);
extern void func_80026870(u8 *, s32, s32, Mat25B90 *, Mat25B90 *);
extern void func_80026C88(u8 *, s32, s32, Mat25B90 *, Mat25B90 *, s32);
extern void func_80026E78(u8 *);
extern void func_80026E88(Mat25B90 *, Mat25B90 *);
extern void func_80026EC8(Mat25B90 *, Mat25B90 *, Mat25B90 *);
extern void func_80026FBC(Mat25B90 *, u8 *);
extern void func_80027090(Arg25B90 *, Mat25B90 *, u8 *);
extern void func_80032FF4(s32 *, u8 *);
extern void func_800331FC(s32 *, s32);
extern void func_80033E14(Mat25B90 *, u8 *);
extern void *memset(void *, s32, s32);

void func_80025B90(u8 *self, Arg25B90 *arg1) {
    Mat25B90 m0;
    Mat25B90 m1;
    Mat25B90 m2;
    Mat25B90 m3;
    Mat25B90 m4;
    Mat25B90 m5;
    Mat25B90 inv;
    Mat25B90 tmp;
    s32 v[3];
    u8 *out;

    out = arg1->unk38 + 0x1AC;
    func_80024720(self);
    if (D_8008AF64[D_8008A2BC] != 0) {
        func_800257A0(self, arg1);
    }
    if (D_8008AF5C[D_8008A2BC] != 0) {
        func_800256EC(self, arg1);
    }
    if (D_8008AF64[D_8008A2BC] == 0) {
        if (D_8008AF4C[D_8008A2BC] != 0 && *(s32 *)(self + 0x132C) == 0) {
            func_80025988(self, arg1);
        }
        if (D_8008AF54[D_8008A2BC] != 0 && *(s32 *)(self + 0x132C) == 0) {
            func_80025A8C(self, arg1);
        }
    }
    if (D_8008AF34[D_8008A2BC] != 0) {
        func_80024E0C(self, arg1);
    }
    if (D_8008AF3C[D_8008A2BC] != 0) {
        func_800250B4(self, arg1);
    }
    if (D_8008AF44[D_8008A2BC] != 0) {
        func_80024B14(self, arg1);
    }
    func_80023004(self);
    func_8002635C(self, 7, 8, 8, 0, &m1);
    func_8002635C(self, 1, 2, 0, 1, &m0);
    func_80026478(self, 2, 4, &m0, &m3);
    func_80026478(self, 1, 3, &m0, &m2);
    func_80026870(self, 8, 10, &m1, &m5);
    func_80026870(self, 7, 9, &m1, &m4);
    func_8002635C(self, 7, 8, 13, 7, &D_8009CDF0);
    if (D_8008AF5C[D_8008A2BC] == 0 && D_8008AF3C[D_8008A2BC] == 0) {
        func_8002673C(self, 4, 6, &m3, &D_8009CD60, 1);
        func_8002673C(self, 3, 5, &m2, &D_8009CD30, 0);
        func_80026C88(self, 10, 12, &m5, &D_8009CDC0, 1);
        func_80026C88(self, 9, 11, &m4, &D_8009CD90, 0);
    } else {
        func_80026478(self, 4, 6, &m3, &D_8009CD60);
        func_80026478(self, 3, 5, &m2, &D_8009CD30);
        func_80026478(self, 10, 12, &m5, &D_8009CDC0);
        func_80026478(self, 9, 11, &m4, &D_8009CD90);
    }
    if (D_8008AF34[D_8008A2BC] != 0) {
        func_80024E0C(self, arg1);
        func_80025004(self, arg1);
    }
    if (D_8008AF3C[D_8008A2BC] != 0) {
        func_800250B4(self, arg1);
        func_80025544(self, arg1);
    }
    func_80033E14(&m1, self + 0x3DC);
    func_80033E14(&m1, self + 0x468);
    func_80033E14(&m0, self + 0x8);
    func_80033E14(&m0, self + 0x94);
    func_80033E14(&m0, self + 0x120);
    func_80033E14(&D_8009CDF0, self + 0x724);
    func_80033E14(&m3, self + 0x238);
    func_80033E14(&m2, self + 0x1AC);
    func_80033E14(&D_8009CD60, self + 0x350);
    func_80033E14(&D_8009CD30, self + 0x2C4);
    func_80033E14(&m4, self + 0x4F4);
    func_80033E14(&m5, self + 0x580);
    func_80033E14(&D_8009CD90, self + 0x60C);
    func_80033E14(&D_8009CDC0, self + 0x698);
    func_80027090(arg1, &m0, out + 0x134);
    func_80026E88(&m1, &inv);
    func_80026EC8(&tmp, &inv, &D_8009CDF0);
    func_80026FBC(&tmp, out + 0x140);
    func_80026EC8(&tmp, &inv, &m5);
    func_80026FBC(&tmp, out + 0x146);
    func_80026EC8(&tmp, &inv, &m4);
    func_80026FBC(&tmp, out + 0x158);
    func_80026E88(&m0, &inv);
    func_80026EC8(&tmp, &inv, &m3);
    func_80026FBC(&tmp, out + 0x16A);
    func_80026EC8(&tmp, &inv, &m2);
    func_80026FBC(&tmp, out + 0x17C);
    func_80026EC8(&tmp, &inv, &m1);
    func_80026FBC(&tmp, out + 0x13A);
    func_80026E88(&m2, &inv);
    func_80026EC8(&tmp, &inv, &D_8009CD30);
    func_80026FBC(&tmp, out + 0x182);
    func_80026E88(&m3, &inv);
    func_80026EC8(&tmp, &inv, &D_8009CD60);
    func_80026FBC(&tmp, out + 0x170);
    func_80026E88(&m4, &inv);
    func_80026EC8(&tmp, &inv, &D_8009CD90);
    func_80026FBC(&tmp, out + 0x15E);
    func_80026E88(&m5, &inv);
    func_80026EC8(&tmp, &inv, &D_8009CDC0);
    func_80026FBC(&tmp, out + 0x14C);
    func_80026E78(out + 0x152);
    func_80026E78(out + 0x176);
    func_80026E78(out + 0x164);
    func_80026E78(out + 0x188);
    memset(v, 0, 12);
    func_80032FF4(v, self + 0xD4);
    func_80032FF4(v, self + 0x160);
    func_80032FF4(v, self + 0x48);
    func_800331FC(v, 0x5555);
    func_80012214(arg1, v);
    func_80014764(arg1, 0);
    *(s32 *)(self + 0x132C) = 0;
}
