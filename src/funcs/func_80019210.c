/* cflags: -fno-strength-reduce -fno-schedule-insns */
#include "common.h"

typedef union {
    u32 value;
    u8 active;
} PackedValue;

typedef struct {
    u16 flags;
    u16 flags2;
    u32 pad4;
    s32 handle;
} Entry;

typedef struct {
    u16 count;
    u16 flags;
    u8 pad4[8];
    s32 offset;
    u16 mode;
    u8 pad12[2];
    u16 width;
    u16 height;
    u8 pad18[8];
    PackedValue value;
} Block;

typedef struct {
    u8 pad0[8];
    u16 width;
    u16 height;
    PackedValue value;
    s32 offset;
    u16 mode;
} Single;

extern void func_80015A94(s32);
extern void func_800194A4(Entry *);
extern void *func_80019518(Entry *);
extern void func_8001954C(Entry *);
extern void func_80039F98(void *);
extern void func_80039FBC(void *);
extern s32 func_8003A3C4(u32, u16, u16);

void func_80019210(Entry *arg0) {
    s32 kind;
    s32 offset;
    s32 simple_offset;
    s32 single_offset;
    s32 flags;
    s32 count;
    s32 i;
    s32 mode;
    u32 packed;
    u32 width;
    u32 height;
    u8 *data;
    Block *block;
    Block *simple;
    Block *record;
    Single *single;

    kind = arg0->flags & 0xE000;
    if (kind == 0) {
        simple = func_80019518(arg0);
        simple_offset = simple->offset;
        if (simple_offset != 0) {
            func_80039F98((u8 *)simple + simple_offset);
        }
    } else if ((kind == 0x4000 || kind == 0x6000 || kind == 0xC000) &&
               (arg0->flags & 0xE000) != 0xC000) {
        block = func_80019518(arg0);
        offset = block->offset;
        if (offset != 0) {
            flags = block->flags;
            count = 1;
            data = (u8 *)block + offset;
            if (flags & 1) {
                count = block->count;
            }
            for (i = 0; i < count; i++) {
                func_80039FBC(data);
                data += 0x204;
            }
        }
        i = block->count - 1;
        if (i >= 0) {
            mode = 4;
            record = (Block *)((i << mode) + (u32)block);
            do {
                if (record->value.active != 0) {
                    if (block->mode == mode) {
                        packed = record->value.value;
                        width = record->width;
                        height = record->height;
                        width >>= 1;
                    } else {
                        packed = record->value.value;
                        width = record->width;
                        height = record->height;
                    }
                    func_8003A3C4(packed, width, height);
                    record->value.active = 0;
                }
                i--;
                record = (Block *)((u8 *)record - 0x10);
            } while (i >= 0);
        }
    } else if ((arg0->flags & 0xE000) == 0x8000) {
        single = func_80019518(arg0);
        single_offset = single->offset;
        if (single_offset != 0) {
            func_80039FBC((u8 *)single + single_offset);
        }
        if (single->value.active != 0) {
            if (single->mode == 4) {
                packed = single->value.value;
                width = single->width;
                height = single->height;
                width >>= 1;
            } else {
                packed = single->value.value;
                width = single->width;
                height = single->height;
            }
            func_8003A3C4(packed, width, height);
            single->value.active = 0;
        }
    } else {
        goto finish;
    }
    func_8001954C(arg0);
finish:
    if (!(arg0->flags2 & 2)) {
        func_80015A94(arg0->handle);
        arg0->handle = 0;
    }
    func_800194A4(arg0);
}
