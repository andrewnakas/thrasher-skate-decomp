#include "common.h"

typedef struct {
    u16 width, height;
    s32 offset;
    u16 origin_x, origin_y;
    u8 padC[4];
} Frame;

typedef struct {
    u16 count, flags;
    u8 pad4[8];
    s32 palette_offset;
    u16 format;
    u8 pad12[2];
    Frame frames[1];
} Texture;

typedef struct {
    u8 pad0[0x14];
    u16 *node;
    u16 flags;
    u8 pad1A[6];
    s32 amount;
    u16 color;
    u8 pad26[2];
    s32 scale_x, scale_y;
    s32 field30, field34;
    u8 pad38[0x18];
} DrawState;

extern s32 func_80015E8C(s32);
extern void func_80015F10(s32);
extern Texture *func_80019518(u16 *);
extern void func_8001954C(u16 *);
extern void func_80038B44(Texture *, s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_80038FC4(Texture *, s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_8003A2D4(s32, s32);
extern s32 D_8008AD88;
extern DrawState *D_8008AD90;
extern s32 D_8008AD94;

void func_80017C44(u16 index, s16 x, s16 y) {
    s32 width, height, scaled;
    u8 was_mapped;
    s32 mode, amount, option, offset, scale;
    u16 flags, format;
    u32 frame_index;
    DrawState *state;
    Texture *texture;
    Frame *frame;
    void *palette;

    if ((index & 0xFFFF) != 0xFFFF) {
        do {
            if (D_8008AD90 == NULL) {
                was_mapped = 0;
                D_8008AD90 = (DrawState *)func_80015E8C(D_8008AD94);
            } else {
                was_mapped = 1;
            }
            state = &D_8008AD90[D_8008AD88];
        } while (0);
        if (state->node != NULL) {
            texture = func_80019518(state->node);
            frame_index = index & 0xFFFF;
            if (frame_index < texture->count) {
                frame = &texture->frames[frame_index];
                scaled = 0;
                scale = state->scale_x;
                if (scale != 0x10000 || state->scale_y != scale) {
                    scaled = 1;
                }
                width = frame->width;
                height = frame->height;
                if (((*state->node & 0xE000) ^ 0x6000) != 0) {
                    x -= frame->origin_x;
                    y -= frame->origin_y;
                }
                mode = 0;
                amount = 0;
                option = 0;
                flags = state->flags;
                if (flags & 2) {
                    mode = 1;
                } else if (flags & 4) {
                    mode = 2;
                    if (!(flags & 1)) {
                        amount = state->amount;
                    }
                } else if (flags & 1) {
                    mode = 3;
                    option = 0;
                }
                offset = texture->palette_offset;
                palette = NULL;
                if (offset != 0) {
                    if (texture->flags & 1) {
                        palette = (u8 *)texture + offset + ((index & 0xFFFF) * 0x204);
                    } else {
                        palette = (u8 *)texture + offset;
                    }
                }
                if (state->field30 != 0) {
                    func_8003A2D4(state->field34, state->field30);
                }
                format = texture->format;
                if (scaled == 0) {
                    func_80038B44(texture, index & 0xFFFF, palette, mode, option, amount,
                        state->color, x, y, width, height, format & 0xFFFF, 0);
                } else {
                    func_80038FC4(texture, index & 0xFFFF, palette, mode, option, amount,
                        state->color, x, y, width, height, state->scale_x, state->scale_y,
                        format & 0xFFFF, 0);
                }
                if (state->field30 != 0) {
                    func_8003A2D4(0, 0);
                }
            }
            func_8001954C(state->node);
        }
        if (was_mapped == 0) {
            D_8008AD90 = NULL;
            func_80015F10(D_8008AD94);
        }
    }
}
