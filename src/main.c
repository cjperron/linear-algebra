#include"../lib/numeric/realnum.h"
#include"../lib/vector/vector.h"
#include"../lib/matrix/matrix.h"

int main(int argc, char *argv[]) {
    realnum* num = realnum_from_aprox(1.0);
    realnum_print(num);

    const char* hola = "\nHola Mundo\n";

    printf("%s", hola);

    return 0;
}