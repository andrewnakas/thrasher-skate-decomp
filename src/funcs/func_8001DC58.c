#include "common.h"

typedef struct {
    u16 flags;
    u8 pad2[0xA];
    s32 unkC;
    u8 pad10[0x21];
    u8 unk31;
} Ent_8001DC58;

void func_8001DCF8(Ent_8001DC58 *, s32);

void func_8001DC58(Ent_8001DC58 *s, s32 v) {
    s->unkC = v;
    if (s->flags & 2) {
        func_8001DCF8(s, v & 0xFF);
        s->unk31 = 0;
    }
}
