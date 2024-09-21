#include <iostream>

#include "CustomList.h"

int main() {
    auto list = new CustomList();

    for (int i = 0; i < 10; i++) {
        list->PushBack(i + 15);
    }

    list->Print();
    std::cout << list->GetValue(2);
    list->Clear();
}