#include "common.h"
typedef struct { u8 *obj; u8 *link; s32 pad; } Ent_8002DE60;
extern s32 func_8002C818(u8 *, u8 *);
extern u8 *D_8008B05C;
extern u8 *D_8008B060;
s32 func_8002DE60(u8 *obj) {
    Ent_8002DE60 *e;
    u8 k = obj[3] - 1;

    e = (Ent_8002DE60 *) D_8008B060;
    for (e--; (u8 *) e >= D_8008B05C; e--) {
        if (k == e->obj[3] && func_8002C818(obj, e->obj)) {
            e->link = obj;
            obj[3] = 0;
            return 0;
        }
    }
    return 0;
}
