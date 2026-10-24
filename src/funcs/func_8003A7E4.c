#include "common.h"

extern s32 D_8008A6E8;
extern s32 D_8008A72C;
extern s32 D_8008B228;
extern void func_8003AECC(void);
extern void func_8003B478(s32 a, s32 b);
extern s32 func_80048450(void);
extern s32 func_800464E4(void);
extern void func_8003AAEC(void);
extern void func_8003ED20(void);
extern void func_800458E4(void);
extern void func_80049BA8(void);
extern void func_8003BDB8(void);
extern void func_8003C0B8(void);
extern void func_8003C730(void);
extern void func_8003F908(void);
extern void func_8004873C(void);
extern void func_80059CF0(s32 a);
extern void func_8003A9F0(void);

s32 func_8003A7E4(void) {
    func_8003AECC();
    if (D_8008A6E8 == 0xFFFF) {
        func_8003B478(0x200, 0xF0);
    }
    if (func_80048450() != 0) {
        return 1;
    }
    if (func_800464E4() != 0) {
        return 1;
    }
    func_8003AAEC();
    func_8003ED20();
    func_800458E4();
    func_80049BA8();
    if (D_8008A6E8 == 0) {
        func_8003BDB8();
        func_8003C0B8();
        func_8003C730();
    }
    func_8003F908();
    func_8004873C();
    func_80059CF0(1);
    func_8003A9F0();
    D_8008A72C = 1;
    D_8008B228 = 0;
    return 0;
}
