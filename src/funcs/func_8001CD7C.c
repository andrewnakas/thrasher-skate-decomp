#include "common.h"

extern u8 *D_8008AE54;
extern u16 D_8008AE58;

typedef struct {
    u16 f0;
    s32 f4;
} E_8001CD7C;

void func_8001CD7C(s32 a, s32 b) {
    E_8001CD7C *tab = (E_8001CD7C *) D_8008AE54;
    u16 i = D_8008AE58;

    tab[i].f0 = b;
    tab[i].f4 = a;
    D_8008AE58 = i + 1;
}
