#include "common.h"

typedef struct {
    u32 kind;
    u32 flags;
    s32 unk8;
    u8 padC[0x14];
    s32 scale[3];
    u8 pad2C[0xC];
    u8 *data;
    s32 unk3C;
    u32 color;
    u8 pad44[8];
    s32 unk4C;
    u8 pad50[4];
    u16 unk54;
    u8 pad56[0x124];
    u16 unk17A;
    u8 pad17C[0x40];
    s32 unk1BC;
} Object;

void *func_80034C20(s32);
void *memset(void *, s32, u32);

Object *func_800120B8(u32 kind, Object *object) {
    u8 *data;

    memset(object, 0, 0x1C0);
    object->kind = kind;
    object->unk8 = 0;
    object->flags = 1;
    object->scale[0] = 0x10000;
    object->scale[1] = 0x10000;
    object->scale[2] = 0x10000;
    object->unk54 = 0xFFFF;
    object->unk17A = 2;
    object->unk3C = 0;
    object->color = 0x808080;
    object->unk4C = 0;
    switch (kind) {
    case 1:
        data = func_80034C20(0x860);
        object->data = data;
        memset(data, 0, 0x860);
        *(u16 *)(object->data + 0x1A6) = 0x72;
        *(u8 *)(object->data + 0x115) = 0x13;
        *(s32 *)(object->data + 0x28) = 0;
        object->unk1BC = 0xDC0000;
        object->flags |= 4;
        break;
    case 3:
        object->unk1BC = 0x500000;
        object->flags |= 0x50;
        break;
    case 4:
        object->unk1BC = 0x320000;
        break;
    }
    return object;
}
