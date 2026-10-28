typedef unsigned int u32;

void copy12(u32 *r) {
    u32 a = r[1], b = r[3], c = r[2], d = r[6], e = r[5], f = r[7];
    r[3] = a; r[1] = b; r[6] = c; r[2] = d; r[7] = e; r[5] = f;
}

void copy12b(u32 *d, u32 *s) {
    u32 a = s[0], b = s[1], c = s[2], e = s[3], f = s[4], g = s[5];
    u32 h = s[6], i = s[7], j = s[8], k = s[9], l = s[10], m = s[11];
    d[0] = a; d[1] = b; d[2] = c; d[3] = e; d[4] = f; d[5] = g;
    d[6] = h; d[7] = i; d[8] = j; d[9] = k; d[10] = l; d[11] = m;
}
