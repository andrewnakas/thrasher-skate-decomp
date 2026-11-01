#include "common.h"

extern char D_8008A8B8[];
extern char D_8008A8BC[];
s32 strcmp(const char *, const char *);

typedef struct {
    char c[2];
} Two4813C;

s32 func_8004813C(char *p) {
    char buf[3];
    char *b = buf;

    *(Two4813C *) buf = *(Two4813C *) p;
    buf[2] = 0;
    if (strcmp(b, D_8008A8B8) == 0) {
        return 1;
    }
    if (strcmp(b, D_8008A8BC) == 0) {
        return 5;
    }
    if (((u8 *) p)[0] == 10) {
        return 2;
    }
    if (((u8 *) p)[0] != 0) {
        return 4;
    }
    switch (((u8 *) p)[2]) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 9:
    case 10:
    case 11:
        return 3;
    default:
        return 4;
    }
}
