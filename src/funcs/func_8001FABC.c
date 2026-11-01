#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    s32 unk10;
    s32 unk14;
} Params;

typedef struct {
    u8 pad0[4];
    u8 unk4;
    u8 pad5[3];
    u8 *unk8;
    u16 *unkC;
} Data;

extern s32 func_8001D870(u16);
extern void func_8001DB74(u8 *);
extern s32 func_8001DD58(u8 *);
extern Data *func_800204F4(s32);
extern void func_8004874C(s32, s32, s32 *, Params *);
typedef struct {
    u16 unk0;
    u16 flags;
    u8 pad4[0x48];
} TableEntry;

extern TableEntry D_8006F2C0[];

void func_8001FABC(u8 *arg0) {
    Params params;
    s32 position[3];
    s32 flags;
    u16 value;
    u16 object_flags;
    u16 table_flags;
    u8 *cursor;
    u8 index;
    Data *data;
    u8 *element;
    TableEntry *table;
    TableEntry *table_entry;

    if (func_8001DD58(arg0) != 0) {
        if (*(u16 *)arg0 & 1) {
            func_8001DB74(arg0);
        }
    } else {
        func_8001D870(*(u16 *)(arg0 + 2));
        table = D_8006F2C0;
        table_entry = &table[*(u16 *)(arg0 + 2)];
        table_flags = table_entry->flags;
        params.unk0 = *(s32 *)(arg0 + 0x3C);
        params.unk4 = *(s32 *)(arg0 + 0x40);
        params.unk8 = arg0[0x30];
        object_flags = *(u16 *)arg0;
        flags = table_flags & 0x7FFF;
        if (object_flags & 0x200) {
            flags |= 0x8000;
        }
        if (object_flags & 0x400) {
            flags |= 0x4000;
        }
        if (object_flags & 0x800) {
            flags |= 0x2000;
        }
        if (object_flags & 0x40) {
            flags |= 0x200;
        }
        flags |= 0x100;
        data = func_800204F4(arg0[0x3D]);
        value = *data->unkC;
        params.unk0 = 0x10000;
        params.unk4 = 0x10000;
        params.unk8 = arg0[0x30];
        params.unkF = data->unk4;
        position[0] = *(s32 *)(arg0 + 0x10);
        position[1] = *(s32 *)(arg0 + 0x14);
        position[2] = *(s32 *)(arg0 + 0x18);
        index = arg0[0x3E];
        cursor = arg0 + 0x3F;
        if (index != 0xFF) {
            do {
                element = data->unk8 + index * 0x10;
                params.unkC = element[4];
                params.unkD = element[8];
                params.unkE = element[0xC];
                func_8004874C(flags, value & 0xFFFF, position, &params);
                position[0] += (params.unkE + 0xA) << 16;
                index = *cursor;
                cursor++;
            } while (index != 0xFF);
        }
        *(s32 *)(arg0 + 0x18) += 0xFFEC0000;
    }
}
