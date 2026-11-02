#include "common.h"

typedef struct {
    u8 pad0[0x54];
    s16 f54;
    u8 pad56[0x178 - 0x56];
    u16 f178;
} Key;

typedef struct {
    u8 pad0[4];
    u32 type;
    u8 pad8[4];
    s32 fC;
    u8 pad10[0x10];
    s32 f20[1];
} Info;

typedef struct {
    Key *key;
    s32 f4;
    Info *info;
    u8 padC[4];
    s32 f10;
} Obj;

typedef struct {
    u16 f0;
    u8 pad2[10];
} E12;

typedef struct {
    u8 pad0[0x14];
    E12 e[1];
} Hdr12;

typedef struct {
    Key *key;
    u16 f4;
    u16 f6;
} Ent8;

typedef struct {
    Key *key;
    u8 pad4[4];
    s32 f8;
    u16 fC;
    u16 padE;
} Ent16;

typedef struct {
    s16 count;
    u16 f2;
    u8 b[1];
} Map;

extern s32 D_8008AE0C;
extern Ent8 D_80092684[];
extern s32 D_8008ADD4;
extern u8 D_8008ADD8;
extern s32 D_8008ADFC;
extern u8 D_8008AE00;

s32 func_8001ADEC(Obj *, u16, u16, u16, s32);
void func_8001AF0C(Obj *, u16, u16, u16, s32, s32);
void func_8001AFC8(Info *, s32, s32);
void func_8001B0C0(Obj *);
s32 func_8001B3F4(s32);
void func_8001BD0C(Ent8 *, s32);
void func_8001C2B8(s32, u16, u16, s32, s32);
void func_8001C2F0(s32, s32, u16, s32, s32, s32, s32);
s32 func_8001C3CC(s32);
s32 func_8001C3F0(s32, s32);
Map *func_8001D1E8(s32, s32, u16);
u8 *func_8002BAC0(u16);

s32 func_8001A9DC(Obj *obj) {
    Ent8 *e8;
    Ent8 *e5; /* case 5 */
    Ent16 *e16;
    Map *m;
    s32 i;
    s32 k;
    s32 n;
    s32 id;
    s32 off;
    s32 t;
    s32 c;
    s32 cnt;
    s32 r;
    u32 sel;

    switch (obj->info->type) {
    case 5:
        e5 = NULL;
        for (i = 0; i < D_8008AE0C; i++) {
            if (obj->key == D_80092684[i].key) {
                e5 = &D_80092684[i];
                break;
            }
        }
        sel = obj->key->f178;
        obj->info->fC = ((Hdr12 *) func_8002BAC0(e5->f4))->e[sel].f0 << 16;
        func_8001ADEC(obj, e5->f6, 0, 0, 0);
        if (sel == 0) {
            func_8001BD0C(e5, 0);
        }
        break;
    case 1:
        e16 = NULL;
        for (i = 0; i < D_8008ADD4; i++) {
            if (obj->key == ((Ent16 *) &D_8008ADD8)[i].key) {
                e16 = &((Ent16 *) &D_8008ADD8)[i];
                break;
            }
        }
        func_8001C3F0(obj->info->f20[0], 0);
        m = NULL;
        n = func_8001C3CC(obj->info->f20[0]);
        func_8001ADEC(obj, e16->fC, 0, 0, 0);
        if (e16->f8 != 0) {
            m = func_8001D1E8(0, 2, e16->f8);
        }
        for (i = 0; i < n; i++) {
            off = i;
            if (m != NULL) {
                k = m->count;
                while (--k != -1) {
                    if (m->b[k] == i) {
                        t = m->f2 + k;
                        off = t - func_8001C3F0(obj->info->f20[i], 0);
                        break;
                    }
                }
            }
            func_8001C2B8(obj->info->f20[i], off, e16->fC + i, 0, 0);
        }
        c = func_8001C3CC(0x12);
        r = func_8001B3F4(c);
        e16->key->f54 = r;
        func_8001C2F0(0x12, 0, r, 0, 0, c, 1);
        break;
    case 2:
    case 3:
    case 4:
        e8 = NULL;
        for (i = 0; i < D_8008ADFC; i++) {
            if (obj->key == ((Ent8 *) &D_8008AE00)[i].key) {
                e8 = &((Ent8 *) &D_8008AE00)[i];
                break;
            }
        }
        switch (obj->info->type) {
        case 3:
            id = 0x15;
            break;
        case 4:
            id = 0x16;
            break;
        case 2:
        default:
            id = 0x13;
            break;
        }
        cnt = func_8001C3CC(id);
        if (cnt >= 7) {
            cnt = 6;
        }
        func_8001ADEC(obj, e8->f4, 0, func_8001C3F0(id, 0), cnt);
        if (obj->info->type == 2) {
            s32 extra = func_8001C3CC(0x14);
            func_8001AF0C(obj, e8->f4 + cnt, 0, func_8001C3F0(0x14, 0), extra, 0);
        }
        break;
    }
    func_8001B0C0(obj);
    if (obj->f10 != 0) {
        func_8001AFC8(obj->info, obj->f4, 0);
    }
    return 0;
}
