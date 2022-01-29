#include <iostream>

void constPtr() {
    int a = 1;
    const int *ptr_to_a = &a; // Указатель на константное значение
    int b = 2;
    int *const ptr_to_b = &b; // Константный указатель
    // *ptr_to_a = -1;  - Так нельзя
    *ptr_to_b = -2;
    ptr_to_a = &b;
    // ptr_to_b = &a; - Так нельзя
}

int main() {
    std::cout << "Hello!" << std::endl;
    constPtr();
    return 0;
}
