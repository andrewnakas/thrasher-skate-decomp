#include "common.h"

typedef struct {
    u8 pad[0x2C];
} Rec_800356DC;

extern Rec_800356DC D_800A6084[];
extern u16 D_8008B128;

Rec_800356DC *func_800356DC(u32 a0) {
    if (a0 >= D_8008B128) {
        return D_800A6084;
    }
    return &D_800A6084[a0];
}
