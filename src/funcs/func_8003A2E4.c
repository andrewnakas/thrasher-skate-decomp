#include "common.h"

extern u8 D_8008A698;
extern u8 D_8008A699;
extern u8 D_8008A69A;
extern u32 D_8008A694;

void func_8003A2E4(u8 *r, u8 *g, u8 *b) {
    *r = D_8008A698 * D_8008A694 >> 8;
    *g = D_8008A699 * D_8008A694 >> 8;
    *b = D_8008A69A * D_8008A694 >> 8;
}
