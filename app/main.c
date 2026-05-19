#include "../src/binary_io.h"

#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int ver = binary_io_version();
    printf("binary_io_version: %d\n", ver);
    return 0;
}
