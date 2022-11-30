int main() {
    int x;
    int y;
    int z;

    x = 1;
    y = x + 1;
    if (x < y) {
        x = y;
    } else {
        y = x;
        x = x * 2;
    }
    z = x + y;

    return 0;
}