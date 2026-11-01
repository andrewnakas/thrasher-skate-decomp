#include "common.h"

typedef struct {
    char name[0x59];
    u8 f59;
    u8 pad5A[7];
    u8 f61;
    u8 f62;
    u8 f63;
    u8 pad64[2];
    u8 f66;
    u8 pad67[9];
} Player_8005458C;

typedef struct {
    char *name;
    u8 val;
    u8 pad5[3];
} Course_8005458C;

typedef struct {
    u8 a;
    u8 b;
    u8 pad2[2];
    s32 c;
} Req_8005458C;

typedef struct {
    u8 pad0[4];
    s32 v;
} Node_8005458C;

extern Player_8005458C D_800B2428[];
extern Course_8005458C D_80082AFC[];
/* Globals the game reads with an unsplit lui/%lo pair are spelled as a small (8-byte) neighbour
   minus an offset: maspsx never makes sym-N gp-relative. */
extern u16 D_8008AC5C[4];
#define D_8008AC5A (&D_8008AC5C[-1])
extern u8 D_8008B4E0[8];
#define D_8008B4D8 (&D_8008B4E0[-8])
#define D_8008B4DC (&D_8008B4E0[-4])
extern s32 D_8008AEA8[2];
#define D_8008AEA4 (&D_8008AEA8[-1])
extern s32 D_800B1C6C[];
extern char D_8008AB0C[8];
extern u8 D_8008AB18;
extern u8 D_8008B4A4;
extern u8 D_8008B4A5;
extern u8 D_8008B4A6;
extern u8 D_8008B4A7;
extern u8 D_8008B4A8;
extern u8 D_8008AB17;
extern s8 D_8008B4C0;
extern s32 D_8008B4B0;
extern s32 D_8008B4B4;
extern s32 D_8008B4B8;

extern char *strcpy(char *, const char *);
extern s32 strcmp(const char *, const char *);
u32 func_80011B48(void);
void func_80011B8C(s32);
s32 func_800140EC(s32);
Node_8005458C *func_80014228(s32);
void func_800142BC(s32, s32);
s32 func_80019FF4(void);
s32 func_8001A1EC(void);
void func_8001B150(s32);
void func_8001B188(void);
void func_8001B238(s32);
void func_8001B4F8(s32);
void func_80020608(void);
void func_800309C4(s32, s32, s32, s32, s32);
s32 func_80036A78(s32, s32, s32);
void func_80036BF4(s32, s32);
void func_800558A8(s32);
void func_8005689C(Player_8005458C *);
u16 func_80056A3C(s32);
void func_8005737C(void);
void func_800B88D4(void);
void func_800BABFC(void);
s32 func_800BAED4(s32, s32, s32);
void func_800BB218(s32, s32);
void func_800C296C(s32);
void func_800C393C(void);
void func_800C54C0(void);
void func_800C77B8(void);
void func_800D1728(void);
void func_800D1830(void);
void func_800D22C0(s32);
void func_800D3750(void);
void func_800DA70C(void);
void func_800DC750(void);
u8 func_800DCCB0(Req_8005458C *);
void func_800DD578(s32, s32 *, s32 *);
s32 func_800DD5D8(s32);
void func_800DD5FC(s32, s32);

s32 func_8005458C(void) {
    Req_8005458C req;
    char name[16];
    s32 sp30;
    s32 sp34;
    s32 i;
    u32 j;
    Player_8005458C *p;
    s32 mode;
    s32 a;
    s32 h;
    u8 c;

    strcpy(name, D_800B2428[0].name);
    i = 0;
    while (name[i] != ' ' && name[i] != 0 && i < 15) {
        i++;
    }
    name[i] = 0;
    for (i = 0; i < 28; i++) {
        if (strcmp(name, D_80082AFC[i].name) == 0) {
            D_800B2428[0].f59 = D_80082AFC[i].val;
            break;
        }
    }
    func_8001B238(1);
    func_8005737C();
    func_80011B8C(0x8E);
    func_8001B150(0);
    if (func_80019FF4() == 1) {
        return 1;
    }
    func_800B88D4();
    func_800DA70C();
    switch (D_8008AC5A[0]) {
        case 4:
            a = 1;
            break;
        case 8:
            a = 2;
            break;
        default:
            a = 0;
            break;
    }
    func_800C296C(a);
    func_800142BC(-0x4000, 1);
    if (D_8008B4D8[0] != 0) {
        func_8001B4F8(func_80056A3C(D_8008AC5A[0]));
        for (j = 0; j < D_8008B4D8[0]; j++) {
            mode = D_800B2428[j].f62;
            strcpy(name, D_800B2428[j].name);
            i = 0;
            while (name[i] != ' ' && name[i] != 0 && i < 15) {
                i++;
            }
            name[i] = 0;
            if (mode == 4 && strcmp(name, D_8008AB0C) == 0) {
                mode = 0xC;
            }
            if (func_800BAED4(j, mode, 0) == 0) {
                return 1;
            }
        }
    } else {
        c = D_8008AB18++;
        switch ((u8) (c % 6)) {
            default:
            case 0:
                D_800B2428[0].f61 = 0;
                D_800B2428[0].f62 = 4;
                break;
            case 1:
                D_800B2428[0].f61 = 1;
                D_800B2428[0].f62 = 6;
                break;
            case 2:
                D_800B2428[0].f61 = 6;
                D_800B2428[0].f62 = 10;
                break;
            case 3:
                D_800B2428[0].f61 = 0;
                D_800B2428[0].f62 = 0;
                break;
            case 4:
                D_800B2428[0].f61 = 1;
                D_800B2428[0].f62 = 2;
                break;
            case 5:
                D_800B2428[0].f61 = 6;
                D_800B2428[0].f62 = 8;
                break;
        }
        D_8008B4A4 = D_800B2428[D_8008B4DC[0]].f63;
        D_800B2428[D_8008B4DC[0]].f63 = 1;
        D_800B2428[D_8008B4DC[0]].f66 = 0;
        D_800B2428[0].f62 += func_80011B48() & 1;
        {
            u16 v = D_800B2428[0].f61;
            D_8008AC5A[0] = v;
            func_8001B4F8(func_80056A3C(v));
        }
        if (func_800BAED4(0, D_800B2428[0].f62, 0) == 0) {
            return 1;
        }
    }
    func_800D1830();
    if (func_8001A1EC() != 0) {
        return 1;
    }
    func_800D22C0(0);
    func_80020608();
    func_800D1728();
    D_8008B4B4 = 0;
    if (D_8008B4D8[0] < 2 && ((u32) (D_800B2428[0].f62 - 10) < 2 || D_800B2428[0].f62 == 0x12)) {
        a = 1;
    } else {
        a = 0;
    }
    D_8008B4B4 = func_800140EC(a);
    if (D_8008B4B4 == 0) {
        return 1;
    }
    D_8008B4B0 = 0;
    D_8008B4B8 = 0;
    while (1) {
        Node_8005458C *n = func_80014228(D_8008B4B4);

        if (n == NULL) {
            break;
        }
        D_800B1C6C[D_8008B4B0] = n->v;
        D_8008B4B0++;
    }
    func_800DC750();
    if (D_8008B4D8[0] != 0) {
        req.c = 0x400;
        req.a = 0;
        req.b = 0;
        D_8008B4A7 = func_800DCCB0(&req);
    } else {
        req.c = 0x3000;
        req.a = 4;
        req.b = 0;
        D_8008B4A8 = func_800DCCB0(&req);
        func_800DD578(D_8008B4A8, &sp30, &sp34);
        h = func_800DD5D8(D_8008B4A8);
        if (func_80036A78(D_8008AEA4[0], D_800B2428[0].f61 * 6 + (D_800B2428[0].f62 >> 1), 0) == 0) {
            func_80036BF4(D_8008AEA4[0], sp30);
            func_800DD5FC(D_8008B4A8, h);
        }
    }
    func_800309C4(1000, 2, D_8008AC5A[0], D_8008B4D8[0] < 2 ? D_800B2428[0].f62 >> 1 : -1, 0);
    D_8008B4A6 = 1;
    D_8008AB17 = 0;
    D_8008B4A5 = 0;
    D_8008B4C0 = -1;
    if (D_8008B4D8[0] != 0) {
        func_800C393C();
    } else {
        D_8008B4DC[0] = 0;
        func_800C54C0();
        func_800BB218(0, 1);
        func_800BABFC();
        func_800D3750();
        func_800558A8(4);
        func_8005689C(D_800B2428);
        func_800C77B8();
    }
    func_8001B188();
    return 0;
}
