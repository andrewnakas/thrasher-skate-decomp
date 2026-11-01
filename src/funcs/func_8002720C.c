#include "common.h"

typedef struct { s32 x, y, z; } Vec3;

typedef struct {
    u8 pad0[6];
    s16 flag;
    u8 pad8[0x40];
    Vec3 position;
    Vec3 previous;
    u8 pad60[0xC];
    Vec3 delta;
    u8 pad78[0x14];
} RecordView;

typedef struct {
    u32 count;
    u8 pad4[0x1318];
    Vec3 position;
} Object;

typedef struct {
    u8 pad0[0x18];
    s16 f18, f1A, f1C, f1E;
} Transform;

extern Vec3 *func_80012238(Transform *);
extern void func_800331FC(Vec3 *, s32);
extern void func_800334D8(Vec3 *, s16 *);
extern void func_80033714(void *, Vec3 *, Vec3 *);
extern void func_80033E14(void *, void *);

void func_8002720C(Object *object, Transform *transform, void *matrix,
                   Vec3 *velocity, s16 *rotation) {
    Vec3 input;
    Vec3 vectors[6];
    Vec3 *current;
    Vec3 *origin;
    RecordView *record;
    u8 *item;
    u32 i;
    s32 copy_x, copy_y, copy_z;

    origin = func_80012238(transform);
    i = 0;
    if (object->count != 0) {
        do {
            current = &vectors[i];
            record = (RecordView *)((u8 *)object + i * 0x8C);
            switch (i) {
            case 0:
                input.x = 0x1E0000;
                input.y = 0x70000;
                input.z = 0;
                break;
            case 1:
                input.x = -0x1E0000;
                input.y = 0x70000;
                input.z = -0xA0000;
                break;
            case 2:
                input.x = -0x1E0000;
                input.y = 0x70000;
                input.z = 0xA0000;
                break;
            }
            func_80033714(matrix, &input, current);
            record->position.x = current->x + origin->x;
            record->position.y = current->y + origin->y;
            record->position.z = current->z + origin->z;
            copy_x = current->x;
            copy_y = current->y;
            copy_z = current->z;
            current[3].x = copy_x;
            current[3].y = copy_y;
            current[3].z = copy_z;
            func_800334D8(&vectors[i + 3], rotation);
            record->delta.x = current[3].x - current->x;
            item = (u8 *)object + (i * 0x8C + 4);
            record->delta.y = current[3].y - current->y;
            record->delta.z = current[3].z - current->z;
            record->delta.x += velocity->x;
            record->delta.y += velocity->y;
            record->delta.z += velocity->z;
            func_800331FC((Vec3 *)(item + 0x68), 0x8000);
            copy_x = record->position.x;
            copy_y = record->position.y;
            copy_z = record->position.z;
            record->previous.x = copy_x;
            record->previous.y = copy_y;
            record->previous.z = copy_z;
            func_80033E14(matrix, item + 4);
            record->flag = 0;
            i++;
        } while (i < object->count);
    }
    object->position.x = origin->x;
    object->position.y = origin->y;
    object->position.z = origin->z;
    transform->f1A = 0;
    transform->f1C = 0;
    transform->f1E = 0;
    transform->f18 = 0;
}
