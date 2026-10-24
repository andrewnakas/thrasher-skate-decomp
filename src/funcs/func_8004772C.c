#include "common.h"

typedef struct {
    u8 pad0[0xD];
    u8 unkD;
} Ent_8004772C;

s16 func_8004772C(Ent_8004772C *e) {
    if (e->unkD != 0) {
        return e->unkD;
    }
    return 0x100;
}
