//
// Created by Алексей on 2019-10-20.
//

#include "parallel_search.h"


typedef struct {
    pthread_mutex_t mutex;
    int max_counted;
} data_t;

data_t data = {PTHREAD_MUTEX_INITIALIZER, 0};

int buffer_start = 0;
int buffer_end = 0;


void* from_start(void* args) {
    pthread_mutex_t *mutex = &data.mutex;
    char* input = (char*)args;
    int input_len = strlen(input);
    int state = 0;
    int count = 0;
    for (int i = 0; i < input_len/2; ++i) {
        if (input[i] == '\'') {
            if (state) {
                state = 0;
                assert(!pthread_mutex_lock(mutex));
                if (count > data.max_counted) {
                    data.max_counted = count;
                    count = 0;
                }
                assert(!pthread_mutex_unlock(mutex));
            } else if (!state && is_capital(input[i+1])) {
                state = 1;
            }
        } else if (state) {
            count++;
        }
    }
    if (count != 0)
        buffer_start = count;
    return 0;
}

void* till_end(void* args) {
    pthread_mutex_t *mutex = &data.mutex;
    char* input = (char*)args;
    int input_len = strlen(input);
    int state = 2;
    int count = 0;
    int i = input_len/2 - 1;
    while (input[i] != '\0') {
        if (input[i] == '\'') {
            if (state == 2) {
                buffer_end = count - 1;
                count = 0;
                state = 0;
            }
            if (state == 1) {
                state = 0;
                assert(!pthread_mutex_lock(mutex));
                if (count > data.max_counted) {
                    data.max_counted = count;
                    count = 0;
                }
                assert(!pthread_mutex_unlock(mutex));
            } else if (state == 0 && is_capital(input[i+1])) {
                state = 1;
            }
        } else if (state) {
            count++;
        }
        ++i;
    }
    return 0;
}

int parallel_str_search(char* input) {
    pthread_t thread1;
    pthread_t thread2;
    assert(!pthread_create(&thread1, NULL, from_start, input));
    assert(!pthread_create(&thread2, NULL, till_end, input));
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    if (buffer_start)
        if (buffer_start + buffer_end > data.max_counted)
            data.max_counted = buffer_end + buffer_start;
    return data.max_counted;
}

double parallel_search(char* input) {
    clock_t begin = clock();
    char* string_mass = (char*)malloc(MB100);
    assert(string_mass);
    strcpy(string_mass, input);
    parallel_str_search(string_mass);
    clock_t end = clock();
    double output = (double)(end - begin)/CLOCKS_PER_SEC;
    free(string_mass);
    return output;
}
