#include <stdio.h>
#include "linear_search.h"


int main() {
    char str[10] = "abc'A''Af'";
    double output  = linear_search(str);
    printf("%lf", output);
    return 0;
}
