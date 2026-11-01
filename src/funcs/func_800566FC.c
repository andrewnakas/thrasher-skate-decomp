#include "common.h"

typedef struct {
    u8 pad0[0xC];
    u32 time;
    u8 pad10[0x51];
    u8 f61;
    u8 f62;
    u8 f63;
    u8 pad64[0xC];
} Voice_800566FC;

typedef struct {
    u8 pad0[0x44];
    u32 mask[2];
    u32 flags;
    u8 pad50[0x12];
    u8 f62;
    u8 pad63[0xD];
} Slot_800566FC;

typedef struct {
    u32 time;
    u8 id;
    u8 pad5[3];
} Ev_800566FC;

typedef struct {
    u8 pad0[0x10];
    u32 time;
    Ev_800566FC ev[5];
} Seq_800566FC;

extern Slot_800566FC D_800B2428[];
extern u8 D_8008B4DC;

s32 func_80056A3C(s32);
Seq_800566FC *func_8001D0A0(u32);

void func_800566FC(Voice_800566FC *v) {
    u32 t = v->time;
    Seq_800566FC *seq;
    s32 i;
    u32 thr[5];
    u8 ids[5];

    seq = func_8001D0A0(func_80056A3C(v->f61));
    for (i = 0; i < 5; i++) {
        ids[i] = seq->ev[i].id;
        if (v->f63 == 0) {
            thr[i] = seq->ev[i].time;
        } else {
            thr[i] = seq->time;
        }
    }
    for (i = 0; i < 5; i++) {
        if (t >= thr[i]) {
            u8 id = ids[i];
            if (id != 0x13) {
                D_800B2428[D_8008B4DC].mask[id >> 5] |= 1 << (id & 0x1F);
            } else {
                switch (D_800B2428[D_8008B4DC].f62) {
                case 0:
                case 1:
                    D_800B2428[D_8008B4DC].flags |= 0x200;
                    break;
                case 2:
                case 3:
                    D_800B2428[D_8008B4DC].flags |= 0x400;
                    break;
                case 4:
                case 5:
                case 12:
                    D_800B2428[D_8008B4DC].flags |= 0x20;
                    break;
                case 6:
                case 7:
                    D_800B2428[D_8008B4DC].flags |= 0x40;
                    break;
                case 8:
                case 9:
                    D_800B2428[D_8008B4DC].flags |= 0x80;
                    break;
                case 10:
                case 11:
                    D_800B2428[D_8008B4DC].flags |= 0x100;
                    break;
                }
            }
        }
    }
}
