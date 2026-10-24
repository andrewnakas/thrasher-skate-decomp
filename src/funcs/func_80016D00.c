#include "common.h"

typedef struct {
    u32 w[4];
} E;

extern E *D_8008AD90;
extern s32 D_8008AD88;
extern s32 D_8008AD94;
extern E *func_80015E8C(s32);
extern void func_80015F10(s32);

void func_80016D00(void) {
    E *s;
    E *d;
    E *end;
    u8 flag;

    if (D_8008AD90 == NULL) {
        D_8008AD90 = func_80015E8C(D_8008AD94);
        flag = 0;
    } else {
        flag = 1;
    }
    d = D_8008AD90 + D_8008AD88 * 5;
    end = D_8008AD90 + 5;
    s = D_8008AD90;
    do {
        *d++ = *s++;
    } while (s != end);
    if (flag == 0) {
        D_8008AD90 = NULL;
        func_80015F10(D_8008AD94);
    }
}
