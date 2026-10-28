typedef signed int s32;
typedef unsigned int u32;
typedef long long s64x;

typedef struct {
    u32 lo;
    u32 hi;
} W2;

typedef union {
    s64x w;
    W2 h;
} UW;

/* 7: union with unsigned halves, low half consumed first */
void e7(s32 *v, s32 k) {
    UW u;
    u.w = (s64x) v[0] * k;
    v[0] = (u.h.lo >> 16) | (u.h.hi << 16);
}

/* 8: same, halves in temporaries first */
void e8(s32 *v, s32 k) {
    UW u;
    u32 lo;
    u32 hi;
    u.w = (s64x) v[0] * k;
    lo = u.h.lo >> 16;
    hi = u.h.hi << 16;
    v[0] = lo | hi;
}
