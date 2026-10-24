#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    u8 padC[0x18];
    s32 unk24;
    u8 pad28[4];
    struct Unk80036758 *unk2C;
} Unk80036758;

typedef struct {
    s32 unk0;
    u8 pad4[0x5C];
} Unk80036758Rec;

extern Unk80036758Rec D_800A677C[];
extern Unk80036758 *D_8008B130;
void EnterCriticalSection(void);
void ExitCriticalSection(void);
void func_80036394(s32);

void func_80036758(s32 id) {
    Unk80036758 *node;

    if (D_800A677C[id - 1].unk0 == 0) {
        return;
    }
    EnterCriticalSection();
    node = D_8008B130;
    while (node != 0) {
        if (node->unk4 == id) {
            node->unk8 = 0;
            node->unk24 = 0;
        }
        node = node->unk2C;
    }
    ExitCriticalSection();
    func_80036394(id);
}
