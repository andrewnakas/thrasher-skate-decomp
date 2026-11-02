#include "common.h"

typedef struct 
{
  u16 flags;
  u16 unk2;
  s16 unk4;
  s16 unk6;
  u8 pad8[8];
} Ent_80047268;
extern Ent_80047268 D_800AB794[];
s16 func_80047414(Ent_80047268 *);
s32 func_80047454(Ent_80047268 *, s32);
s32 func_800476A8(Ent_80047268 *);
s32 func_8004772C(Ent_80047268 *);
void func_80047268(u16 i)
{
  Ent_80047268 *e;
  s32 mask;
  s32 scale;
  s32 v;
  s32 f;
  s32 x;
  s32 y;
  u16 x1;
  u16 y1;
  e = &D_800AB794[i];
  f = e->flags & 0x180;
  v = f == 0;
  if (v)
  {
    mask = 0xFF;
    scale = 4;
  }
  else if (f == 0x80)
  {
    mask = 0x7F;
    scale = 2;
  }
  else
  {
    mask = 0x3F;
    scale = 1;
  }
  v = scale * func_80047414(e);
  x = mask & v;
  y = func_80047454(e, v) & 0xFF;
  x1 = x + (func_800476A8(e) - 1);
  y1 = y + (func_8004772C(e) - 1);
  e->unk4 = x + (y << 8);
  e->unk6 = x1 + (y1 << 8);
}
