/*
  Сравните и выведите в консоль время работы последовательного и
  параллельного с использованием нескольких потоков алгоритмов,
  каждый из которых выделяет в динамической памяти символьный
  массив размером 100 Мб и выполняет поиск в тексте максимальной
  последовательности, заключенной между символами кавычек и
  начинающейся с буквы латинского алфавита в верхнем регистре.
*/

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
