//
// Created by Алексей on 2019-10-20.
//

#include "is_capital.h"

int is_capital(char x) {
    if (x >='A' && x <= 'Z')
        return 1;
    else
        return 0;
}