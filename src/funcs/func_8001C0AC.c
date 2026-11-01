#include "common.h"

void func_8001CFA4(void);
s32 func_8003682C(s32);
s32 func_80036E1C(s32, s32);
s32 func_8003F964(void);
s32 func_80046530(void);
/* read with an unsplit lui/lw at every use: spelled as neighbour minus offset */
extern s32 D_80089FE8[2];
extern s32 D_8008A034[2];
extern s32 D_8008A064[2];
extern s32 D_8008A078[2];
#define D_80089FE4 (D_80089FE8[-1])
#define D_8008A030 (D_8008A034[-1])
#define D_8008A060 (D_8008A064[-1])
#define D_8008A070 (D_8008A078[-2])
extern s32 D_8008AE9C;
extern s32 D_8008AEA0;
extern s32 D_8008AEA4;

s32 func_8001C0AC(void) {
    if ((D_8008AE9C = func_8003682C(func_80036E1C(D_80089FE4, D_8008A030))) != 0) {
        if ((D_8008AEA0 = func_8003682C(func_80036E1C(D_80089FE4, D_8008A060))) != 0) {
            if ((D_8008AEA4 = func_8003682C(func_80036E1C(D_80089FE4, D_8008A070))) != 0) {
                func_8001CFA4();
                if (func_8003F964() == 0) {
                    return func_80046530() != 0;
                }
                return 1;
            }
        }
    }
    return 1;
}
