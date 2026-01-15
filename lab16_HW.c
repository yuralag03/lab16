#define _CRT_SECURE_NO_DEPRECATE
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double* create_random_array(int size, double min_val, double max_val);
void print_array(double* arr, int size, const char* name);
double* create_array_d_variant10(double* a, int n, double* b, int m, int* result_size);
void free_all(double* a, double* b, double* d);

int main() {
    setlocale(LC_ALL, "");
    srand(time(NULL));

    int n, m;
    double* a, * b, * d;
    int d_size;

    printf("Введите размер массива A (n > 0): ");
    scanf("%d", &n);

    printf("Введите размер массива B (m > 0): ");
    scanf("%d", &m);

    if (n <= 0 || m <= 0) {
        printf("Ошибка: размеры массивов должны быть положительными!\n");
        return -1;
    }

    a = create_random_array(n, -10.0, 10.0);
    b = create_random_array(m, -10.0, 10.0);

    if (a == NULL || b == NULL) {
        printf("Ошибка выделения памяти!\n");
        free_all(a, b, NULL);
        return -1;
    }

    printf("\n=== ИСХОДНЫЕ МАССИВЫ ===\n");
    print_array(a, n, "Массив A");
    print_array(b, m, "Массив B");

    printf("\n=== СОЗДАНИЕ МАССИВА D ===\n");
    printf("Правило:\n");
    printf("1. Все положительные элементы массива A (в порядке следования)\n");
    printf("2. Все отрицательные элементы массива B (в обратном порядке)\n");

    d = create_array_d_variant10(a, n, b, m, &d_size);

    if (d == NULL) {
        printf("Ошибка создания массива D!\n");
        free_all(a, b, NULL);
        return -1;
    }

    printf("\n=== РЕЗУЛЬТАТ: МАССИВ D ===\n");
    print_array(d, d_size, "Массив D");

    printf("\n=== СТАТИСТИКА ===\n");
    printf("Размер массива A: %d\n", n);
    printf("Размер массива B: %d\n", m);
    printf("Размер массива D: %d\n", d_size);

    int positive_count_a = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) positive_count_a++;
    }

    int negative_count_b = 0;
    for (int i = 0; i < m; i++) {
        if (b[i] < 0) negative_count_b++;
    }

    printf("Положительных элементов в A: %d\n", positive_count_a);
    printf("Отрицательных элементов в B: %d\n", negative_count_b);
    printf("Теоретический размер D: %d\n", positive_count_a + negative_count_b);

    free_all(a, b, d);

    printf("\nПрограмма завершена. Память освобождена.\n");

    return 0;
}

double* create_random_array(int size, double min_val, double max_val) {
    double* arr = (double*)malloc(size * sizeof(double));
    if (arr == NULL) return NULL;

    double range = max_val - min_val;

    for (int i = 0; i < size; i++) {
        arr[i] = min_val + ((double)rand() / RAND_MAX) * range;
    }

    return arr;
}

void print_array(double* arr, int size, const char* name) {
    if (arr == NULL || size <= 0) {
        printf("%s: массив пуст\n", name);
        return;
    }

    printf("%s [размер: %d]:\n", name, size);
    for (int i = 0; i < size; i++) {
        printf("[%3d] = %8.4f", i, arr[i]);
        if ((i + 1) % 5 == 0 || i == size - 1) printf("\n");
        else printf(" | ");
    }
}

void free_all(double* a, double* b, double* d) {
    if (a != NULL) free(a);
    if (b != NULL) free(b);
    if (d != NULL) free(d);
}

double* create_array_d_variant10(double* a, int n, double* b, int m, int* result_size) {
    int count_pos_a = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
            count_pos_a++;
        }
    }

    int count_neg_b = 0;
    for (int i = 0; i < m; i++) {
        if (b[i] < 0) {
            count_neg_b++;
        }
    }

    int total_size = count_pos_a + count_neg_b;

    if (total_size == 0) {
        *result_size = 0;
        return NULL;
    }

    double* d = (double*)malloc(total_size * sizeof(double));
    if (d == NULL) {
        *result_size = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
            d[index] = a[i];
            index++;
        }
    }

    for (int i = m - 1; i >= 0; i--) {
        if (b[i] < 0) {
            d[index] = b[i];
            index++;
        }
    }

    *result_size = total_size;
    return d;
}