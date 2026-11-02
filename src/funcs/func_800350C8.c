#include "common.h"

typedef struct {
    s16 time;
    u16 val;
    u16 decay;
} Motor_800350C8;

typedef struct {
    s8 type;
    s8 cfg;
    u16 flags;
    u32 buttons;
    u32 pressed;
    u32 released;
    union {
        s32 axis0;
        struct {
            s8 b10;
            u8 b11;
            u8 b12;
            u8 b13;
        } b;
    } u;
    s32 axis1;
    s32 old0;
    s32 old1;
    Motor_800350C8 m[2];
} Port_800350C8;

typedef struct {
    u8 pad0[8];
    s8 slot;
    u8 pad9;
    u8 motor[2];
    u8 c;
    u8 d;
    u8 padE[6];
} Cfg_800350C8;

typedef struct {
    u8 type;
    u8 pad1[3];
    s32 port;
    u8 a[4];
} Slot_800350C8;

extern s32 D_8008B10C;
extern u32 D_8008A6E0;
#define D_8008A6DC (*(&D_8008A6E0 - 1)) /* unsplit lui/lhu: reach it through the neighbour */
extern Port_800350C8 D_800A6084[];
extern Cfg_800350C8 D_800A6244[];
extern Slot_800350C8 D_800A6294[];

void func_8003599C(void);
void func_800358A8(void);
s32 func_80035810(s32);
s32 func_8005EE34(s32, s32, s32);
s32 func_8005ED68(s32);
void func_8005F038(s32, u8 *, s32, Motor_800350C8 *);
s32 func_8005F000(s32, u8 *);

void func_800350C8(void) {
    u16 i;
    Port_800350C8 *port;
    Cfg_800350C8 *dev;
    Cfg_800350C8 *cfg;
    Cfg_800350C8 *cfgs;
    Slot_800350C8 *slot;
    u32 b;
    u32 bits;
    u32 old;
    s32 n;
    s32 flag;
    s32 st;
    s32 x;
    s32 y;
    u16 id;
    s32 k;
    u32 t;
    Motor_800350C8 *m;

    i = 0;
    func_8003599C();
    if (D_8008B10C != 0) {
        func_800358A8();
    }
    port = D_800A6084;
    for (; i < 10; i++, port++) {
        n = port->cfg;
        if (n == -1) {
            continue;
        }
        dev = NULL;
        slot = NULL;
        flag = 0;
        cfgs = D_800A6244;
        cfg = &cfgs[n];
        if (cfg->slot != -1 && (slot = &D_800A6294[cfg->slot], dev = cfg, n = slot->port, n != -1)) {
            port->flags &= ~1;
            switch (slot->type) {
                case 4:
                    port->type = 0;
                    break;
                case 7:
                    port->type = 1;
                    if (n < 0) {
                        flag = 1;
                    }
                    break;
                case 2:
                    port->type = 2;
                    break;
                case 1:
                    port->type = 3;
                    break;
                case 8:
                default:
                    port->type = -1;
                    break;
            }
        } else {
            port->flags |= 1;
            n = 0;
        }
        b = func_80035810((u16) n);
        bits = 0;
        switch (port->type) {
            case 0:
            case 1:
                if (b & 0x8000) {
                    bits |= 4;
                } else if (b & 0x2000) {
                    bits |= 8;
                }
                if (b & 0x1000) {
                    bits |= 1;
                } else if (b & 0x4000) {
                    bits |= 2;
                }
                if (b & 0x10) {
                    bits |= 0x10;
                }
                if (b & 0x80) {
                    bits |= 0x20;
                }
                if (b & 0x20) {
                    bits |= 0x40;
                }
                if (b & 0x40) {
                    bits |= 0x80;
                }
                if (b & 4) {
                    bits |= 0x100;
                }
                if (b & 8) {
                    bits |= 0x200;
                }
                if (b & 1) {
                    bits |= 0x400;
                }
                if (b & 2) {
                    bits |= 0x800;
                }
                if (b & 0x800) {
                    bits |= 0x1000;
                }
                if (b & 0x100) {
                    bits |= 0x2000;
                }
                flag = (u16) func_80035810(flag);
                if (flag != 0) {
                    port->type = 1;
                    t = func_80035810(slot->a[1] | (slot->a[0] << 8));
                    slot->a[0] = t >> 8;
                    slot->a[1] = t;
                    x = 0x8000;
                    y = 0x8000;
                    if (abs(slot->a[0] - 0x80) > 0x20) {
                        x = slot->a[0] << 8;
                    }
                    if (abs(slot->a[1] - 0x80) > 0x20) {
                        y = slot->a[1] << 8;
                    }
                    old = port->u.axis0;
                    port->u.axis0 = (x << 16) + y;
                    port->old0 = old;
                    x = 0x8000;
                    y = 0x8000;
                    if (abs(slot->a[2] - 0x80) > 0x20) {
                        x = slot->a[2] << 8;
                    }
                    if (abs(slot->a[3] - 0x80) > 0x20) {
                        y = slot->a[3] << 8;
                    }
                    old = port->axis1;
                    port->axis1 = (x << 16) + y;
                    port->old1 = old;
                }
                break;
            case 2:
                if (b & 0x8000) {
                    bits |= 4;
                } else if (b & 0x2000) {
                    bits |= 8;
                }
                if (b & 0x1000) {
                    bits |= 1;
                } else if (b & 0x4000) {
                    bits |= 2;
                }
                port->u.b.b10 = slot->a[0] + 0x80;
                if (abs(port->u.b.b10) < 9) {
                    port->u.b.b10 = 0;
                }
                port->u.b.b11 = slot->a[1];
                port->u.b.b12 = slot->a[2];
                port->u.b.b13 = slot->a[3];
                if (b & 0x10) {
                    bits |= 0x10;
                }
                if (port->u.b.b12 > 0x10) {
                    bits |= 0x20;
                }
                if (b & 0x20) {
                    bits |= 0x40;
                }
                if (port->u.b.b11 > 0x10) {
                    bits |= 0x80;
                }
                if (port->u.b.b13 > 0x10) {
                    bits |= 0x100;
                }
                if (b & 8) {
                    bits |= 0x200;
                }
                if (b & 0x800) {
                    bits |= 0x1000;
                }
                break;
            case 3:
            case 4:
                break;
        }
        {
            port->pressed = bits ^ port->buttons;
            port->released = port->buttons & port->pressed;
            port->buttons = bits;
        }
        id = dev->slot << 4;
        if (func_8005EE34(id, 2, 0) != 0) {
            port->flags |= 2;
            st = func_8005ED68(id);
            if (st == 0) {
                return;
            }
            if (st == 1) {
                dev->c = 0;
            }
            m = port->m;
            if (dev->c == 0) {
                func_8005F038(id, dev->motor, 2, m);
                if (st == 2 || (st == 6 && func_8005F000(id, &dev->d) != 0)) {
                    dev->c = 1;
                }
            } else {
                for (k = 0; k < 2; m++, k++) {
                    if (m->time != 0) {
                        m->time -= D_8008A6DC;
                        if (m->time <= 0) {
                            m->val = 0;
                        }
                        if (k == 0) {
                            if (m->val != 0) {
                                dev->motor[0] = 1;
                            } else {
                                dev->motor[0] = 0;
                            }
                        } else {
                            dev->motor[1] = m->val >> 8;
                        }
                        if (m->val < m->decay) {
                            m->val = 0;
                        } else {
                            m->val -= m->decay;
                        }
                    }
                }
            }
        } else {
            port->flags &= ~2;
        }
    }
}
