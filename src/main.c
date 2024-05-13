#include"../lib/numeric/realnum.h"
#include"../lib/vector/vector.h"
#include"../lib/matrix/matrix.h"



int main(int argc, char *argv[]) {

    linvector vec = linvector_new(3, 1.0, 2.0, 3.0);
    linvector_print(&vec, 3);
    printf("\n");

    linvector vec2 = linvector_new(3, 4.0, 5.0, 6.0);
    linvector_print(&vec2, 3);

    printf("\n");

    linvector vec3 = linvector_add(&vec, &vec2);
    linvector_print(&vec3, 3);
    printf("\n");
    
    linvector vec4 = linvector_sub(&vec, &vec2);
    linvector_print(&vec4, 3);
    printf("\n");

    linvector vec5 = linvector_mul(&vec, realnum_from_aprox(2.0));
    linvector_print(&vec5, 3);
    printf("\n");

    linvector vec6 = linvector_div(&vec, realnum_from_aprox(2.0));
    linvector_print(&vec6, 3);
    printf("\n");

    linvector vec7 = linvector_normalize(&vec);
    linvector_print(&vec7, 3);
    printf("\n");

    
    linvector_free(&vec);
    linvector_free(&vec2);
    linvector_free(&vec3);
    linvector_free(&vec4);
    linvector_free(&vec5);
    linvector_free(&vec6);
    linvector_free(&vec7);



    return 0;
}