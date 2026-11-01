#include "common.h"

typedef struct BspNode {
    u8 type;
    u8 axis;
    s16 dist;
    s32 pad4;
    struct BspNode *back;
    struct BspNode *front;
} BspNode;

void func_8002CF58(BspNode *, s32);
extern s16 D_8008AFC4[4];
extern s16 D_8008AFCC[4];
extern s32 D_8008B054;
extern BspNode *D_8008B058;

void func_8002CE0C(BspNode *node) {
    s32 da;
    s32 db;
    s32 sa;
    s32 sb;
    s16 *tbl;

    if (node != NULL) {
        if (node->type == 0x70) {
            tbl = D_8008AFC4;
            da = tbl[node->axis] + node->dist;
            db = D_8008AFCC[node->axis] + node->dist;
            sa = da > 0 ? 1 : (da < 0 ? -1 : 0);
            sb = db > 0 ? 1 : (db < 0 ? -1 : 0);
            D_8008B054 = da;
            D_8008B058 = node;
            func_8002CF58(node, da);
            if (sa == -1) {
                if (sb == -1) {
                    func_8002CE0C(node->back);
                } else if (sb == 1) {
                    func_8002CE0C(node->back);
                    func_8002CE0C(node->front);
                } else {
                    func_8002CE0C(node->back);
                }
            } else if (sa == 1) {
                if (sb == -1) {
                    func_8002CE0C(node->front);
                    func_8002CE0C(node->back);
                } else {
                    func_8002CE0C(node->front);
                }
            } else {
                if (sb == -1) {
                    func_8002CE0C(node->back);
                } else if (sb == 1) {
                    func_8002CE0C(node->front);
                } else {
                    func_8002CE0C(node->back);
                    func_8002CE0C(node->front);
                }
            }
        } else if (node->type == 0x6C) {
            func_8002CF58(node, D_8008B054);
        }
    }
}
