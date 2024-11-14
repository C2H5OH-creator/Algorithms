#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <stack>
#include <algorithm>

// Функция слияния с поддержкой режима галопа
void Merge(std::vector<int>& array, int leftStart, int middle, int rightEnd) {
    // Копируем левую и правую части исходного массива для слияния
    std::vector<int> leftSubarray(array.begin() + leftStart, array.begin() + middle + 1);
    std::vector<int> rightSubarray(array.begin() + middle + 1, array.begin() + rightEnd + 1);

    int leftIndex = 0;   // Текущая позиция в левом подмассиве
    int rightIndex = 0;  // Текущая позиция в правом подмассиве
    int mergeIndex = leftStart; // Индекс для слияния в исходном массиве

    int gallopThreshold = 7; // Порог для включения режима галопа
    int leftGallopCount = 0; // Счётчик совпадений для включения галопа в левом подмассиве
    int rightGallopCount = 0; // Счётчик совпадений для включения галопа в правом подмассиве

    while (leftIndex < leftSubarray.size() && rightIndex < rightSubarray.size()) {
        if (leftSubarray[leftIndex] <= rightSubarray[rightIndex]) {
            array[mergeIndex++] = leftSubarray[leftIndex++];
            leftGallopCount++;
            rightGallopCount = 0;  // Сбросить счётчик для правого подмассива
        }
        else {
            array[mergeIndex++] = rightSubarray[rightIndex++];
            rightGallopCount++;
            leftGallopCount = 0;  // Сбросить счётчик для левого подмассива
        }

        // Проверяем, нужно ли включить режим галопа для левого подмассива
        if (leftGallopCount >= gallopThreshold) {
            int rightLimitIndex = std::lower_bound(rightSubarray.begin() + rightIndex, rightSubarray.end(), leftSubarray[leftIndex]) - rightSubarray.begin();
            while (rightIndex < rightLimitIndex) {
                array[mergeIndex++] = rightSubarray[rightIndex++];
            }
            leftGallopCount = 0;  // Сбрасываем счётчик после режима галопа
        }

        // Проверяем, нужно ли включить режим галопа для правого подмассива
        if (rightGallopCount >= gallopThreshold) {
            int leftLimitIndex = std::lower_bound(leftSubarray.begin() + leftIndex, leftSubarray.end(), rightSubarray[rightIndex]) - leftSubarray.begin();
            while (leftIndex < leftLimitIndex) {
                array[mergeIndex++] = leftSubarray[leftIndex++];
            }
            rightGallopCount = 0;  // Сбрасываем счётчик после режима галопа
        }
    }

    // Копируем оставшиеся элементы левого подмассива, если есть
    while (leftIndex < leftSubarray.size()) {
        array[mergeIndex++] = leftSubarray[leftIndex++];
    }

    // Копируем оставшиеся элементы правого подмассива, если есть
    while (rightIndex < rightSubarray.size()) {
        array[mergeIndex++] = rightSubarray[rightIndex++];
    }
}

// Функция для получения minrun
size_t GetMinRun(size_t n) {
    size_t r = 0;
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

// Функция сортировки вставками
template <typename T>
void InsertionSort(std::vector<T>& array, size_t startIdx, size_t endIdx) {
    for (size_t currentIdx = startIdx + 1; currentIdx <= endIdx; currentIdx++) {
        T currentValue = array[currentIdx];
        size_t positionIdx = currentIdx;

        // Перемещаем элементы, которые больше currentValue, на одну позицию вперёд
        while (positionIdx > startIdx && array[positionIdx - 1] > currentValue) {
            array[positionIdx] = array[positionIdx - 1];
            positionIdx--;
        }

        // Вставляем currentValue на его правильное место
        array[positionIdx] = currentValue;
    }
}

// Поиск run и его добавление в стек
std::vector<std::pair<int, int>> IdentifyRuns(std::vector<int>& array, size_t minrun) {
    std::vector<std::pair<int, int>> runs;
    size_t i = 0;
    while (i < array.size()) {
        size_t run_start = i;
        while (i + 1 < array.size() && array[i] <= array[i + 1]) {
            i++;
        }
        while (i + 1 < array.size() && array[i] > array[i + 1]) {
            i++;
        }
        size_t run_end = std::min(run_start + minrun - 1, array.size() - 1);
        InsertionSort(array, run_start, run_end);
        runs.emplace_back(run_start, run_end);
        i = run_end + 1;
    }
    return runs;
}

// Основная функция Timsort
template <typename T>
void Timsort(std::vector<T>& array) {
    size_t array_len = array.size();
    size_t minrun = GetMinRun(array_len);

    // Шаг 1: Определяем run и сортируем их
    auto runs = IdentifyRuns(array, minrun);

    // Шаг 2: Слияние отсортированных run
    while (runs.size() > 1) {
        std::vector<std::pair<int, int>> new_runs;
        for (size_t i = 0; i < runs.size(); i += 2) {
            if (i + 1 < runs.size()) {
                Merge(array, runs[i].first, runs[i].second, runs[i + 1].second);
                new_runs.emplace_back(runs[i].first, runs[i + 1].second);
            }
            else {
                new_runs.push_back(runs[i]);
            }
        }
        runs = new_runs;
    }
}

int main() {
    std::vector<int> array;
    for (int i = 0; i < 15; i++) {
        array.push_back(rand() % 10);  // генерируем массив случайных чисел
        printf("%d ", array[i]);
    }
    Timsort(array);
    std::cout << "\n\nОтсортированный массив:\n";
    for (int i = 0; i < array.size(); i++) {
        printf("%d ", array[i]);
    }
    return 0;
}
