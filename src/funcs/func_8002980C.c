#include "common.h"

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    u8 *unk4;
} Entry;

typedef struct {
    u16 unk0;
    u16 unk2;
    u8 unk4;
    u8 count;
    u16 unk6;
    u16 unk8;
    u16 unkA;
    s32 unkC;
    Entry *entries[4];
} Record;

typedef struct {
    u16 unk0;
    u16 unk2;
    u8 unk4;
    u8 count;
    u16 unk6;
    u16 unk8;
    u16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
} Source;

typedef struct {
    u8 pad[0x4C];
    s32 count;
    Record *records;
} State;

extern u8 *func_8001D5B0(u8 *, u32, s32);
extern void *func_80034C20(s32);
extern State D_800A4F00;

void func_8002980C(u8 *arg0, s32 arg1, u8 *arg2) {
    s32 alignment;
    s32 item_index;
    s32 group_index;
    s32 group_count;
    s32 record_index;
    Entry *entry;
    u8 *items;
    Record *record;
    u16 count;
    u8 item_count;
    u8 value;
    u8 *header;
    u8 *cursor;
    Source *source;
    u8 *next;
    u8 *item_field;

    if (*(u32 *)(arg2 + 0x18) & 0x100000) {
        header = func_8001D5B0(arg0, 0x54565944, 1);
        record_index = 0;
        count = *(u16 *)(header + 0xA);
        D_800A4F00.count = count;
        record = func_80034C20(count << 5);
        source = (Source *)(header + 0xC);
        D_800A4F00.records = record;
        if (D_800A4F00.count > 0) {
            do {
                record->unk0 = source->unk0;
                record->unk2 = source->unk2;
                record->unk4 = source->unk4;
                record->count = source->count;
                record->unk6 = source->unk6;
                group_count = record->count;
                next = (u8 *)(source + 1);
                record->unk8 = source->unk8;
                group_index = 0;
                record->unkA = source->unkA;
                record->unkC = source->unkC | (source->unkE << 8) |
                    (source->unk10 << 16);
                if (group_count != 0) {
                    do {
                        entry = func_80034C20(group_count * 8);
                        record->entries[group_index] = entry;
                        entry->unk0 = *next;
                        item_count = next[1];
                        entry->unk1 = item_count;
                        items = func_80034C20(entry->unk1 * 8);
                        cursor = next + 2;
                        item_index = 0;
                        entry->unk4 = items;
                        if (entry->unk1 != 0) {
                            item_field = items + 5;
                            do {
                                item_index += 1;
                                item_field[-1] = cursor[0];
                                value = cursor[1];
                                cursor += 2;
                                item_field[0] = value;
                                item_field += 8;
                            } while (item_index < (s32)entry->unk1);
                        }
                        next = cursor;
                        group_count = record->count;
                        group_index += 1;
                    } while (group_index < group_count);
                }
                alignment = (s32)next & 3;
                if (alignment != 0) {
                    source = (Source *)(next - (alignment - 4));
                } else {
                    source = (Source *)next;
                }
                record++;
                record_index += 1;
            } while (record_index < D_800A4F00.count);
        }
    }
}
