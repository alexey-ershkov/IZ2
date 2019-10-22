//
// Created by Алексей on 2019-10-20.
//

#include "linear_search.h"



int linear_str_search(char* input) {
    int i = 0;
    int count = 0;
    int max_counted = 0;
    int state = 0;
    while (input[i] != '\0') {
        if (input[i] == '\'') {
            if (state) {
                state = 0;
                if (count > max_counted) {
                    max_counted = count;
                    count = 0;
                }
            } else if (!state && is_capital(input[i+1])) {
                state = 1;
            }
        } else if (state) {
            count++;
        }
        i++;
    }
    return max_counted;
}

int linear_search(char* input) {
    if (NULL == input) {
        printf("Empty input\n");
        return -1;
    }
    char* string_mass = (char*)malloc(strlen(input)* sizeof(char) + 1);
    if (!string_mass) {
        printf("Malloc error\n");
        return -1;
    }
    strcpy(string_mass, input);
    int output = linear_str_search(string_mass);
    free(string_mass);
    return output;
}
