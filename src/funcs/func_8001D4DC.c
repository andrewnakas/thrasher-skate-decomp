#include "common.h"

typedef struct {
    u8 pad0[8];
    s32 *base;
    s32 *end;
    s32 *cur;
} Ent_8001D4DC;

s32 func_8001D4DC(Ent_8001D4DC *e, s32 whence, s32 n) {
    s32 *p;

    switch (whence) {
    case 0:
        p = e->base + n;
        e->cur = p;
        return p - e->base;
    case 1:
        p = e->cur + n;
        e->cur = p;
        return p - e->base;
    }
    return -1;
}
