#include "common.h"

extern u16 D_8008AE58;
extern u8 *D_8008AE54;
extern s32 func_80013ECC();
extern void func_8001CD7C();
extern void func_8001CDA4();

s32 func_8001CC5C(s32 *rec, s32 id, s32 *out)
{
    s32 ret = 0;
    s32 found = ret;
    s32 cnt;
    s32 i = 0;
    u8 *p;

    *out = 0;
    if (!(rec[0] & 1)) {
        cnt = D_8008AE58;
        if (i < cnt) {
            s32 key = id & 0xFFFF;
            s32 lim = cnt;
            p = D_8008AE54;
            do {
                u8 *q = p;
                if (*(u16 *) q == key) {
                    ret = *(s32 *) (q + 4);
                    found = 1;
                    break;
                }
                i++;
                p = q + 8;
            } while (i < lim);
        }
    }
    if (found != 0) {
        return ret;
    }
    {
        s32 flags;
        u32 f = rec[0];
        flags = (f & 0x8000000) != 0;
        if (f & 0x4000000) {
            flags |= 2;
        }
        if (f & 1) {
            flags |= 4;
        }
        ret = func_80013ECC(id & 0xFFFF, flags);
        if (ret == 0) {
            return 0;
        }
    }
    func_8001CD7C(ret, id & 0xFFFF);
    *out = 1;
    func_8001CDA4(ret, rec);
    return ret;
}
