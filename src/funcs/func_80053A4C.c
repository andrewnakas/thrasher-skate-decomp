#include "common.h"

typedef struct {
    u32 sector;
    s32 size;
    u16 rate;
    u8 chans;
    u8 padB;
    s32 unkC;
    s32 unk10;
} Strm_80053A4C;

typedef struct {
    u32 pos;
    s32 size;
} File_80053A4C;

extern s32 D_8008B450;
extern Strm_80053A4C D_800B13AC[2];

Strm_80053A4C *func_80053A4C(File_80053A4C *f, s32 flags) {
    Strm_80053A4C *s;
    s32 i;

    s = NULL;
    i = D_8008B450;
    do {
        if (D_800B13AC[i].size == 0) {
            s = &D_800B13AC[i];
            D_8008B450 = i + 1;
            if (i + 1 == 2) {
                D_8008B450 = 0;
            }
            break;
        }
        if (++i == 2) {
            i = 0;
        }
    } while (i != D_8008B450);
    if (s != NULL) {
        s->unk10 = 0;
        s->unkC = 0;
        s->sector = f->pos >> 11;
        s->size = f->size;
        if (flags & 2) {
            s->rate = 22050;
        } else if (flags & 1) {
            s->rate = 11025;
        } else {
            s->rate = 44100;
        }
        if (flags & 4) {
            s->chans = 1;
        } else {
            s->chans = 2;
        }
        return s;
    }
    return NULL;
}
