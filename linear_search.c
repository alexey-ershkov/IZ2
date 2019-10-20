//
// Created by Алексей on 2019-10-20.
//

#include "linear_search.h"

int is_capital(char x) {
    if (x >='A' && x <= 'Z')
        return 1;
    else
        return 0;
}

int linear_str_search(char* input) {
    int i = 0, count = 0, max_counted = 0, state = 0;
    while (input[i] != '\0'){
        if (input[i] == '\'')
        {
            if (state) {
                state = 0;
                if (count > max_counted) {
                    max_counted = count;
                    count = 0;
                }
            }
            else if (!state && is_capital(input[i+1]))
                state = 1;
        }
        else if (state)
            count++;
        i++;
    }
    return max_counted;
}

double linear_search(char* input)
{
    clock_t begin = clock();
    char* string_mass = (char*)malloc(MB100);
    assert(string_mass);
    strcpy(string_mass, input);
    int max = linear_str_search(string_mass);
    printf("%d\n", max);
    clock_t end = clock();
    double output = (double)(end - begin)/CLOCKS_PER_SEC;
    return output;
}