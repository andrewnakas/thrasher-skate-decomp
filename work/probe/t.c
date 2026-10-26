extern int G;
extern int H;
void f(int *p) {
    int v;
    v = *p;
    G = v;
    H = *(p + 1) + G;
}
