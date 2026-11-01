#include "common.h"

typedef struct Chunk_8001D540 {
    s32 key;
    s32 len;
    u8 data[1];
} Chunk_8001D540;

typedef struct {
    u8 pad0[8];
    s32 *base;
    Chunk_8001D540 *end;
    Chunk_8001D540 *cur;
} Ent_8001D540;

s32 func_8001D540(Ent_8001D540 *e, s32 key, s32 rewind) {
    Chunk_8001D540 *c;

    c = e->cur;
    if (rewind == 0) {
        u8 *d = c->data;
        c = (Chunk_8001D540 *)(d + c->len);
    }
    while (c < e->end) {
        u8 *d;
        if (key == c->key) {
            e->cur = c;
            return (s32 *)c - e->base;
        }
        d = c->data;
        c = (Chunk_8001D540 *)(d + c->len);
    }
    return -1;
}
