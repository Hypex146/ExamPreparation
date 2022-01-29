#include <iostream>

class Base {
private:
    int number_;
    static int static_number_;
public:
    Base() : number_{0} {}

    explicit Base(int number) : number_{number} {}

    static void setStaticNumber(int number) { Base::static_number_ = number; }

    int getNumber() const { return number_; }

    static int getStaticNumber() { return Base::static_number_; }

};

int Base::static_number_ {0}; // Строго необходимо инициализировать вне функций, чтобы иметь возможность использовать!

int main() {
    Base obj;
    Base::setStaticNumber(7);
    std::cout << Base::getStaticNumber();
    return 0;
}

