#include "common.h"

typedef struct {
    s32 unk0;
    u8 pad4[0x5C];
} Unk800366F0;

extern Unk800366F0 D_800A677C[];
s32 func_8005D130(Unk800366F0 *);

s32 func_800366F0(s32 i) {
    if (D_800A677C[i - 1].unk0 == -1) {
        return 0;
    }
    return func_8005D130(&D_800A677C[i - 1]);
}
