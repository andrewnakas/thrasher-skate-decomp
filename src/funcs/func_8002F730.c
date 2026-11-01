/* cflags: -fno-strength-reduce */
#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} Vertex;

void func_8002F730(u16 *flags, s32 count, Vertex *vertices, s8 *indices) {
    u8 *cursor;
    s32 lastRecord;
    s32 missingVertex;

    if (count > 0) {
        lastRecord = 1;
        missingVertex = -1;
        /* The second cursor addresses the final vertex slot of each 0x2C-byte record. */
        cursor = (u8 *)flags + 0x28;
        do {
            *flags = 0;
            *(u8 *)(cursor - 0x26) = 0;
            *(u8 *)(cursor - 0x25) = 0;
            *(s32 *)(cursor - 0x24) = 0;
            *(s32 *)(cursor - 0x20) = 0;
            *(s32 *)(cursor - 0x1C) = 0;
            *(s32 *)(cursor - 0x18) = 0;
            if (count != lastRecord) {
                *(u8 **)(cursor - 0x14) = (u8 *)flags + 0x2C;
            } else {
                *(u8 **)(cursor - 0x14) = 0;
            }
            *(Vertex **)(cursor - 0xC) = &vertices[indices[0]];
            *(Vertex **)(cursor - 0x8) = &vertices[indices[1]];
            *(Vertex **)(cursor - 0x4) = &vertices[indices[2]];
            if (indices[3] == missingVertex) {
                *flags &= 0xFFFE;
            } else {
                *flags |= 1;
                *(Vertex **)cursor = &vertices[indices[3]];
            }
            cursor += 0x2C;
            flags = (u16 *)((u8 *)flags + 0x2C);
            count--;
            indices += 4;
        } while (count > 0);
    }
}
