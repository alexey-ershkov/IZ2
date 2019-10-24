//
// Created by Алексей on 2019-10-20.
//

#include "parallel_search.h"

enum switch_case {
    STATE_FALSE,
    STATE_TRUE,
    STATE_CHECK
};


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
    enum switch_case state = STATE_FALSE;
    int count = 0;
    for (int i = 0; i < input_len/2; ++i) {
        if (input[i] == '\'') {
            if (state == STATE_TRUE) {
                state = STATE_FALSE;
                if (!pthread_mutex_lock(mutex)) {
                    printf("Mutex error\n");
                    return (void*)-1;
                }
                if (count > data.max_counted) {
                    data.max_counted = count;
                    count = 0;
                }
                if (!pthread_mutex_unlock(mutex)) {
                    printf("Mutex error\n");
                    return (void*)-1;
                }
            } else if (state == STATE_FALSE && is_capital(input[i+1])) {
                state = STATE_TRUE;
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
    enum switch_case state = STATE_CHECK;
    int count = 0;
    int i = input_len/2 - 1;
    while (input[i] != '\0') {
        if (input[i] == '\'') {
            if (state == STATE_CHECK) {
                buffer_end = count - 1;
                count = 0;
                state = STATE_FALSE;
            }
            if (state == STATE_TRUE) {
                state = STATE_FALSE;
                if (!pthread_mutex_lock(mutex)) {
                    printf("Mutex error\n");
                    return (void*) -1;
                }
                if (count > data.max_counted) {
                    data.max_counted = count;
                    count = 0;
                }
                if (!pthread_mutex_unlock(mutex)) {
                    printf("Mutex error\n");
                    return (void*) -1;
                }
            } else if (state == STATE_FALSE && is_capital(input[i+1])) {
                state = STATE_TRUE;
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
    if (pthread_create(&thread1, NULL, from_start, input)) {
        printf("Pthread error\n");
        return -1;
    }
    if (pthread_create(&thread2, NULL, till_end, input)) {
        printf("Pthread error\n");
        return -1;
    }
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    if (buffer_start)
        if (buffer_start + buffer_end > data.max_counted)
            data.max_counted = buffer_end + buffer_start;
    return data.max_counted;
}

int parallel_search(char* input) {
    if (NULL == input) {
        printf("Empty input\n");
        return -1;
    }
    char* string_mass = (char*)malloc(strlen(input) * sizeof(char) + 1);
    if (!string_mass) {
        printf("Malloc error\n");
        return -1;
    }
    strcpy(string_mass, input);
    int output = parallel_str_search(string_mass);
    free(string_mass);
    return output;
}
