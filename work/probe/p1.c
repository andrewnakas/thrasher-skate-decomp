extern unsigned char *A;
extern unsigned char *B;
void g(unsigned char *);

/* 1: do-while, i++ at top, recompute in cond */
void f1(void) {
    int i;
    i = 0;
    if (A != B) {
        do {
            i++;
            g(B - i * 16);
        } while (A < B - i * 16);
    }
}

/* 2: do-while with p local */
void f2(void) {
    int i;
    unsigned char *p;
    i = 0;
    if (A != B) {
        i++;
        do {
            p = B - i * 16;
            g(p);
            i++;
        } while (A < p);
        i--;
    }
}

/* 3: for with (i+1) */
void f3(void) {
    int i;
    i = 0;
    if (A != B) {
        for (i = 0; A < B - (i + 1) * 16; i++)
            g(B - (i + 1) * 16);
    }
}

/* 4: while with pre-increment in cond */
void f4(void) {
    int i;
    i = 0;
    if (A != B) {
        while (A < B - (++i) * 16)
            g(B - i * 16);
    }
}

/* 5: do-while, i++ at top, shift form */
void f5(void) {
    int i;
    i = 0;
    if (A != B) {
        do {
            i++;
            g(B - (i << 4));
        } while (A < B - (i << 4));
    }
}

/* 6: infinite for with break */
void f6(void) {
    int i;
    unsigned char *p;
    i = 0;
    if (A != B) {
        for (;;) {
            i++;
            p = B - i * 16;
            if (!(A < p))
                break;
            g(p);
        }
    }
}

/* 7: i starts at 1, for with empty init */
void f7(void) {
    int i;
    i = 0;
    if (A != B) {
        i = 1;
        for (; A < B - i * 16; i++)
            g(B - i * 16);
    }
}

/* 8: do-while then use i in a dead-looking but live way: store to B */
void f8(void) {
    int i;
    i = 0;
    if (A != B) {
        do {
            i++;
            g(B - i * 16);
        } while (A < B - i * 16);
        if (i < 0)
            g(B);
    }
}

/* 9: pointer biv + counter */
void f9(void) {
    int i;
    unsigned char *p;
    i = 0;
    if (A != B) {
        p = B;
        do {
            i++;
            p -= 16;
            g(p);
        } while (A < p);
    }
}

/* 10: do-while, condition via count compare against A - B */
void f10(void) {
    int i;
    i = 0;
    if (A != B) {
        do {
            i++;
            g(B - i * 16);
        } while ((unsigned)(B - A) > (unsigned)i * 16);
    }
}

/* 11: while(1) with counter, break at top */
void f11(void) {
    int i;
    i = 0;
    if (A != B) {
        while (1) {
            i++;
            if (!(A < B - i * 16))
                break;
            g(B - i * 16);
        }
    }
}

/* 12: do-while where i is also passed to g indirectly via a global store */
void f12(void) {
    int i;
    i = 0;
    if (A != B) {
        do {
            i++;
            g(B - i * 16);
        } while (A < B - i * 16);
        A = B;
    }
}
