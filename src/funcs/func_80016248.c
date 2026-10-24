#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} S80016248;

s32 func_80016248(S80016248 *arg0) {
    return (s32)arg0 + arg0->unk4 + arg0->unk0 + arg0->unk8;
}
