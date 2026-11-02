#include "common.h"

typedef struct {
    u8 pad0[0x28];
    void *root;
} Obj2BFFC;

extern s32 D_8008B034[2];
extern s32 *D_8008B048;

s32 func_8002C148(Obj2BFFC *o, s32 x, s32 z);
Obj2BFFC *func_8002C0B8(s16 *v);
void func_8002C284(s16 *v, void *n);

Obj2BFFC *func_8002BFFC(s32 *p, s32 **out, Obj2BFFC *hint) {
    Obj2BFFC *o;
    s16 v[3];

    D_8008B048 = D_8008B034;
    v[0] = p[0] >> 16;
    v[1] = 0;
    v[2] = p[2] >> 16;
    o = 0;
    if (hint != 0 && func_8002C148(hint, v[0], v[2]) != 0) {
        o = hint;
    }
    if (o == 0) {
        o = func_8002C0B8(v);
        if (o == 0) {
            return 0;
        }
    }
    func_8002C284(v, o->root);
    if (D_8008B048 >= &D_8008B034[5]) return 0;
    *D_8008B048 = 0;
    *out = D_8008B034;
    return o;
}
