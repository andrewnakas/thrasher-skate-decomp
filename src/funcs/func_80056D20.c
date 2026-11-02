#include "common.h"

typedef struct {
    u8 b[8];
} B8_80056D20;

typedef struct {
    u32 w[0x12F];
} Blob_80056D20;

extern B8_80056D20 D_800B2514[];
extern u8 D_800B1F6C[];
extern B8_80056D20 D_8008B4D8[1];

s32 func_80056DD0(void);

s32 func_80056D20(void) {
    s32 r;

    r = func_80056DD0();
    if (r != 0) {
        return r;
    }
    D_8008B4D8[-1] = D_800B2514[0];
    *(Blob_80056D20 *) D_800B1F6C = *(Blob_80056D20 *) ((u8 *) D_800B2514 + 8);
    return 0;
}
