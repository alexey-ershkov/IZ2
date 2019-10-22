
#include "parallel_search.h"
#include "linear_search.h"

int main() {
    char str[10] = "Ad'Ahh'gAf";
    clock_t begin = clock();
    for (int i = 0; i < 1000; ++i) {
        linear_search(str);
    }
    clock_t end = clock();
    double output = (double)(end - begin)/(CLOCKS_PER_SEC * 1000);
    printf("%.10lf\n", output);
    begin = clock();
    for (int i = 0; i < 1000; ++i) {
        parallel_search(str);
    }
    end = clock();
    output = (double)(end - begin)/(CLOCKS_PER_SEC * 1000);
    printf("%.10lf\n", output);
    return 0;
}
