/* cflags: -fno-strength-reduce */
#include "common.h"

typedef struct Record Record;
typedef struct {
    u8 pad0[8];
    Record *records;
} Owner;

struct Record {
    u16 id;
    u16 flags;
    u16 rotation[3];
    s16 position[3];
    s32 extent[3];
    s32 unk1C;
    s32 unk20;
    u8 pad24[6];
    u16 unk2A;
    u8 pad2C[0x10];
    Owner *owner;
    Record *next;
    u8 pad44[0x11C];
};

typedef struct {
    u16 id;
    u16 flags;
    s16 position[3];
    s16 extent[3];
    u16 rotation[3];
    u16 pad16;
} Entry;

typedef struct {
    u8 pad0[0xA];
    u16 count;
    Entry entries[1];
} Chunk;

typedef struct {
    u8 pad0[0x18];
    u32 flags;
} Settings;

extern s32 D_8008AFEC;
s32 func_8001D5B0(void *, u32, s32);
u32 func_80034C20(s32);
s32 func_8002BA64(u16);
void *func_80034D4C(void *, const void *, s32);
void func_8001BC2C(u16);
void func_8002F810(Record *);

void func_800282E4(void *archive, Owner *owner, Settings *settings) {
    if (settings->flags & 0x08000000) {
        Record *previous = 0;
        Chunk *chunk = (Chunk *)func_8001D5B0(archive, 0x504F5250, 1);
        Entry *entry = chunk->entries;
        Record *allocation = (Record *)func_80034C20(chunk->count * 0x160);
        s32 remaining;
        Record *cursor;

        owner->records = allocation;
        remaining = chunk->count - 1;
        cursor = allocation;
        if (remaining >= 0) {
            s16 *anchor = (s16 *)((u8 *)chunk + 0x1A);
            Record *record = cursor;
            do {
                s32 lastExtent;
                cursor->id = func_8002BA64(entry->id);
                func_80034D4C(&cursor->flags, &entry->flags, 2);
                record->position[0] = anchor[-5];
                record->position[1] = anchor[-4];
                record->position[2] = anchor[-3];
                record->rotation[0] = anchor[1];
                record->rotation[1] = anchor[2];
                record->rotation[2] = anchor[3];
                record->extent[0] = anchor[-2] << 8;
                record->extent[1] = anchor[-1] << 8;
                lastExtent = anchor[0];
                record->unk1C = 0;
                record->unk20 = 0;
                record->owner = owner;
                record->extent[2] = lastExtent << 8;
                if (previous != 0) {
                    previous->next = cursor;
                }
                previous = record;
                anchor += 12;
                entry++;
                record->next = 0;
                remaining--;
                func_8001BC2C(cursor->id);
                func_8002F810(cursor);
                record->unk2A = 0xFF;
                record++;
                cursor++;
            } while (remaining >= 0);
        }
        D_8008AFEC += chunk->count;
    }
}
