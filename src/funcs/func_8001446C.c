#include "common.h"

typedef struct {
    s32 x, y, z;
} V3_1446C;

typedef struct {
    u8 pad0[0x130];
    s32 unk130;
    s16 rot[1];
} Pose_1446C;

typedef struct {
    u8 pad0[4];
    s32 flags;
    s32 model;
    V3_1446C pos;
    u8 pad18[2];
    s16 rx;
    s16 ry;
    s16 rz;
    V3_1446C scale;
    u8 pad2C[0xC];
    Pose_1446C *pose;
} Obj_1446C;

typedef struct {
    u8 chain[19][8];
} Chains_1446C;

typedef struct {
    s32 off[19 * 3];
} Offs_1446C;

s32 func_80032C28(s32, s32);
void func_800333C8(V3_1446C *, s16);
void func_80033428(V3_1446C *, s16);
void func_80033480(V3_1446C *, s16);
extern Chains_1446C D_8006E5D4[];
extern Offs_1446C D_8006E66C[];

void func_8001446C(Obj_1446C *obj, s32 part, V3_1446C *in, V3_1446C *out, s32 mode) {
    V3_1446C v;
    Pose_1446C *pose;
    u8 *c;
    V3_1446C *o;
    s32 j;
    u8 b;

    pose = obj->pose;
    c = D_8006E5D4[obj->model].chain[part];
    if (mode & 1) {
        v.x = in->x;
        v.y = in->y;
        v.z = in->z;
    } else {
        v.x = 0;
        v.y = 0;
        v.z = 0;
    }
    b = *c;
    while ((s8) b != -1) {
        j = (s8) b * 3;
        func_800333C8(&v, pose->rot[j]);
        func_80033428(&v, -pose->rot[j + 1]);
        func_80033480(&v, pose->rot[j + 2]);
        o = (V3_1446C *) &D_8006E66C[obj->model].off[j];
        v.x += o->x;
        v.y += o->y;
        c++;
        v.z += o->z;
        b = *c;
    }
    v.y += pose->unk130;
    if (mode & 2) {
        v.x = in->x;
        v.y = in->y;
        v.z = in->z;
    }
    if (obj->flags & 8) {
        v.x = func_80032C28(v.x, obj->scale.x);
        v.y = func_80032C28(v.y, obj->scale.y);
        v.z = func_80032C28(v.z, obj->scale.z);
    }
    if (!(mode & 4)) {
        func_800333C8(&v, obj->rx);
        func_80033428(&v, -obj->ry);
        func_80033480(&v, obj->rz);
        out->x = v.x + obj->pos.x;
        out->y = v.y + obj->pos.y;
        out->z = v.z + obj->pos.z;
    } else {
        out->x = v.x;
        out->y = v.y;
        out->z = v.z;
    }
}
