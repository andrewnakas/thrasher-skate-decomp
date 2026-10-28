#include "common.h"

extern s32 func_8002C454(void);
extern u16 D_8008AFA4;
extern u8 *D_8008AFA8;

u8 *func_8002C490(void) {
    u8 *p;
    s32 id;

    if (D_8008AFA8 == 0) {
        return 0;
    }
    id = func_8002C454();
    if (id != -1) {
        id = id - D_8008AFA4;
        p = D_8008AFA8 + id * 8;
        return p;
    }
    return 0;
}
