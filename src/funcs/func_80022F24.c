#include "common.h"

void func_80022454(u8 *rec);
void func_80022968(u8 *rec);
void func_80022E4C(u8 *rec);

void func_80022F24(u8 *s) {
    u32 i;
    u8 *rec;

    if (*(u32 *) (s + 0x132C) != 0) {
        return;
    }
    rec = s + 0xFFC;
    i = 0;
    if (*(u32 *) (s + 0xFF8) == i) {
        return;
    }
    do {
        switch (*(u32 *) rec) {
        case 0:
            func_80022454(rec);
            break;
        case 7:
            func_80022968(rec);
            break;
        case 9:
            func_80022E4C(rec);
            break;
        }
        rec += 0x28;
    } while (++i < *(u32 *) (s + 0xFF8));
}
