
#include "parallel_search.h"
#include "linear_search.h"

int main() {
    char str[10] = "Ad'Ahh'gAf";
    double  output = linear_search(str);
    printf("%lf\n", output);
    output = parallel_search(str);
    printf("%lf\n", output);
    return 0;
}
