#include "common.h"

typedef struct {
    u8 pad0[4];
    u32 end;
    u8 pad8[8];
    u32 pos;
} Chunk_80053774;

typedef struct Queue_80053774 {
    Chunk_80053774 *chunk;
    s32 loops;
    struct Queue_80053774 *next;
} Queue_80053774;

typedef struct {
    u16 flags;
    u8 key;
    u8 pad3;
    u32 size;
    u8 pad8[8];
    u32 addr;
    u8 pad14[0xC];
    Queue_80053774 q;
    u8 pad2C[0x14];
    s32 voiceL;
    u8 pad44[8];
    s32 voiceR;
} Stream_80053774;

extern s32 D_8008A9EC;
extern u8 D_80010920[];
extern u8 D_8008AA00[];
extern Stream_80053774 D_800B134C;
typedef struct {
    s32 used;
    Queue_80053774 q;
} Pool_80053774;

extern s32 D_8008B460[2];
extern s32 D_8008B464[2];
extern u32 D_8008B480;

void func_800535EC();
void func_800536F8();
s32 func_80053BCC(Chunk_80053774 *, u32, u32, void (*)(), u32 *, s32 *);
void func_80053E98(Chunk_80053774 *);
void SpuIsTransferCompleted(s32);
void SpuSetIRQ(s32);
void SpuSetKey(s32, s32);

u32 func_80053774(u32 len, s32 *outpos, s32 sync) {
    u32 got;
    s32 sp1C;
    Stream_80053774 *st;
    Queue_80053774 *q;
    Queue_80053774 *n;
    Queue_80053774 *p;
    s32 last;
    u32 remain;
    u32 total;
    u32 addr;
    s32 res;
    s32 mask;
    u32 k;
    void (*cb)();

    if (D_8008A9EC == 0) {
        printf(D_80010920, D_8008AA00, 0x383);
        exit(1);
    }
    remain = len;
    q = &D_800B134C.q;
    *outpos = 0;
    addr = D_800B134C.addr;
    total = 0;
    if (D_800B134C.flags & 0x200) {
        addr >>= 1;
    }
    while (q != NULL) {
        last = remain >= q->chunk->end - q->chunk->pos;
        if (last) {
            if (q->loops == 0 && q->next == NULL) {
                cb = sync ? func_800535EC : func_800536F8;
            } else {
                cb = func_800536F8;
            }
        } else {
            cb = sync ? func_800535EC : func_800536F8;
        }
        res = func_80053BCC(q->chunk, addr, remain, cb, &got, &sp1C);
        if (res != 1) {
            remain -= got;
            total += got;
            if (D_800B134C.flags & 0x200) {
                addr += got >> 1;
            } else {
                addr += got;
            }
            if (!last) {
                break;
            }
            if (q->loops != 0) {
                q->loops--;
                func_80053E98(q->chunk);
            } else {
                n = q->next;
                if (n == NULL) {
                    break;
                }
                q->chunk = n->chunk;
                q->loops = n->loops;
                q->next = n->next;
                for (k = 0; k < 2; k++) {
                    if (n == &((Pool_80053774 *) D_8008B460)[k].q) {
                        D_8008B460[k * 4] = 0;
                        D_8008B480 = k;
                        break;
                    }
                }
            }
        } else {
            SpuIsTransferCompleted(1);
            SpuSetIRQ(0);
            mask = res << D_800B134C.voiceL;
            if (D_800B134C.flags & 0x200) {
                mask |= res << D_800B134C.voiceR;
            }
            SpuSetKey(0, mask);
            D_800B134C.key = res;
            break;
        }
    }
    if (total < len) {
        *outpos = D_800B134C.addr + total;
    }
    D_800B134C.addr += len;
    if (D_800B134C.addr >= D_800B134C.size) {
        D_800B134C.addr -= D_800B134C.size;
    }
    return total;
}
