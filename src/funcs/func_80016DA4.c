#include "common.h"

typedef struct {
    u32 w[4];
} E;

extern E *D_8008AD90;
extern s32 D_8008AD88;
extern s32 D_8008AD94;
extern E *func_80015E8C(s32);
extern void func_80015F10(s32);

void func_80016DA4(void) {
    E *s;
    E *end;
    E *d;
    u8 flag;
    s32 i;

    if (D_8008AD90 == NULL) {
        D_8008AD90 = func_80015E8C(D_8008AD94);
        flag = 0;
    } else {
        flag = 1;
    }
    i = D_8008AD88;
    s = D_8008AD90 + i * 5;
    if (i < 10) {
        d = s + 5;
        i++; /* the game's allocation depends on this dead bump */
        end = d;
        do {
            *d++ = *s++;
        } while (s != end);
        D_8008AD88 = D_8008AD88 + 1;
    }
    if (flag == 0) {
        D_8008AD90 = NULL;
        func_80015F10(D_8008AD94);
    }
}
