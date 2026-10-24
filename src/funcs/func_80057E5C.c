#include "common.h"

typedef struct {
    u8 pad[0x30];
} Ent_80057E5C;

extern Ent_80057E5C D_800B2C7C[];

Ent_80057E5C *func_80057E5C(s32 i) {
    return &D_800B2C7C[i];
}
