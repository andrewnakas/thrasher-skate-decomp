#include "common.h"

typedef struct {
    u8 pad0[0x38];
    u8 *unk38;
} S80014BF4;

typedef struct {
    u8 pad0[0x124];
    u16 unk124;
    u16 unk126;
    u16 unk128;
} T80014BF4;

typedef struct {
    u8 pad0[0x134];
    u16 unk134;
    u16 unk136;
    u16 unk138;
} U80014BF4;

void func_80014BF4(S80014BF4 *arg0, S80014BF4 *arg1) {
    ((U80014BF4 *)arg0->unk38)->unk134 = ((T80014BF4 *)arg1->unk38)->unk124;
    ((U80014BF4 *)arg0->unk38)->unk136 = ((T80014BF4 *)arg1->unk38)->unk126;
    ((U80014BF4 *)arg0->unk38)->unk138 = ((T80014BF4 *)arg1->unk38)->unk128;
}
