#include "common.h"

/* Object whose state machine is driven by the action argument. */
typedef struct {
    u32 flags;          /* 0x0 */
    u8 pad4[0x18];
    s32 f1C;            /* 0x1C */
    s32 f20;            /* 0x20 */
} T_8002BB24;

/* Table entry returned by func_8002BAC0 for the object's low half-word. */
typedef struct {
    s32 f0;             /* 0x0 */
    u8 pad4[0x2];
    u8 f6;              /* 0x6 */
} T_8002BB24_ent;

extern u8 (*D_8008A314)(void *, u8);
s32 func_800142FC(s32);
s32 func_80014310(s32);
s32 func_8002AC14(s32, s32);
s32 func_8002B060(u8 *);
s32 func_8002B210(u8 *);
T_8002BB24_ent *func_8002BAC0(u16);

void func_8002BB24(T_8002BB24 *arg0, u32 arg1) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    T_8002BB24_ent *temp_v0;

    switch (arg1) {
    case 0:
        if (!(arg0->flags & 0x00800000)) {
            temp_v0 = func_8002BAC0((u16) arg0->flags);
            if (temp_v0->f0 & 0x20) {
                temp_a0 = arg0->f20;
                arg0->flags |= 0x00800000;
                if (temp_a0 != 0) {
                    func_8002AC14(temp_a0, 0x808080);
                }
            }
            if ((temp_v0->f6 != 0) && (D_8008A314 != NULL)) {
                D_8008A314(arg0, temp_v0->f6);
                return;
            }
        } else {
        default:
            return;
        }
        break;
    case 1:
        arg0->flags |= 0x01000000;
        arg0->flags |= 0x00400000;
        func_8002B210(arg0);
        func_8002B060(arg0);
        return;
    case 2:
        arg0->flags |= 0x00400000;
        return;
    case 3:
        arg0->flags &= 0xFFBFFFFF;
        return;
    case 4:
        temp_a0_2 = arg0->f1C;
        arg0->flags |= 0x02000000;
        if (temp_a0_2 != 0) {
            func_80014310(temp_a0_2);
            return;
        }
        break;
    case 5:
        temp_a0_3 = arg0->f1C;
        arg0->flags &= 0xFDFFFFFF;
        if (temp_a0_3 != 0) {
            func_800142FC(temp_a0_3);
        }
        break;
    }
}
