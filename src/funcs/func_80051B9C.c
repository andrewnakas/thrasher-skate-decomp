#include "common.h"

typedef struct {
    u8 pad0[4];
    u32 end;
    u32 pos;
    s32 file;
} Chunk_80051B9C;

typedef struct Queue_80051B9C {
    Chunk_80051B9C *chunk;
    s32 loops;
    struct Queue_80051B9C *next;
} Queue_80051B9C;

typedef struct {
    u8 pad0[2];
    u8 flag;
    u8 pad3[5];
    u8 *buf;
    u32 size;
    u8 pad10[8];
    u32 pos;
    u8 pad1C[0x10];
    Queue_80051B9C q;
} Stream_80051B9C;

extern s32 D_8008A9C8;
extern s8 D_800108B0[];
extern s8 D_8008A9D4[];

void func_80051B2C();
void func_80051B84();
s32 func_80037070(s32, u8 *, u32, void (*)(), Stream_80051B9C *, s32 *, s32 *);
void func_80051AE4(Queue_80051B9C *);
void func_80051F3C(Chunk_80051B9C *);
void func_80051F9C(Chunk_80051B9C *);

u32 func_80051B9C(Stream_80051B9C *s, u32 len, s32 *outpos, s32 sync) {
    s32 got;
    s32 sp24;
    Queue_80051B9C *q;
    Queue_80051B9C *n;
    u32 remain;
    u32 total;
    u8 *dst;
    s32 last;
    void (*cb)();

    if (D_8008A9C8 == 0) {
        printf(D_800108B0, D_8008A9D4, 0x522);
        exit(1);
    }
    remain = len;
    total = 0;
    *outpos = 0;
    q = &s->q;
    dst = s->buf + s->pos;
    while (q != NULL) {
        last = remain >= q->chunk->end - q->chunk->pos;
        if (last) {
            if (q->loops == 0 && q->next == NULL) {
                cb = sync ? func_80051B2C : func_80051B84;
            } else {
                cb = func_80051B84;
            }
        } else {
            cb = sync ? func_80051B2C : func_80051B84;
        }
        if (func_80037070(q->chunk->file, dst, remain, cb, s, &got, &sp24) != 4) {
            remain -= got;
            total += got;
            dst += got;
            q->chunk->pos += got;
            if (!last) {
                break;
            }
            if (q->loops != 0) {
                q->loops--;
                func_80051F9C(q->chunk);
            } else {
                n = q->next;
                if (n == NULL) {
                    break;
                }
                func_80051F3C(q->chunk);
                q->chunk = n->chunk;
                q->loops = n->loops;
                q->next = n->next;
                func_80051AE4(n);
            }
        } else {
            s->flag = 0;
            break;
        }
    }
    if (total < len) {
        *outpos = s->pos + total;
        remain = len - total;
        dst = s->buf + s->pos + total;
        while (remain != 0) {
            dst[1] = 1;
            remain -= 0x800;
            dst += 0x800;
        }
    }
    s->pos += len;
    if (s->pos >= s->size) {
        s->pos -= s->size;
    }
    return total;
}
