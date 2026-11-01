#include "common.h"

typedef struct {
    u16 id;             /* 0x0 */
    u16 flags;          /* 0x2 */
    u8 pad4[4];
    s32 data;           /* 0x8 */
    s32 extra;          /* 0xC */
} Node_8001974C;

extern s32 D_8008AD64;

extern Node_8001974C *func_80019630(u32);
extern Node_8001974C *func_80019670(u32);
extern s32 func_80036A78(s32, s32, s32);
extern s32 func_80036B18(s32);
extern s32 func_800159D8(s32);
extern s32 func_80015E8C(s32);
extern s32 func_80036BF4(s32, s32);
extern void func_80015F10(s32);
extern Node_8001974C *func_80019444(void);

Node_8001974C *func_8001974C(u16 id, s32 flag) {
    Node_8001974C *e;
    Node_8001974C *p;
    s32 data;
    s32 extra;
    s32 owned;

    if ((id & 0xE000) != 0xA000) {
        return 0;
    }
    data = id & 0xFFFF;
    e = func_80019630(data);
    if (e != 0) {
        return e;
    }
    p = func_80019670(data);
    owned = 1;
    if (p != 0) {
        data = p->data;
        extra = p->extra;
    } else {
        owned = 0;
        extra = 0;
        if (func_80036A78(D_8008AD64, data, owned) != 0) {
            return 0;
        }
        data = func_800159D8(func_80036B18(D_8008AD64));
        if (data == 0) {
            return 0;
        }
        func_80036BF4(D_8008AD64, func_80015E8C(data));
        func_80015F10(data);
    }
    e = func_80019444();
    if (e == 0) {
        return 0;
    }
    e->flags = 0;
    if (flag != 0) {
        e->flags = 1;
    }
    if (owned) {
        e->flags |= 2;
    }
    e->id = id;
    e->data = data;
    e->extra = extra;
    return e;
}
