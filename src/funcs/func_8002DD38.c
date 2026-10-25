#include "common.h"

typedef struct {
    s32 f0;
    void (*f4)(u8 *);
    void (*f8)(u8 *);
} T_8002DD38;

extern u8 D_8006F834[0xC00];

s32 func_8002DD38(u8 *p) {
    void (*f)(u8 *) = ((T_8002DD38 *) D_8006F834)[p[3]].f4;

    if (f != 0) {
        f(p);
    }
    return 0;
}
