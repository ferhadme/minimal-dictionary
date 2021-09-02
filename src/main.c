#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

int main(void)
{
    dictionary *dict = malloc(sizeof(dictionary));
    printf("test\n");

    free(dict);
    return 0;
}
