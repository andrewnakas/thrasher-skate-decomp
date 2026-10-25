#include "common.h"

typedef struct {
    s32 key;
    void (*fn)(void *);
} Entry;

extern Entry D_800928C4[];
extern Entry *D_8008AEA8;

s32 func_8001D620(u8 *arg0) {
    u8 *cur;
    u8 *end;
    u8 *next;
    s32 size;
    Entry *e;
    s32 key;

    cur = *(u8 **)(arg0 + 0x10);
    end = *(u8 **)(arg0 + 0xC);
    if (cur < end) {
        key = *(s32 *)cur;
        e = D_800928C4;
        if (e < D_8008AEA8) {
            do {
                if (key == e->key) {
                    e->fn(*(void **)(arg0 + 0x10));
                    break;
                }
                e++;
            } while (e < D_8008AEA8);
        }
        next = *(u8 **)(arg0 + 0x10);
        size = *(s32 *)(next + 4);
        next += 8;
        next += size;
        *(u8 **)(arg0 + 0x10) = next;
        if (next < *(u8 **)(arg0 + 0xC)) {
            return (s32)next;
        }
    }
    return 0;
}
