#include "common.h"

extern s32 D_8008A9EC;
extern s32 D_8008B444;
extern u8 *D_800B10EC[];
extern u8 D_800B0F6C[];

typedef struct {
    u8 pad[0x48];
    u8 f48;
    u8 pad2[3];
    s32 f4C;
    s32 f50;
} Voice_80052380;

void SpuFree(s32);
void SpuSetKey(s32, u32);
void func_8004E30C(u8);

s32 func_80052380(u32 mask) {
    u32 i;
    u32 j;
    u32 voices;
    u8 *e;
    u8 *q;
    u8 *t;

    voices = 0;
    for (i = 0; i < 0x18; i++) {
        if ((mask & (1 << i)) == 0) {
            continue;
        }
        e = D_800B10EC[i];
        if (e == NULL) {
            continue;
        }
        if (*(u16 *) e & 0x100) {
            mask &= ~(1 << *(s32 *) (e + 0x58));
        }
        if (*(u8 *) (e + 2) != 8) {
            continue;
        }
        j = 0;
        do {
            s32 *pool = &(&D_8008A9EC)[-21];
            q = e + j * 0xC;
            D_800B10EC[*(s32 *) (q + 0x4C)] = NULL;
            voices |= 1 << *(s32 *) (q + 0x4C);
            SpuFree(*(s32 *) (q + 0x50));
            *pool += 0x1000;
            *(s32 *) (q + 0x50) = -1;
            func_8004E30C(q[0x48]);
            j++;
        } while (j <= ((*(u16 *) e >> 8) & 1));
        for (j = 0; j < 4; j++) {
            t = D_800B0F6C + j * 0x60;
            if (e == t) {
                u16 v = *(u16 *) t;

                D_8008B444 = j;
                *(u16 *) t = v & 0x7FFF;
                break;
            }
        }
    }
    SpuSetKey(0, voices);
    return 0;
}
