#include "common.h"

typedef struct {
    u8 pos[4];
    u32 size;
    u8 name[16];
} CdFile;

typedef struct {
    s32 f0;
    s32 f4;
    u8 f8[8];
    u8 pad10[8];
    s32 f18;
    u8 pad1C[4];
    u8 name[0x40];
} FileRec;

extern s32 D_8008A5E8;
extern CdFile D_800A633C[40];
extern FileRec D_800A671C[];

u8 *func_80035EB8(u8 *);
s32 func_80036324(void);
void func_80036020(void);
void func_80036074(void);
void func_80036394(s32);
void func_800363B8(s32, s32, u32);
s32 func_80035F5C(s32, void *, s32);
s32 func_8001659C(u8 *);
s32 func_8001657C(u8 *, u8 *);
void func_8001653C(u8 *, u8 *, s32);
void func_80034D4C(void *, void *, s32);
CdFile *CdSearchFile(CdFile *, u8 *);
s32 func_8005D130(CdFile *);
void memset(void *, s32, s32);

s32 func_800363F8(u8 *name, s32 arg1, s32 mode) {
    CdFile file;
    u8 *path;
    u8 *p;
    s32 fd;
    FileRec *rec;
    CdFile *found;
    s32 i;

    path = func_80035EB8(name);
    fd = func_80036324();
    if (fd == 0) {
        return 0;
    }
    rec = &D_800A671C[fd];
    if (mode != 0) {
        rec->f4 = 1;
    }
    rec->f18 = arg1;
    func_80036020();
    if (D_8008A5E8 != 0) {
        D_8008A5E8 = 0;
        memset(D_800A633C, 0, 0x3C0);
    }
    p = path + func_8001659C(path) - 1;
    while (p != path) {
        if (p[-1] == '\\') {
            break;
        }
        p--;
    }
    found = NULL;
    for (i = 0; i < 40; i++) {
        if (func_8001657C(p, D_800A633C[i].name) == 0) {
            found = &D_800A633C[i];
            break;
        }
    }
    if (found == NULL) {
        i = 0;
        while ((found = CdSearchFile(&file, path)) == NULL && i < 3) {
            i++;
        }
        if (found == NULL) {
            func_80036394(fd);
            func_80036074();
            return 0;
        }
        for (i = 0; i < 40; i++) {
            if (D_800A633C[i].name[0] == 0) {
                func_80034D4C(&D_800A633C[i], found, 0x18);
                break;
            }
        }
    }
    func_800363B8(fd, func_8005D130(found), found->size);
    if (mode == 1) {
        if (func_80035F5C(fd, rec->f8, 8) == 0) {
            rec->f0 = 0;
            return 0;
        }
    }
    func_8001653C(rec->name, name, 0x3F);
    func_80036074();
    return fd;
}
