#include "common.h"

typedef struct Node_80041538 {
    u8 pad0[0xC];
    u16 x;
    u16 y;
    u16 z;
    u8 pad12[0xE];
    struct Node_80041538 *child;
    struct Node_80041538 *next;
    u8 pad28[0xC];
} Node_80041538;

typedef struct {
    Node_80041538 *node;
    u32 pad4;
    u16 x;
    u16 y;
    u16 z;
    u8 next;
    u8 child;
} Out_80041538;

typedef struct {
    u8 pad0[0x10];
    Node_80041538 *nodes;
    u8 pad14[0x10];
    Out_80041538 *out;
} Tree_80041538;

extern void func_800416A8(Node_80041538 *);
extern s32 D_8008B348;
extern Tree_80041538 *D_8008B34C;
extern Out_80041538 *D_8008B350;
extern s32 D_8008B354;
extern Node_80041538 *D_8008B364[2];

Node_80041538 *func_80041538(Node_80041538 *n) {
    Node_80041538 *c;

    D_8008B364[++D_8008B354] = n;
    if (D_8008B348 & 1) {
        D_8008B350 = D_8008B34C->out;
        D_8008B350 += ((u32) n - (u32) D_8008B34C->nodes) / 52 + 1;
        D_8008B350->node = n;
        D_8008B350->x = n->x;
        D_8008B350->y = n->y;
        D_8008B350->z = n->z;
        if (n->child != NULL) {
            D_8008B350->child = ((u32) n->child - (u32) D_8008B34C->nodes) / 52 + 1;
        } else {
            D_8008B350->child = 0;
        }
        if (n->next != NULL) {
            D_8008B350->next = ((u32) n->next - (u32) D_8008B34C->nodes) / 52 + 1;
        } else {
            D_8008B350->next = 0;
        }
        D_8008B350++;
    }
    c = n->child;
    while (c != NULL) {
        c = func_80041538(c);
    }
    func_800416A8(n);
    D_8008B354--;
    return n->next;
}
