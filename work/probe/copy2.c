#include "common.h"

typedef struct { s32 f0, f1, f2, f3, f4; } E;
extern E *D_8008B384[];
extern E *D_8008B060;
extern s32 D_8008B388[];

void q1(s32 a) { E *p; p = D_8008B060; D_8008B060 = p + 1; p->f0 = a; }
void q2(s32 a, s32 i) { E *p; p = D_8008B384[i]; D_8008B384[i] = p + 1; p->f0 = a; }
void q3(s32 a, s32 i) { E *p; E **slot; slot = &D_8008B384[i]; p = *slot; *slot = p + 1; p->f0 = a; }
void q4(s32 a, s32 i) { E *p; s32 v; v = D_8008B388[i]; p = (E *)v; D_8008B388[i] = v + 0x14; p->f0 = a; }
void q5(s32 a, s32 i) { E *p; p = (E *)D_8008B388[i]; D_8008B388[i] = (s32)p + 0x14; p->f0 = a; }
void q6(s32 a, s32 i) { E *p; E **slot; slot = (E **)&D_8008B388[i]; p = *slot; *slot = p + 1; p->f0 = a; }
void q7(s32 a) { E *p; u8 *q; p = D_8008B060; q = (u8 *)p; D_8008B060 = p + 1; *(s32 *)q = a; }
