#include "common.h"
typedef struct { u8 pad[0x24]; s16 unk24; } Unk;
extern Unk *D_8008ACA0;
void func_8003BE34(s16);
void func_80011D34(s16 arg0) {
    D_8008ACA0->unk24 = arg0;
    func_8003BE34(arg0);
}
