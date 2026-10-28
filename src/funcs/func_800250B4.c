#include "common.h"

extern s32 func_80033714(void *, void *, void *);
extern s32 func_80032FF4(void *, void *);
extern s32 func_80024DBC(void *, void *);

void func_800250B4(u8 *o) {
    s32 v[4];
    s32 a[4];
    s32 b[4];

    v[0] = 0x10C28F;
    v[1] = 0xFFE6CB86;
    v[2] = 0x0DD2F1;
    func_80033714(o + 8, v, a);
    func_80032FF4(a, o + 0x41C);
    func_80024DBC(o + 0x534, a);

    v[0] = 0xFFF78084;
    v[1] = 0xFFE2EB44;
    v[2] = 0x0DFE35;
    func_80033714(o + 8, v, b);
    func_80032FF4(b, o + 0x4A8);
    func_80024DBC(o + 0x5C0, b);

    v[0] = 0x0E0ED9;
    v[1] = 0xFFE54D0F;
    v[2] = 0x24C312;
    func_80033714(o + 8, v, a);
    func_80032FF4(a, o + 0x41C);
    func_80024DBC(o + 0x64C, a);

    v[0] = 0xFFF965A2;
    v[1] = 0xFFDFAB03;
    v[2] = 0x24DA1C;
    func_80033714(o + 8, v, b);
    func_80032FF4(b, o + 0x4A8);
    func_80024DBC(o + 0x6D8, b);

    v[0] = 0;
    v[1] = 0x1D67AE;
    v[2] = 0x280B02;
    func_80033714(o + 0x94, v, a);
    func_80032FF4(a, o + 0xD4);
    func_80024DBC(o + 0x1EC, a);

    v[0] = 0;
    v[1] = 0x1BE76C;
    v[2] = 0x0D49BA;
    func_80033714(o + 0x120, v, b);
    func_80032FF4(b, o + 0x160);
    func_80024DBC(o + 0x278, b);

    v[0] = 0;
    v[1] = 0xFFF889FC;
    v[2] = 0x3CE7EF;
    func_80033714(o + 0x94, v, a);
    func_80032FF4(a, o + 0xD4);
    func_80024DBC(o + 0x304, a);

    v[0] = 0;
    v[1] = 0xFFF6E9BB;
    v[2] = 0x25A0C4;
    func_80033714(o + 0x120, v, b);
    func_80032FF4(b, o + 0x160);
    func_80024DBC(o + 0x390, b);
}
