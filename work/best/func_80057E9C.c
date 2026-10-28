#include "common.h"

extern u8 D_8008AC68[];
extern u8 D_8008AC6C[];
extern u8 D_8008AC74[];

void sprintf(u8 *buf, u8 *fmt, ...);

void func_80057E9C(u32 value, u8 *buf) {
    u16 ms = value % 1000;
    u32 total = (value - ms) / 1000;
    u16 sec;
    u16 min;

    if ((u16) total < 1000) {
        sec = total;
        min = 0;
    } else {
        min = (u16) total / 1000;
        sec = total - min * 1000;
        min = ((u16) total - sec) / 1000;
    }
    if (value < 1000) {
        sprintf(buf, D_8008AC68, ms);
    } else if (value <= 999999) {
        sprintf(buf, D_8008AC6C, sec, ms);
    } else {
        sprintf(buf, D_8008AC74, min, sec, ms);
    }
}
