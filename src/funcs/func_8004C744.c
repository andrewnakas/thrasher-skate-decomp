#include "common.h"

extern char D_800107F8[];
extern char D_8008A950[];
extern void *D_800AF8A4[];

void *func_8004C744(u32 idx, void *v) {
    if (idx >= 0x10) {
        printf(D_800107F8, D_8008A950, 0x1D7);
        exit(1);
    }
    D_800AF8A4[idx] = v;
    return v;
}
