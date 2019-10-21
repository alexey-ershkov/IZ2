//
// Created by Алексей on 2019-10-20.
//

#ifndef IZ2_PARALLEL_SEARCH_H
#define IZ2_PARALLEL_SEARCH_H

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include "is_capital.h"
#define MB100 104857600 // size of 100 MB in Bytes

double parallel_search(char* input);
int parallel_str_search(char* input);

#endif //IZ2_PARALLEL_SEARCH_H
