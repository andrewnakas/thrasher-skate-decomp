#include "common.h"

extern s32 func_8004763C(u16 i);

u16 func_80047680(u16 i) { return 1 << func_8004763C(i); }
