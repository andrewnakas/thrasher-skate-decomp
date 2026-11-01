#include "common.h"

typedef struct {
    void *object;
    u16 offset;
    u16 pad;
} Entry;

extern s32 D_8008ADFC;
extern Entry D_8008AE00;
extern u16 D_8008AE08;

void *func_80012078(s32);
void func_80014450(void *);
void func_80014464(void *, Entry *);
void func_8001C488(s32, u16, void *, void (*)(void));
void func_8001A9DC(void);

void *func_8001A108(u32 mode) {
    Entry *entry;
    void *object;

    if (D_8008ADFC > 0) {
        return 0;
    }
    entry = (Entry *)((u8 *)&D_8008AE00 + D_8008ADFC * 8);
    object = func_80012078(3);
    if (object == 0) {
        return 0;
    }
    func_80014450(object);
    entry->offset = D_8008AE08 + D_8008ADFC * 6;
    func_80014464(object, entry);
    entry->object = object;
    switch (mode) {
    case 0:
        func_8001C488(2, 0xFFFF, object, func_8001A9DC);
        break;
    case 1:
        func_8001C488(3, 0xFFFF, object, func_8001A9DC);
        break;
    case 2:
        func_8001C488(4, 0xFFFF, object, func_8001A9DC);
        break;
    }
    D_8008ADFC++;
    return object;
}
