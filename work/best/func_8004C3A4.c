#include "common.h"

/* 0xC-byte slot record in D_8008B408 */
typedef struct {
    u8 f0;
    u8 f1;
    u8 pad2[6];
    s32 f8;
} R_8004C3A4;

/* 0xC-byte list node in D_800AF8E4 */
typedef struct N_8004C3A4 {
    u8 f0;
    u8 pad1[3];
    void *f4;
    struct N_8004C3A4 *f8;
} N_8004C3A4;

extern u8 D_8008B408[4];
extern N_8004C3A4 *D_8008B424;
extern s32 D_8008B428;
extern s32 D_8008B420;
extern u8 D_800AF8E4[];

s32 func_80051574(s32, s32 *);
void func_80051728(s32);
s32 func_8004C798(s32, void *);

s32 func_8004C3A4(s32 a0, u8 *a1) {
    R_8004C3A4 *e;
    N_8004C3A4 *n;
    N_8004C3A4 *p;
    s32 t;
    u32 i;
    s32 k;

    for (i = 0; i < 2; i++) {
        e = &((R_8004C3A4 *) D_8008B408)[i];
        if (e->f8 == 0) {
            continue;
        }
        func_80051574(e->f8, &t);
        if (t == 1) {
            continue;
        }
        switch (a1[0] & 0xC0) {
        case 0:
            return 0x601;
        case 0x40:
            if (e->f1 != 0) {
                return 0x601;
            }
            func_80051728(e->f8);
            break;
        case 0xC0:
            func_80051728(e->f8);
            D_8008B428 = 1;
            p = D_8008B424;
            if (p != 0) {
                do {
                    p->f0 = 0xFF;
                    p = p->f8;
                } while (p != 0);
            }
            D_8008B424 = 0;
            D_8008B428 = 0;
            break;
        default:
            if (e->f1 == 0) {
                func_80051728(e->f8);
                break;
            }
            k = D_8008B420;
            D_8008B428 = 1;
            do {
                n = (N_8004C3A4 *) (D_800AF8E4 + k * 0xC);
                if (n->f0 == 0xFF) {
                    n->f0 = a0 & 0xFF;
                    n->f4 = a1;
                    n->f8 = 0;
                    if (D_8008B424 == 0) {
                        D_8008B424 = n;
                    } else {
                        p = D_8008B424;
                        while (p->f8 != 0) {
                            p = p->f8;
                        }
                        p->f8 = n;
                    }
                    D_8008B428 = 0;
                    return 0;
                }
                k++;
                if (k == 0x20) {
                    k = 0;
                }
            } while (k != D_8008B420);
            return 0x603;
        }
    }
    return func_8004C798(a0 & 0xFF, a1);
}
