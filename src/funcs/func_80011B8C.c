#include "common.h"

s32 func_80011CBC(void *);
void func_8003A7E4(void);
void func_80011C40(s32);
void func_80011BD4(void *);

s32 func_80011B8C(void *arg0) {
    if (func_80011CBC(arg0) != 0) {
        return 1;
    }
    func_8003A7E4();
    func_80011C40(-1);
    func_80011BD4(arg0);
    return 0;
}
