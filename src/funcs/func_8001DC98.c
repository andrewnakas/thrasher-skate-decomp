#include "common.h"

typedef struct {
    u16 f00;
    u16 f02;
    u8 pad0[0x68];
} Ent_8001DC98;

extern s32 D_8008AEAC;
extern u8 *D_8008AEB0;

void func_8001DC98(void) {
    s32 i = D_8008AEAC;
    Ent_8001DC98 *e = (Ent_8001DC98 *) D_8008AEB0;

    for (; i > 0; i--) {
        if (e->f00 & 1) {
            (*(void (**)(Ent_8001DC98 *)) ((u8 *) e + 4))(e);
        }
        e++;
    }
}
