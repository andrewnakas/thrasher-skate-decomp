#include "common.h"

typedef struct Record Record;
typedef struct Region Region;
typedef struct {
    u16 pad0;
    u16 kind;
} Mesh;
typedef struct {
    u16 flags;
    u8 pad2[2];
    u8 data[0x18];
} Surface;
struct Record {
    u8 pad0[0x40];
    Record *next;
};
struct Region {
    u8 pad0[8];
    Record *records;
    u8 padC[0x20];
    Mesh *mesh;
    u8 pad30[4];
    Record *slots[4];
};
typedef struct {
    s32 kind;
    Region *region;
    void *data;
    u32 meshKind;
    Surface *surface;
    Mesh *mesh;
    s32 field18;
    s32 height;
    u8 pad20[0xC];
    s32 result;
} Output;

void *memset(void *, s32, u32);
Surface *func_8002EE94(u8 *, Region **, Region *, s32);
s32 func_8002F4C0(s16, s16, void *);
s32 func_8002C490(Surface *);
s32 func_8002F054(Record *, u8 *, Output *);

s32 func_8002ECB8(u8 *point, Output *out, Region *hint, s32 mode) {
    Region *region = 0;
    Surface *surface;
    Record *record;
    s32 height = 0x27100000;
    s32 result;
    s32 i;

    if (out != 0) {
        memset(out, 0, 0x30);
    }
    surface = func_8002EE94(point, &region, hint, mode);
    if (surface != 0) {
        if (surface->flags & 0x20) {
            surface = 0;
        }
    }
    if (surface != 0) {
        void *data = surface->data;
        height = func_8002F4C0(*(s16 *)(point + 2), *(s16 *)(point + 0xA), data);
        if (out != 0) {
            Region *selected = region;
            s32 value;
            Mesh *mesh;

            out->kind = 2;
            out->data = data;
            out->surface = surface;
            out->region = selected;
            value = func_8002C490(surface);
            selected = region;
            out->field18 = value;
            out->meshKind = selected->mesh->kind;
            mesh = selected->mesh;
            out->height = height;
            out->mesh = mesh;
        }
    }
    if (region != 0) {
        result = 0x27100000;
        record = region->records;
        if (record != 0) {
            s32 limit = result;
            do {
                result = func_8002F054(record, point, out);
                if (result != limit) {
                    break;
                }
                record = record->next;
            } while (record != 0);
        }
        i = 3;
        if (result == 0x27100000) {
            s32 limit = 0x27100000;
            for (; i != -1; i--) {
                record = region->slots[i];
                if (record != 0) {
                    result = func_8002F054(record, point, out);
                    if (result != limit) {
                        break;
                    }
                }
            }
        }
        if (result != 0x27100000) {
            if (out != 0) {
                Region *selected = region;
                out->result = result;
                out->region = selected;
            }
            return result;
        }
    }
    return height;
}
