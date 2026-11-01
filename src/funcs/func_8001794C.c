#include "common.h"

typedef struct Node {
    s16 id;
    u16 flags;
    struct Node *next;
    s32 handle, offset;
} Node;

typedef struct {
    u16 count, flags;
    u8 pad4[8];
    s32 palette_offset;
} Texture;

typedef struct {
    u16 id, count;
    u16 colors[256];
} Palette;

typedef struct {
    u8 pad0[0x14];
    u16 width, height;
    s32 offset;
} FrameView;

extern s32 func_800159D8(s32);
extern s32 func_80015E8C(s32);
extern void func_80015F10(s32);
extern Node *func_80019444(void);
extern Texture *func_80019518(Node *);
extern void func_8001954C(Node *);
extern Node *func_80019630(u32);
extern s32 func_80019670(u32);
extern s32 func_80036A78(void *, u32, u16);
extern s32 func_80036B18(void *);
extern s32 func_80036BF4(void *, s32);
extern void func_80039D90(Palette *);
extern s32 printf(char *, ...);
extern char D_80089FB0[];
extern void *D_8008AD64;

Node *func_8001794C(s16 id, s32 shared) {
    s32 category, key, handle, offset, cached;
    Node *node;
    s32 palette_count, i, j, transparent, first, end, frame_index;
    s32 value; /* Cached lookup result, then pixel count. */
    u16 *colors;
    u8 *pixels;
    FrameView *frame;
    u16 old;
    u32 color;

    category = id & 0xE000;
    if (category != 0x4000 && category != 0x6000 && category != 0xC000) {
        return NULL;
    }
    key = id & 0xFFFF;
    node = func_80019630(key);
    if (node != NULL) {
        return node;
    }
    value = func_80019670(key);
    cached = 1;
    if (value != 0) {
        if (((Node *)value)->flags & 1) {
            shared = 1;
        }
        handle = ((Node *)value)->handle;
        offset = ((Node *)value)->offset;
    } else {
        cached = 0;
        offset = 0;
        if (func_80036A78(D_8008AD64, key, 0) != 0) {
            return NULL;
        }
        handle = func_800159D8(func_80036B18(D_8008AD64));
        if (handle == 0) {
            return NULL;
        }
        func_80036BF4(D_8008AD64, func_80015E8C(handle));
        func_80015F10(handle);
        printf(D_80089FB0);
    }
    node = func_80019444();
    if (node == NULL) {
        return NULL;
    }
    node->flags = 0;
    if (shared != 0) {
        node->flags = 1;
    }
    if (cached != 0) {
        node->flags |= 2;
    }
    node->id = id;
    node->handle = handle;
    node->offset = offset;
    /* The saved handle and offset become the mapped base and palette cursor. */
    handle = (s32)func_80019518(node);
    palette_count = 1;
    if (((Texture *)handle)->palette_offset != 0) {
        offset = handle + ((Texture *)handle)->palette_offset;
        if (((Texture *)handle)->flags & 1) {
            palette_count = ((Texture *)handle)->count;
        }
        for (i = 0; i < palette_count; i++) {
            transparent = -1;
            colors = ((Palette *)offset)->colors;
            for (j = 0; j < ((Palette *)offset)->count; j++) {
                if (colors[j] == 0x7C1F) {
                    transparent = j;
                    break;
                }
            }
            if ((u32)(transparent + 1) >= 2) {
                if (palette_count == 1) {
                    end = ((Texture *)handle)->count;
                    first = 0;
                } else {
                    first = i;
                    end = i + 1;
                }
                for (frame_index = first; frame_index < end; frame_index++) {
                    frame = (FrameView *)((u8 *)handle + frame_index * 0x10);
                    value = frame->width * frame->height;
                    pixels = (u8 *)handle + frame->offset;
                    for (j = 0; j < value; j++) {
                        color = *pixels;
                        if (color == transparent) {
                            *pixels = 0;
                        } else if (color == 0) {
                            *pixels = transparent;
                        }
                        pixels++;
                    }
                }
                old = colors[transparent];
                colors[transparent] = colors[0];
                colors[0] = old;
            }
            func_80039D90((Palette *)offset);
            offset += sizeof(Palette);
        }
    }
    func_8001954C(node);
    return node;
}
