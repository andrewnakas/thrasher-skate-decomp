#include "common.h"

typedef struct {
    u8 tag;
    u8 len;
    u8 pad[2];
    u8 data[1];
} Chunk;

extern u8 *D_8008AFA8;

u8 *func_8002C3A0(s32);

Chunk *func_8002C3C0(s32 i, u8 tag) {
    s32 off;
    u8 *p;
    Chunk *e;
    s32 n;
    s32 len;

    off = *(s32 *) (func_8002C3A0(i) + 4);
    if (off != 0) {
        p = D_8008AFA8 + off;
        e = (Chunk *) (p + 4);
        n = *p;
        if (--n != -1) {
            do {
                if (e->tag == tag) {
                    return e;
                }
                n--;
                len = (e->len + 3) & ~3;
                e = (Chunk *) e->data;
                e = (Chunk *) ((u8 *) e + len);
            } while (n != -1);
        }
    }
    return NULL;
}
