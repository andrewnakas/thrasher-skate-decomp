#include "common.h"

typedef struct {
    u8 n;
    u8 fl;
    u16 type;
} Trk;

typedef struct {
    u16 w0;
    u8 b2;
    u8 b3;
    s32 rate;
    s32 off8;
    Trk trk[1];
} Hdr;

typedef struct {
    u32 flags;
    u16 time;
    u16 pad6;
    s32 v8;
    s16 d[3];
} Key;

typedef struct {
    u32 time;
    s32 rate;
    u32 end;
    u32 next;
    Key *ptr;
    u8 pad14[8];
    s32 v1C;
    u8 *p20;
    Trk *trk;
    Key *p28;
    s32 dpos[4];
    s32 pos[4];
    s32 vel[3];
    s32 d58[3];
    s16 drot[58];
    Hdr *hdr;
    s32 fdc;
    u8 padE0[4];
    s32 flags;
    s32 save[3];
    u8 padF4[0x20];
    u8 ntrk;
    u8 b115;
    u8 pad116[2];
    s32 x118[3];
    s16 r124[3];
    s16 dr12A[3];
    s32 v130;
    s16 rot[58];
    u16 v1A8;
    u8 cnt1AA;
} Chan;

typedef struct {
    u8 pad0[4];
    s32 flags;
    u8 pad8[0x18];
    s32 s20;
    s32 s24;
    s32 s28;
    u8 pad2C[0xC];
    u8 *chans;
} Obj;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    u16 wC;
    s32 v10;
} Out;

extern s32 func_80032C28(s32, s32);
extern void func_80033428(Out *, s16);
extern u16 D_8006E5AC[];
extern s32 D_80089F40;
extern u16 D_80089F50;
extern s32 D_80089F54;

Out *func_800123B0(Obj *o, s32 dt, s32 flags, Out *out, u8 idx) {
    Chan *c;
    Hdr *hdr;
    Trk *trk;
    Key *p;
    s16 *h;
    s16 *ts;
    u16 *tu;
    u8 *tb;
    u8 *tp;
    u8 *r8;
    s32 cnt;
    s32 i;
    s32 j;
    s32 k;

    c = (Chan *)(o->chans + (idx * 0x1AC + 0x1AC));
    hdr = c->hdr;
    if (o->flags & 0x2000) {
        c->rot[7] = c->v1A8;
        o->flags &= ~0x2000;
    }
    out->x = 0;
    out->y = 0;
    out->z = 0;
    out->wC = 0;
    out->v10 = 0;
    c->fdc = flags;
    if (flags & 2) {
        s32 rate;
        s32 f;

        out->x = c->save[0];
        out->z = c->save[2];
        c->x118[0] = 0;
        c->x118[1] = 0;
        c->x118[2] = 0;
        rate = hdr->rate;
        c->rate = rate;
        c->end = (hdr->w0 & 0x7FFF) * rate;
        f = c->flags & 0x21;
        c->flags = f;
        if (hdr->b3 & 0x80) {
            c->flags = f | 0x10;
        }
        c->time = 0;
        c->next = 0;
        c->cnt1AA = 0;
        trk = hdr->trk;
        c->ntrk = hdr->b2 >> 4;
        c->p20 = (u8 *)trk + c->ntrk * 4 + hdr->off8;
        c->trk = trk;
        c->b115 = hdr->trk[0].n;
        c->ptr = (Key *)((u8 *)trk + c->ntrk * 4);
        if (hdr->w0 & 0x8000) {
            c->p28 = c->ptr;
            c->ptr = (Key *)((u8 *)c->ptr + 0x64);
        }
        for (i = 0; i < c->ntrk; trk++, i++) {
            p = c->ptr;
            cnt = 2;
            if (trk->type == 0) {
                u8 *q;

                {
                    s32 v = p->v8;
                    c->v1C = v;
                    out->v10 = v;
                }
                h = p->d;
                if (flags & 8) {
                    out->x = -(p->d[0] << 13);
                } else {
                    out->x = p->d[0] << 13;
                }
                out->z = h[2] << 13;
                c->v130 = h[1] << 13;
                if (c->flags & 0x10) {
                    tu = (u16 *)(h + 3);
                    if (flags & 8) {
                        for (j = 0; j < trk->n; j++) {
                            s32 m;
                            cnt += 2;
                            m = D_8006E5AC[j] * 3;
                            c->rot[m] = tu[0];
                            c->rot[m + 1] = -tu[1];
                            c->rot[m + 2] = -tu[2];
                            tu += 3;
                        }
                    } else {
                        for (j = 0; j < trk->n; j++) {
                            cnt += 2;
                            c->rot[j * 3] = tu[0];
                            c->rot[j * 3 + 1] = tu[1];
                            c->rot[j * 3 + 2] = tu[2];
                            tu += 3;
                        }
                    }
                    q = (u8 *)tu;
                } else {
                    r8 = (u8 *)(h + 3);
                    if (flags & 8) {
                        for (j = 0; j < trk->n; j++) {
                            s32 m;
                            cnt += 3;
                            m = D_8006E5AC[j] * 3;
                            c->rot[m] = r8[0] << 8;
                            c->rot[m + 1] = -((s8)r8[1] << 8);
                            c->rot[m + 2] = -((s8)r8[2] << 8);
                            r8 += 3;
                        }
                    } else {
                        for (j = 0; j < trk->n; j++) {
                            cnt += 3;
                            c->rot[j * 3] = r8[0] << 8;
                            c->rot[j * 3 + 1] = (s8)r8[1] << 8;
                            c->rot[j * 3 + 2] = (s8)r8[2] << 8;
                            r8 += 3;
                        }
                    }
                    q = r8;
                }
                if (p->flags & (1 << (trk->n + 2))) {
                    tp = q;
                    c->flags |= 0x40;
                    if (flags & 8) {
                        c->pos[0] = -((s8)tp[0] << 16);
                        c->pos[1] = -((s8)tp[1] << 16);
                    } else {
                        c->pos[0] = (s8)tp[0] << 16;
                        c->pos[1] = (s8)tp[1] << 16;
                    }
                    c->pos[2] = (s8)tp[2] << 16;
                    q = tp + 4;
                    cnt += 4;
                    c->pos[3] = (s8)tp[3] << 16;
                }
                cnt &= 3;
                if (cnt == 0) {
                    c->ptr = (Key *)q;
                } else {
                    cnt = 4 - cnt;
                    c->ptr = (Key *)(q + cnt);
                }
            } else {
                u8 *r;

                cnt = 0;
                if (trk->fl & 2) {
                    continue;
                }
                if (!(p->flags & 1)) {
                    r = (u8 *)p + 6;
                    cnt = 2;
                } else {
                    r = (u8 *)p->d;
                }
                if (p->flags & 2) {
                    ts = (s16 *)r;
                    if (flags & 8) {
                        c->x118[0] = -(ts[0] << 13);
                    } else {
                        c->x118[0] = ts[0] << 13;
                    }
                    c->x118[1] = ts[1] << 13;
                    r = (u8 *)(ts + 3);
                    cnt += 2;
                    c->x118[2] = ts[2] << 13;
                }
                if (p->flags & 4) {
                    if (c->flags & 0x10) {
                        tu = (u16 *)r;
                        if (flags & 8) {
                            c->r124[0] = tu[0];
                            c->r124[1] = -tu[1];
                            c->r124[2] = -tu[2];
                        } else {
                            c->r124[0] = tu[0];
                            c->r124[1] = tu[1];
                            c->r124[2] = tu[2];
                        }
                        r = (u8 *)(tu + 3);
                        cnt += 2;
                    } else {
                        r8 = r;
                        if (flags & 8) {
                            c->r124[0] = r8[0] << 8;
                            c->r124[1] = -((s8)r8[1] << 8);
                            c->r124[2] = -((s8)r8[2] << 8);
                        } else {
                            c->r124[0] = r8[0] << 8;
                            c->r124[1] = (s8)r8[1] << 8;
                            c->r124[2] = (s8)r8[2] << 8;
                        }
                        r = r8 + 3;
                        cnt += 3;
                    }
                } else {
                    c->dr12A[0] = 0;
                    c->r124[0] = 0;
                    c->dr12A[1] = 0;
                    c->r124[1] = 0;
                    c->dr12A[2] = 0;
                    c->r124[2] = 0;
                }
                cnt &= 3;
                if (cnt == 0) {
                    c->ptr = (Key *)r;
                } else {
                    cnt = 4 - cnt;
                    c->ptr = (Key *)(r + cnt);
                }
            }
        }
        c->next += c->rate;
    } else {
        u32 key;

        c->time += func_80032C28(dt, D_80089F40) >> 16;
        p = c->ptr;
        if (p == NULL) {
            return NULL;
        }
        if (p->flags == 0) {
            return NULL;
        }
        trk = c->trk;
        if (c->time >= c->next) {
                    do {
                if (p->flags != 0) {
                    key = p->time;
                    if (c->time >= key) {
                        do {
                            u32 f = p->flags;
                            u32 ti = f >> 28;

                            cnt = 2;
                            if (trk[ti].type == 0) {
                                s32 bit;
                                u8 *q;

                                q = (u8 *)p + 6;
                                if (f & 1) {
                                    s32 v;
                                    q = (u8 *)p->d;
                                    v = p->v8;
                                    cnt = 0;
                                    c->v1C = v;
                                    out->v10 = v;
                                }
                                bit = 2;
                                if (p->flags & bit) {
                                    ts = (s16 *)q;
                                    if (flags & 8) {
                                        c->vel[0] = -(ts[0] << 8);
                                    } else {
                                        c->vel[0] = ts[0] << 8;
                                    }
                                    c->vel[2] = ts[2] << 8;
                                    q = (u8 *)(ts + 3);
                                    cnt += 2;
                                    c->vel[1] = ts[1] << 8;
                                }
                                for (j = 0; j < trk[ti].n; j++) {
                                    bit <<= 1;
                                    if (p->flags & bit) {
                                        if (c->flags & 0x10) {
                                            tu = (u16 *)q;
                                            if (flags & 8) {
                                                k = D_8006E5AC[j] * 3;
                                                c->drot[k++] = tu[0];
                                                c->drot[k++] = -tu[1];
                                                c->drot[k] = -tu[2];
                                            } else {
                                                k = j * 3;
                                                c->drot[k++] = tu[0];
                                                c->drot[k++] = tu[1];
                                                c->drot[k] = tu[2];
                                            }
                                            q = (u8 *)(tu + 3);
                                            cnt += 2;
                                        } else {
                                            tb = q;
                                            if (flags & 8) {
                                                k = D_8006E5AC[j] * 3;
                                                c->drot[k++] = (s8)tb[0] << 7;
                                                c->drot[k++] = -((s8)tb[1] << 7);
                                                c->drot[k] = -((s8)tb[2] << 7);
                                            } else {
                                                k = j * 3;
                                                c->drot[k++] = (s8)tb[0] << 7;
                                                c->drot[k++] = (s8)tb[1] << 7;
                                                c->drot[k] = (s8)tb[2] << 7;
                                            }
                                            q = tb + 3;
                                            cnt += 3;
                                        }
                                    }
                                }
                                bit <<= 1;
                                if (p->flags & bit) {
                                    tp = q;
                                    if (flags & 8) {
                                        c->dpos[0] = -((s8)q[0] << 16);
                                        c->dpos[1] = -((s8)q[1] << 16);
                                    } else {
                                        c->dpos[0] = (s8)q[0] << 16;
                                        c->dpos[1] = (s8)q[1] << 16;
                                    }
                                    q = tp + 4;
                                    c->dpos[2] = (s8)tp[2] << 16;
                                    cnt += 4;
                                    c->dpos[3] = (s8)tp[3] << 16;
                                    c->dpos[0] >>= 2;
                                    c->dpos[1] >>= 2;
                                    c->dpos[2] >>= 2;
                                    c->dpos[3] >>= 2;
                                }
                                cnt &= 3;
                                if (cnt == 0) {
                                    c->ptr = (Key *)q;
                                } else {
                                    cnt = 4 - cnt;
                                    c->ptr = (Key *)(q + cnt);
                                }
                            } else {
                                u8 *r;

                                p = c->ptr;
                                r = (u8 *)p->d;
                                if (p->flags & 1) {
                                    cnt = 0;
                                } else {
                                    r = (u8 *)p + 6;
                                }
                                if (p->flags & 2) {
                                    ts = (s16 *)r;
                                    if (flags & 8) {
                                        c->d58[0] = -(ts[0] << 8);
                                    } else {
                                        c->d58[0] = ts[0] << 8;
                                    }
                                    c->d58[1] = ts[1] << 8;
                                    r = (u8 *)(ts + 3);
                                    cnt += 2;
                                    c->d58[2] = ts[2] << 8;
                                }
                                if (p->flags & 4) {
                                    if (c->flags & 0x10) {
                                        tu = (u16 *)r;
                                        if (flags & 8) {
                                            c->dr12A[0] = tu[0];
                                            c->dr12A[1] = -tu[1];
                                            c->dr12A[2] = -tu[2];
                                        } else {
                                            c->dr12A[0] = tu[0];
                                            c->dr12A[1] = tu[1];
                                            c->dr12A[2] = tu[2];
                                        }
                                        r = (u8 *)(tu + 3);
                                        cnt += 2;
                                    } else {
                                        tb = r;
                                        if (flags & 8) {
                                            c->dr12A[0] = (s8)tb[0] << 7;
                                            c->dr12A[1] = -((s8)tb[1] << 7);
                                            c->dr12A[2] = -((s8)tb[2] << 7);
                                        } else {
                                            c->dr12A[0] = (s8)tb[0] << 7;
                                            c->dr12A[1] = (s8)tb[1] << 7;
                                            c->dr12A[2] = (s8)tb[2] << 7;
                                        }
                                        r = tb + 3;
                                        cnt += 3;
                                    }
                                }
                                cnt &= 3;
                                if (cnt == 0) {
                                    c->ptr = (Key *)r;
                                } else {
                                    cnt = 4 - cnt;
                                    c->ptr = (Key *)(r + cnt);
                                }
                            }
                            p = c->ptr;
                        } while (p->time == key);
                    }
                    for (i = 0; i < c->ntrk; i++) {
                        if (trk[i].type == 0) {
                            c->cnt1AA++;
                            c->v130 += c->vel[1];
                            out->x = c->vel[0];
                            out->z = c->vel[2];
                            k = 0;
                            for (j = 0; j < trk[i].n; j++) {
                                c->rot[k] += c->drot[k];
                                k++;
                                c->rot[k] += c->drot[k];
                                k++;
                                c->rot[k] += c->drot[k];
                                k++;
                            }
                            if (c->flags & 0x40) {
                                c->pos[0] += c->dpos[0];
                                c->pos[1] += c->dpos[1];
                                c->pos[2] += c->dpos[2];
                                c->pos[3] += c->dpos[3];
                            }
                        } else if (!(trk[i].fl & 2)) {
                            c->x118[0] += c->d58[0];
                            c->x118[1] += c->d58[1];
                            c->x118[2] += c->d58[2];
                            c->r124[0] += c->dr12A[0];
                            c->r124[1] += c->dr12A[1];
                            c->r124[2] += c->dr12A[2];
                        }
                    }
                }
                c->next += c->rate;
            } while (c->time >= c->next);
        }
    }
    if (c->next >= c->end) {
        c->save[0] = c->vel[0];
        c->save[1] = c->vel[1];
        c->save[2] = c->vel[2];
    }
    out->wC = c->rot[1];
    out->v10 = c->v1C;
    if (D_80089F54 == 0) {
        out->wC = out->wC - D_80089F50;
        func_80033428(out, D_80089F50);
    } else {
        out->wC = D_80089F50 - out->wC;
        func_80033428(out, -D_80089F50);
    }
    if (o->flags & 8) {
        out->x = func_80032C28(out->x, o->s20);
        out->y = func_80032C28(out->y, o->s24);
        out->z = func_80032C28(out->z, o->s28);
    }
    return out;
}
