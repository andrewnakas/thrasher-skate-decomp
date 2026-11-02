#include "common.h"

typedef struct Obj_8002EE94 {
    u16 flags;
    u8 pad2[6];
    s32 active;
    u8 padC[8];
    struct Obj_8002EE94 *next;
} Obj_8002EE94;

typedef struct {
    u8 pad0[2];
    s16 x;
    u8 pad4[6];
    s16 z;
} Pos_8002EE94;

extern s32 func_8002BFFC(Pos_8002EE94 *, Obj_8002EE94 ***, s32);
extern s32 func_8002EFCC(Obj_8002EE94 *, s32, s32);

Obj_8002EE94 *func_8002EE94(Pos_8002EE94 *pos, s32 *out, s32 key, Obj_8002EE94 *hint) {
    Obj_8002EE94 **lists;
    Obj_8002EE94 ***pp;
    Obj_8002EE94 ***q;
    Obj_8002EE94 *o;
    s32 n;
    s16 *zp;

    lists = NULL;
    if (hint != NULL && func_8002EFCC(hint, pos->x, pos->z) != 0) {
        if (out != NULL) {
            *out = key;
        }
        return hint;
    }
    pp = &lists;
    n = func_8002BFFC(pos, pp, key);
    if (n == 0) {
        if (out != NULL) {
            *out = 0;
        }
        return NULL;
    }
    if (out != NULL) {
        *out = n;
    }
    /* the dead params are reused: key holds x, out holds z, q walks the bucket lists */
    key = pos->x;
    o = *lists++;
    zp = &pos->z;
    out = (s32 *) (s32) *zp;
    q = pp;
    while (o != NULL) {
        if (!(o->flags & 0x20) && o->active != 0 && func_8002EFCC(o, key, (s32) out) != 0) {
            return o;
        }
        o = o->next;
        if (o == NULL) {
            o = *(*q)++;
        }
    }
    return NULL;
}
