#include <iostream>

void foo() {
    static int a = 0; // Инициализируется только один раз
    a++;
    std::cout << a << std::endl;
}

int main() {
    foo(); // Выведет 1
    foo(); // Выведет 2
    foo(); // Выведет 3
    return 0;
}
