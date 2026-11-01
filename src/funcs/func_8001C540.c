#include "common.h"

typedef struct {
    s32 w[4];
} Item16;

void func_80034BD8(void *);
void *func_80034C20(u32);
void func_80034D4C(void *, void *, s32);
void qsort(void *, u32, u32, s32 (*)(const void *, const void *));
s32 func_8001C4BC(const void *, const void *);
extern Item16 *D_8008AE64;
extern u16 D_8008AE68;

void func_8001C540(void) {
    Item16 **ptrs;
    Item16 *sorted;
    Item16 **pp;
    Item16 *it;
    s32 n;

    ptrs = func_80034C20(D_8008AE68 * 4);
    pp = ptrs;
    it = D_8008AE64;
    for (n = D_8008AE68; n > 0; n--) {
        *pp++ = it++;
    }
    qsort(ptrs, D_8008AE68, 4, func_8001C4BC);
    sorted = func_80034C20(D_8008AE68 * 16);
    pp = ptrs;
    it = sorted;
    for (n = D_8008AE68; n > 0; n--) {
        *it++ = **pp++;
    }
    func_80034D4C(D_8008AE64, sorted, D_8008AE68 * 16);
    func_80034BD8(sorted);
    func_80034BD8(ptrs);
}
