#include "common.h"

extern s32 D_8008A63C;
extern s32 D_8008A640;
extern s32 D_8008A644;
extern s32 D_8008B188;
void MemCardAccept(s32);
void MemCardSync(s32, s32, s32 *);

s32 func_80037BB8(void) {
    MemCardAccept(D_8008A63C + D_8008A640);
    MemCardSync(0, 0, &D_8008B188);
    if (D_8008B188 == 3) {
        D_8008A644 = 0;
    }
    if (D_8008B188 == 0 || D_8008B188 == 3) {
        return 0;
    }
    D_8008A644 = 0;
    return 1;
}
