#include "common.h"

typedef struct {
    u8 pad0[8];
    s32 *start;
    s32 *end;
    s32 *cursor;
} Stream;

s32 func_8001D4DC(Stream *stream, s32 mode, s32 offset) {
    s32 *cursor;

    switch (mode) {
    case 0:
        cursor = stream->start + offset;
        stream->cursor = cursor;
        return cursor - stream->start;
    case 1:
        cursor = stream->cursor + offset;
        stream->cursor = cursor;
        return cursor - stream->start;
    default:
        return -1;
    }
}
