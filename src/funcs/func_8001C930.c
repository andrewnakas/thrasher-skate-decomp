#include "common.h"

typedef struct {
    union {
        u32 word;
        struct {
            u8 b0;
            u8 b1;
            u8 b2;
            u8 b3;
        } byte;
        struct {
            u32 id : 7;
            u32 flag : 1;
        } bit;
    } u;
    u16 key;
    u16 pad;
    u32 tag;
} R_8001C930;   /* 12 bytes */

typedef struct {
    u32 f0;
    u32 f4;
    u32 f8;
    u32 fC;
} E_8001C930;   /* 16 bytes */

extern u32 D_8008AE40;
extern u32 D_8008AE44;
extern u32 D_8008AE5C;

u32 func_8001C930(u32 id, u16 arg) {
    R_8001C930 *p = (R_8001C930 *)D_8008AE40;
    R_8001C930 *end = (R_8001C930 *)D_8008AE44;
    R_8001C930 *found = 0;
    u32 srcw;

    srcw = ((E_8001C930 *)((id << 4) + D_8008AE5C))->fC;
    if ((u32)p < (u32)end) {
        do {
            u32 w = p->u.word;

            if (id == (w & 0x7F)) {
                if ((w >> 7) & 1) {
                    found = p;
                } else if (arg == 0xFFFF || (srcw & 0x1000000) != 0) {
                    if (p->key == 0xFFFF) {
                        break;
                    }
                } else {
                    if (p->key == 0xFFFF) {
                        break;
                    }
                    if (p->key == arg && p->tag == ((E_8001C930 *)((id << 4) + D_8008AE5C))->f4) {
                        break;
                    }
                }
            }
            p = (R_8001C930 *)((u8 *)p + 0xC);
        } while ((u32)p < (u32)end);
    }
    if ((u32)p == (u32)end) {
        p = (R_8001C930 *)D_8008AE44;
        D_8008AE44 = (u32)((u8 *)p + 0xC);
        p->u.bit.flag = 0;
        p->u.bit.id = id;
        if (found == 0) {
            p->u.byte.b1 = 0xFF;
            p->u.byte.b2 = 0xFF;
            p->u.byte.b3 = 0xFF;
        } else {
            p->u.byte.b1 = found->u.byte.b1;
            p->u.byte.b2 = found->u.byte.b2;
            p->u.byte.b3 = found->u.byte.b3;
        }
    }
    return (u32)p;
}
