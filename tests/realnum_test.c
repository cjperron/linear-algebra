#include"../lib/numeric/realnum.h"

int main() {
    realnum* a = realnum_from_frac(1, 3);
    realnum* b = realnum_from_frac(1, 3);
    realnum aux = realnum_add(a, b);
    realnum c = realnum_fracsimp(&aux);
    realnum_print_as_frac(&c);
    realnum_free(a);
    realnum_free(b);
    return 0;
}
