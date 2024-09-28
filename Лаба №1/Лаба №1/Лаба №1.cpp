#include <iostream>

//#include "CustomList.h"
#include "CustomVector.h"
#include "CustomVector.cpp"

int main() {
    CustomVector<int> intArray;

    for (int i = 0; i < 10; i++) {
        intArray.PushBack(i + 15);
    }

    intArray.Print();
}