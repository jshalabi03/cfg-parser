int f2(int i) { return i + 2; }
int f1(int i) { return f2(2) + i + 1; }
int f0(int i) { return f1(1) + f2(2); }
int pointed(int i) { return i; }
int not_called(int i) { return 0; }

int main(int argc, char **argv) {
    int (*f)(int);
    f0(1);
    f1(1);
    f = pointed;
    if (argc == 1)
        f(1);
    if (argc == 2)
        not_called(1);
    return 0;
}