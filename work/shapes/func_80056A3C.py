# Shape file for work/shape_search.py. Every variant is a complete translation unit.
HEAD = '''#include "common.h"

extern s32 D_80082FA4[];
extern u8 D_8008A160[0x10];

'''
VARIANTS = {
    "inline_sum": HEAD + '''s32 func_80056A3C(u32 idx) {
    return D_80082FA4[idx & 0xFFFF] + *(s32 *) D_8008A160;
}
''',
    "table_then_global": HEAD + '''s32 func_80056A3C(u32 idx) {
    u32 i;
    s32 a;

    i = idx & 0xFFFF;
    a = D_80082FA4[i];
    return a + *(s32 *) D_8008A160;
}
''',
    "global_then_table": HEAD + '''s32 func_80056A3C(u32 idx) {
    u32 i;
    s32 a;
    s32 b;

    b = *(s32 *) D_8008A160;
    i = idx & 0xFFFF;
    a = D_80082FA4[i];
    return a + b;
}
''',
    "two_temps_masked_first": HEAD + '''s32 func_80056A3C(u32 idx) {
    u32 i;
    s32 a;
    s32 b;

    i = idx & 0xFFFF;
    a = D_80082FA4[i];
    b = *(s32 *) D_8008A160;
    return b + a;
}
''',
}
