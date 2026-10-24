#include "common.h"

extern s32 D_8008B188;
extern s32 D_8008B18C;

s32 func_800383E8(void) {
    switch (D_8008B188) {
        case 0:
            D_8008B18C = 0;
            break;
        case 1:
            D_8008B18C = 1;
            break;
        case 2:
            D_8008B18C = 2;
            break;
        case 3:
            D_8008B18C = 3;
            break;
        case 4:
            D_8008B18C = 4;
            break;
        case 5:
            D_8008B18C = 5;
            break;
        case 6:
            D_8008B18C = 6;
            break;
        case 7:
            D_8008B18C = 7;
            break;
        default:
            D_8008B18C = 8;
            break;
    }
    return D_8008B18C;
}
