#include <stdlib.h>
#include <unistd.h>

#include "cvector/include/cvector.h"

        
int main(int argc, char *argv[]) {

    struct CVector *vec = cvector_create(sizeof(int), NULL);

    cvector_free(vec);

    return 0;
}