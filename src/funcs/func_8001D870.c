#include "common.h"

extern u8 *D_8008AEC4;

s32 func_8001D870(u16 i) {
    return (s32) (D_8008AEC4 + i * 0x44);
}
