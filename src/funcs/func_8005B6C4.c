#include "common.h"

extern u8 D_800842CC[];
extern u8 D_800842D0[];
extern u8 D_800842D4[];
extern u8 D_800842D8[];

/* Four SPU register writes through pointers held in globals. Reading each
 * pointer into a local before the store is what the listing does: the load
 * and the store can then land in the same pair of words the game has. */
void func_8005B6C4(s32 arg0) {
    s32 *p;

    p = *(s32 **) D_800842CC;
    *p = 0x04000002;
    p = *(s32 **) D_800842D0;
    *p = arg0;
    p = *(s32 **) D_800842D4;
    *p = 0;
    p = *(s32 **) D_800842D8;
    *p = 0x01000401;
}
