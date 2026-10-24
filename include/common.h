#ifndef COMMON_H
#define COMMON_H

/* Thrasher: Skate and Destroy decomp: shared types.
 * Compiled by PsyQ-era GCC (see toolchain/compiler.toml): C89, no // comments
 * in code that must match old cpp behaviour, no inline asm (tools/scan.py). */

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;
typedef int bool32;

#ifndef NULL
#define NULL ((void *)0)
#endif

#define ARRAY_COUNT(a) (sizeof(a) / sizeof((a)[0]))

#endif
