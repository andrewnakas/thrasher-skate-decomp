#include "common.h"

u16 func_80034004(u8 *dst, u8 *src, u16 n);
u8 *func_8003453C(u8 *buf, s32 v, s32 frac);
u8 *func_80034654(u8 *buf, s32 v, u16 radix, u16 flags);
u8 *func_80034698(u8 *buf, s32 v, u16 radix, u16 flags);
u8 *func_80034758(u8 *buf, u32 v, s32 digits);

#define VA_ARG(ap, t) (ap += sizeof(t), *(t *) (ap - sizeof(t)))

s32 func_80034060(u8 *dst, u8 *src, u8 *ap) {
    u8 tmp[0x100];
    u8 *buf;
    u8 *fmt;
    u16 left;
    u16 n;
    s32 *p;
    s16 *q;
    long long l;
    s32 v;

    left = 0xFF;
    fmt = src;
    buf = dst;
    while (*fmt != 0) {
        if (left == 0) {
            break;
        }
        if (*fmt != '%') {
            *buf++ = *fmt;
            left--;
        } else {
            fmt++;
            switch (*fmt) {
            case 's':
                n = func_80034004(buf, VA_ARG(ap, u8 *), left);
                break;
            case 'c':
                *buf = VA_ARG(ap, s32);
                n = 1;
                break;
            case 'd':
                n = func_80034004(buf, func_80034654(tmp, VA_ARG(ap, s32), 10, 0), left);
                break;
            case 'u':
                n = func_80034004(buf, func_80034698(tmp, VA_ARG(ap, s32), 10, 0), left);
                break;
            case 'x':
                n = func_80034004(buf, func_80034698(tmp, VA_ARG(ap, s32), 16, 0), left);
                break;
            case 'o':
                n = func_80034004(buf, func_80034698(tmp, VA_ARG(ap, s32), 8, 0), left);
                break;
            case 'b':
                n = func_80034004(buf, func_80034698(tmp, VA_ARG(ap, s32), 2, 0), left);
                break;
            case 'f':
                n = func_80034004(buf, func_8003453C(tmp, VA_ARG(ap, s32), 0x10), left);
                break;
            case 'l':
                l = VA_ARG(ap, long long);
                if (l < 0) {
                    l = -l;
                    *buf++ = '-';
                    left--;
                }
                n = func_80034004(buf, func_80034654(tmp, l >> 32, 10, 0), left);
                buf += n;
                left -= n;
                n = func_80034004(buf, func_80034758(tmp, (u32) l >> 16, 0x10), left);
                break;
            case 'a':
                v = VA_ARG(ap, s32);
                n = func_80034004(buf, func_8003453C(tmp, v * 360, 0x10), left);
                break;
            case 'y':
                p = VA_ARG(ap, s32 *);
                n = func_80034004(buf, func_8003453C(tmp, p[0], 0x10), left);
                buf += n;
                *buf++ = ',';
                *buf++ = ' ';
                left -= (u16) (n + 2);
                n = func_80034004(buf, func_8003453C(tmp, p[1], 0x10), left);
                break;
            case 'z':
                p = VA_ARG(ap, s32 *);
                n = func_80034004(buf, func_8003453C(tmp, p[0], 0x10), left);
                buf += n;
                *buf++ = ',';
                *buf++ = ' ';
                left -= (u16) (n + 2);
                n = func_80034004(buf, func_8003453C(tmp, p[1], 0x10), left);
                buf += n;
                *buf++ = ',';
                *buf++ = ' ';
                left -= (u16) (n + 2);
                n = func_80034004(buf, func_8003453C(tmp, p[2], 0x10), left);
                break;
            case 'F':
                n = func_80034004(buf, func_8003453C(tmp, VA_ARG(ap, s32), 0xC), left);
                break;
            case 'A':
                v = VA_ARG(ap, s32);
                n = func_80034004(buf, func_8003453C(tmp, v * 360, 0xC), left);
                break;
            case 'Z':
                q = VA_ARG(ap, s16 *);
                n = func_80034004(buf, func_80034654(tmp, q[0], 10, 0), left);
                buf += n;
                *buf++ = ',';
                *buf++ = ' ';
                left -= (u16) (n + 2);
                n = func_80034004(buf, func_80034654(tmp, q[1], 10, 0), left);
                buf += n;
                *buf++ = ',';
                *buf++ = ' ';
                left -= (u16) (n + 2);
                n = func_80034004(buf, func_80034654(tmp, q[2], 10, 0), left);
                break;
            default:
                *buf = *fmt;
                n = 1;
                break;
            }
            if (n > left) {
                n = left;
            }
            buf += n;
            left -= n;
        }
        fmt++;
    }
    *buf = 0;
    left--;
    return 0xFF - left;
}
