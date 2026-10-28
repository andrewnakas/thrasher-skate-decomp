typedef signed int s32;
typedef unsigned int u32;
typedef long long s64x;
typedef unsigned long long u64x;

typedef struct {
    s32 lo;
    s32 hi;
} W2;

typedef union {
    s64x w;
    W2 h;
} UW;

/* 1: plain 64-bit local, assigned then multiplied then shifted */
void e1(s32 *v, s32 k) {
    s64x p;
    p = v[0];
    p = p * k;
    v[0] = (s32) (p >> 16);
}

/* 2: inline, no named temp */
void e2(s32 *v, s32 k) {
    v[0] = (s32) (((s64x) v[0] * k) >> 16);
}

/* 3: unsigned typedef both operands */
void e3(s32 *v, s32 k) {
    u64x p;
    p = (u64x) v[0] * (u64x) k;
    v[0] = (s32) (p >> 16);
}

/* 4: two-word union viewed both ways */
void e4(s32 *v, s32 k) {
    UW u;
    u.w = (s64x) v[0] * k;
    v[0] = (u.h.hi << 16) | (u.h.lo >> 16);
}

/* 5: halves read through a pointer to the wide value */
void e5(s32 *v, s32 k) {
    s64x p = (s64x) v[0] * k;
    s64x *pp = &p;
    v[0] = (s32) (*pp >> 16);
}

/* 6: same union, both halves used in separate statements */
void e6(s32 *v, s32 k) {
    UW u;
    u.w = (s64x) v[0] * k;
    v[0] = u.h.hi;
    v[0] = (v[0] << 16) | (u.h.lo >> 16);
}
