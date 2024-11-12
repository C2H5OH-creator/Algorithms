#include <iostream>
#include <vector>
#include <climits> 
#include <cmath>

// Функция слияния двух отсортированных подмассивов
void Merge(std::vector<int>& t_array, int p, int q, int r) {
    std::vector<int> LEFT(t_array.begin() + p, t_array.begin() + q + 1);
    std::vector<int> RIGHT(t_array.begin() + q + 1, t_array.begin() + r + 1);

    LEFT.push_back(INT_MAX);
    RIGHT.push_back(INT_MAX);

    int left = 0;  // Индекс для LEFT
    int right = 0;  // Индекс для RIGHT
    int gallop_threshold = 4;  // Порог галопа, можно настраивать

    // Слияние с галопом
    for (int k = p; k <= r; ++k) {
        // Если элементы в левой части меньше или равны правой
        if (LEFT[left] <= RIGHT[right]) {
            // Проверяем возможность перехода в галоп
            int gallop_count = 0;
            while (gallop_count < gallop_threshold && LEFT[left] <= RIGHT[right]) {
                t_array[k++] = LEFT[left++];
                gallop_count++;
            }
            k--;  // Корректируем индекс после выхода из цикла
        }
        else {
            // Если элемент из правого массива меньше
            int gallop_count = 0;
            while (gallop_count < gallop_threshold && RIGHT[right] < LEFT[left]) {
                t_array[k++] = RIGHT[right++];
                gallop_count++;
            }
            k--;  // Корректируем индекс после выхода из цикла
        }
    }
}

// Подсчёт minrun
size_t GetMinRun(size_t n) {
    size_t r = 0;
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

// Сортировка вставками
template <typename T>
void InsertionSort(std::vector<T>& array, size_t p, size_t r) {
    for (size_t i = p + 1; i <= r; i++) {
        T value = array[i];
        size_t j = i - 1;

        while (j >= p && array[j] > value) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = value;
    }
}

// Timsort: сортировка слиянием с вставками для маленьких подмассивов
template <typename T>
void Timsort(std::vector<T>& array) {
    size_t array_len = array.size();
    size_t minrun = GetMinRun(array_len);  // Получаем minrun для массива

    // Шаг 1: Сортировка вставками для маленьких подмассивов
    for (size_t start = 0; start < array_len; start += minrun) {
        size_t end = std::min(start + minrun - 1, array_len - 1);
        InsertionSort(array, start, end);
    }

    // Шаг 2: Слияние отсортированных подмассивов
    for (size_t size = minrun; size < array_len; size *= 2) {
        for (size_t start = 0; start < array_len; start += 2 * size) {
            size_t mid = std::min(start + size - 1, array_len - 1);
            size_t end = std::min(start + 2 * size - 1, array_len - 1);
            if (mid < end) {
                Merge(array, start, mid, end);
            }
        }
    }
}

int main()
{
    std::vector<int> array;
    for (int i = 0; i < 15; i++) {
        array.push_back(rand());
        printf("%d ", array[i]);
    }
    Timsort(array);
    std::cout << std::endl << std::endl;
    for (int i = 0; i < array.size(); i++) { printf("%d ", array[i]); }
}