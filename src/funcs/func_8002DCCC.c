#include "common.h"

typedef struct {
    void (*fn)(u8 *self);
    u8 pad[8];
} E_8002DCCC;

extern E_8002DCCC D_8006F834[];

s32 func_8002DCCC(u8 *self) {
    if (self[3] < 3) {
        if (D_8006F834[self[3]].fn != 0) {
            D_8006F834[self[3]].fn(self);
        }
    } else {
        self[3] = 0;
    }
    return 0;
}
