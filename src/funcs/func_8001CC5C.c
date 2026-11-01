#include "common.h"

typedef struct {
    u16 id;
    u16 pad2;
    u8 *obj;
} CacheEnt;

extern CacheEnt *D_8008AE54;
extern u16 D_8008AE58;

u8 *func_80013ECC(u16 id, s32 mode);
void func_8001CD7C(u8 *obj, u16 id);
void func_8001CDA4(u8 *obj, u32 *flags);

u8 *func_8001CC5C(u32 *flags, u16 id, s32 *created) {
    u8 *obj = NULL;
    s32 found = 0;
    s32 i;
    s32 mode;

    *created = 0;
    if (!(*flags & 1)) {
        for (i = 0; i < D_8008AE58; i++) {
            if (D_8008AE54[i].id == id) {
                obj = D_8008AE54[i].obj;
                found = 1;
                break;
            }
        }
    }
    if (!found) {
        mode = 0;
        if (*flags & 0x8000000) {
            mode = 1;
        }
        if (*flags & 0x4000000) {
            mode |= 2;
        }
        if (*flags & 1) {
            mode |= 4;
        }
        obj = func_80013ECC(id, mode);
        if (obj == NULL) {
            return NULL;
        }
        func_8001CD7C(obj, id);
        *created = 1;
        func_8001CDA4(obj, flags);
    }
    return obj;
}
