#include "common.h"

typedef struct { u16 pad; u32 hi:8; u32 lo:8; } B32;
typedef struct { u16 pad; u16 hi:8; u16 lo:8; } B16;
typedef struct { u16 pad; int hi:8; int lo:8; } BINT;
typedef struct { u16 pad; unsigned char hi:8; unsigned char lo:8; } BCH;
typedef struct { u8 pad[2]; u8 hi; u8 lo; } F8;
typedef struct { u8 pad[2]; s8 hi; s8 lo; } FS8;
typedef union { u32 w; u8 b[4]; } U;

u32 m01(u8 *p) { return ~((p[2] & 0xFF) << 8 | (p[3] & 0xFF)) & 0xFFFF; }
u32 m02(s8 *p) { return ~((p[2] & 0xFF) << 8 | (p[3] & 0xFF)) & 0xFFFF; }
u32 m03(u8 *p) { s32 h = p[2]; s32 l = p[3]; return ~((h & 0xFF) << 8 | (l & 0xFF)) & 0xFFFF; }
u32 m04(B32 *p) { return ~((p->hi & 0xFF) << 8 | (p->lo & 0xFF)) & 0xFFFF; }
u32 m05(B16 *p) { return ~((p->hi & 0xFF) << 8 | (p->lo & 0xFF)) & 0xFFFF; }
u32 m06(BINT *p) { return ~((p->hi & 0xFF) << 8 | (p->lo & 0xFF)) & 0xFFFF; }
u32 m07(BCH *p) { return ~((p->hi & 0xFF) << 8 | (p->lo & 0xFF)) & 0xFFFF; }
u32 m08(F8 *p) { return ~(p->hi << 8 | p->lo) & 0xFFFF; }
u32 m09(FS8 *p) { return ~(p->hi << 8 | p->lo) & 0xFFFF; }
u32 m10(volatile u8 *p) { return ~((p[2] & 0xFF) << 8 | (p[3] & 0xFF)) & 0xFFFF; }
u32 m11(u8 *p) { u8 h = p[2]; u8 l = p[3]; return ~(((u32)h & 0xFF) << 8 | ((u32)l & 0xFF)) & 0xFFFF; }
u32 m12(U *p) { return ~((p->b[2] & 0xFF) << 8 | (p->b[3] & 0xFF)) & 0xFFFF; }
u32 m13(u8 *p) { u32 h, l; h = p[2] & 0xFF; l = p[3] & 0xFF; return ~(h << 8 | l) & 0xFFFF; }
u32 m14(s8 *p) { s32 h = p[2]; s32 l = p[3]; return ~((h & 0xFF) << 8 | (l & 0xFF)) & 0xFFFF; }
u32 m15(u8 *p) { return ~(((u16)p[2] & 0xFF) << 8 | ((u16)p[3] & 0xFF)) & 0xFFFF; }
u32 m16(u8 *p) { return ~((p[2] << 8) | p[3]) & 0xFFFF; }
