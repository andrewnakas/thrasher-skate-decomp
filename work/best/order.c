typedef signed int s32;
typedef unsigned int u32;
typedef long long s64x;

typedef struct { u32 lo; u32 hi; } W2;
typedef union { s64x w; W2 h; } UW;

/* a: union, low consumed first */
s32 fa(s32 x, s32 y) {
    UW u;
    u.w = (s64x) x * y;
    return (u.h.lo >> 16) | (u.h.hi << 16);
}

/* b: union, low into a temp first */
s32 fb(s32 x, s32 y) {
    UW u;
    u32 lo;
    u.w = (s64x) x * y;
    lo = u.h.lo >> 16;
    return lo | (u.h.hi << 16);
}

/* c: DImode shift, cast */
s32 fc(s32 x, s32 y) {
    return (s32) (((s64x) x * y) >> 16);
}

/* d: DImode local then shift */
s32 fd(s32 x, s32 y) {
    s64x p = (s64x) x * y;
    return (s32) (p >> 16);
}

/* e: union with signed halves */
s32 fe(s32 x, s32 y) {
    union { s64x w; struct { s32 lo; u32 hi; } h; } u;
    u.w = (s64x) x * y;
    return (u.h.lo >> 16) | (u.h.hi << 16);
}

/* f: union halves stored to locals, low first, reused */
s32 ff(s32 x, s32 y) {
    UW u;
    u32 lo;
    u32 hi;
    u.w = (s64x) x * y;
    lo = u.h.lo;
    hi = u.h.hi;
    lo = lo >> 16;
    hi = hi << 16;
    return lo | hi;
}

/* g: low half computed in a separate statement before the multiply's high use */
s32 fg(s32 x, s32 y) {
    UW u;
    u32 r;
    u.w = (s64x) x * y;
    r = u.h.lo >> 16;
    r = r | (u.h.hi << 16);
    return r;
}

/* h: union pointer */
s32 fh(s32 x, s32 y) {
    UW u;
    UW *p = &u;
    p->w = (s64x) x * y;
    return (p->h.lo >> 16) | (p->h.hi << 16);
}
