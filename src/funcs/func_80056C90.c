#include "common.h"

typedef struct {
    u8 b[8];
} B8_80056C90;

typedef struct {
    u32 w[0x12F];
} Blob_80056C90;

extern B8_80056C90 D_800B2514[];
extern u8 D_800B1F6C[];
extern B8_80056C90 D_8008B4D8[1];

s32 func_80056C90(void) {
    D_800B2514[0] = D_8008B4D8[-1];
    *(Blob_80056C90 *) ((u8 *) D_800B2514 + 8) = *(Blob_80056C90 *) D_800B1F6C;
    return 0;
}
