#include "common.h"

typedef struct {
    s32 used;
    s32 len;
    u8 *base;
    u8 *end;
    u8 *cur;
} Slot_8001D428;

extern Slot_8001D428 D_80092914[4];

Slot_8001D428 *func_8001D428(s32 *data, s32 size) {
    Slot_8001D428 *s;
    s32 i;
    s32 hdr;
    s32 len;

    hdr = 1;
    if (data[0] != 0x4D524F46) {
        if (size != 0) {
            hdr = 0;
            len = size;
        } else {
            len = 0;
        }
    } else {
        len = data[1];
    }
    s = D_80092914;
    for (i = 0; i < 4; i++, s++) {
        if (s->used == 0) {
            break;
        }
    }
    s->used = 1;
    if (hdr) {
        s->base = (u8 *)(data + 2);
    } else {
        s->base = (u8 *)data;
    }
    s->len = len;
    s->end = s->base + len;
    s->cur = s->base;
    return &D_80092914[i];
}
