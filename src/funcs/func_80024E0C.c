#include "common.h"

typedef struct {
    u32 x;
    u32 y;
    u32 z;
} V3u;

extern void func_80024720(void);
extern void func_80033714(u8 *, V3u *, V3u *);
extern void func_80032FF4(V3u *, u8 *);
extern void func_80024DBC(u8 *, V3u *);

void func_80024E0C(u8 *arg0) {
    V3u v;
    V3u w;
    V3u z;

    func_80024720();
    v.x = 0;
    v.y = 0;
    v.z = 0x360000;
    func_80033714(arg0 + 0x3DC, &v, &w);
    z.x = w.x;
    z.y = w.y;
    z.z = w.z;
    func_80032FF4(&w, arg0 + 0x41C);
    func_80032FF4(&z, arg0 + 0x4A8);
    func_80024DBC(arg0 + 0x64C, &w);
    func_80024DBC(arg0 + 0x6D8, &z);
    v.x = 0;
    v.y = 0;
    v.z = 0x1D0000;
    func_80033714(arg0 + 0x3DC, &v, &w);
    z.x = w.x;
    z.y = w.y;
    z.z = w.z;
    func_80032FF4(&w, arg0 + 0x41C);
    func_80032FF4(&z, arg0 + 0x4A8);
    func_80024DBC(arg0 + 0x534, &w);
    func_80024DBC(arg0 + 0x5C0, &z);
}
