typedef int s32;
typedef unsigned int u32;

typedef struct { s32 x, y, z; } V3;
typedef struct { s32 x, y, z; } W3;
typedef union { V3 v; s32 a[3]; } U3;

extern void memcpy(void *d, void *s, u32 n);

void o1_field(V3 *p, V3 *q) { p->x = q->x; p->y = q->y; p->z = q->z; }

void o2_struct(V3 *p, V3 *q) { *p = *q; }

void o3_memcpy(V3 *p, V3 *q) { memcpy(p, q, 12); }

void o4_union(U3 *p, U3 *q) { *p = *q; }

void o5_loop(s32 *p, s32 *q) { s32 i; for (i = 0; i < 3; i++) { p[i] = q[i]; } }

void o6_byval(V3 *out, V3 v) { *out = v; }

void o7_elems(V3 *p, V3 *q) { s32 a = q->x, b = q->y, c = q->z; p->x = a; p->y = b; p->z = c; }

void o8_arr3(s32 *p, s32 *q) { p[0] = q[0]; p[1] = q[1]; p[2] = q[2]; }

void o9_stack(V3 *p, V3 *q) { V3 t; t.x = q->x; t.y = q->y; t.z = q->z; p->x = t.x; p->y = t.y; p->z = t.z; }

void o10_arr_copy(s32 *p, s32 *q) { s32 a[3]; a[0] = q[0]; a[1] = q[1]; a[2] = q[2]; p[0] = a[0]; p[1] = a[1]; p[2] = a[2]; }
