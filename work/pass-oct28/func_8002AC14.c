/* cflags: -mno-split-addresses */
#include "common.h"

typedef struct {
    u8 id;      /* 0x00 */
    u8 count;   /* 0x01 */
    u8 pad2[2]; /* 0x02 */
    u8 *data;   /* 0x04 */
} Ent_8002AC14;

extern u8 D_800A4F00[0x100];

void func_8002AC14(void *arg0, u32 rgb) {
    u8 *o;
    Ent_8002AC14 *e;
    u8 *d;
    u8 *out;
    s32 n;
    s32 r;
    s32 g;
    s32 b;
    s32 k;
    s32 scale;
    s32 v;
    s32 cnt;
    u8 *tbl;

    o = arg0;
    n = *(u8 *) (o + 5) - 1;
    if (n < 0) {
        return;
    }
    r = (rgb & 0xFF) - 0x80;
    g = ((rgb >> 8) & 0xFF) - 0x80;
    b = ((rgb >> 16) & 0xFF) - 0x80;
    for (; n >= 0; n--) {
        e = ((Ent_8002AC14 **) (o + 0x10))[n];
        d = e->data;
        cnt = e->count;
        tbl = *(u8 **) (D_800A4F00 + 4) + e->id * 156;
        for (k = 0; k < cnt; k++) {
            scale = d[k * 8 + 5] << 9;
            out = *(u8 **) (tbl + 0x48) + d[k * 8 + 4] * 12;
            v = ((r * scale) >> 16) + d[k * 8 + 0];
            if (v >= 0x100) {
                v = 0xFF;
            }
            if (v < 0) {
                v = 0;
            }
            out[8] = v;
            v = ((g * scale) >> 16) + d[k * 8 + 1];
            if (v >= 0x100) {
                v = 0xFF;
            }
            if (v < 0) {
                v = 0;
            }
            out[9] = v;
            v = ((b * scale) >> 16) + d[k * 8 + 2];
            if (v >= 0x100) {
                v = 0xFF;
            }
            if (v < 0) {
                v = 0;
            }
            out[10] = v;
        }
    }
}
