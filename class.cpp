#include <iostream>

#define MAS_LEN 10

class Base {
private:
    int number_;
    int static_mas_[MAS_LEN];
    int *dynamic_mas_;

    int *initDynamicMas(int len) const {
        int *mas = new int[len];
        for (int i = 0; i < len; i++) {
            mas[i] = 0;
        }
        return mas;
    }

public:
    Base() : number_{0}, static_mas_{}, dynamic_mas_{initDynamicMas(MAS_LEN)} {
        std::cout << "First constructor" << std::endl;
    }

    explicit Base(int number) : static_mas_{}, number_{number}, dynamic_mas_{initDynamicMas(MAS_LEN)} {
        std::cout << "Second constructor" << std::endl;
    }

    Base(const Base &obj) : Base() {
        std::cout << "Copy constructor" << std::endl;
        number_ = obj.number_;
        for (int i = 0; i < MAS_LEN; i++) {
            static_mas_[i] = obj.static_mas_[i];
            dynamic_mas_[i] = obj.dynamic_mas_[i];
        }
    }

    Base(Base &&obj) noexcept: number_{obj.number_}, static_mas_{}, dynamic_mas_{obj.dynamic_mas_} {
        std::cout << "Move constructor" << std::endl;
        for (int i = 0; i < MAS_LEN; i++) {
            static_mas_[i] = obj.static_mas_[i];
        }
        obj.dynamic_mas_ = nullptr;
    }

    Base &operator=(const Base &obj) {
        std::cout << "Copy operator" << std::endl;
        if (this == &obj) { return *this; }
        number_ = obj.number_;
        for (int i = 0; i < MAS_LEN; i++) {
            static_mas_[i] = obj.static_mas_[i];
            dynamic_mas_[i] = obj.dynamic_mas_[i];
        }
        return *this;
    }

    Base &operator=(Base &&obj) noexcept {
        std::cout << "Move operator" << std::endl;
        if (this == &obj) { return *this; }
        delete[] dynamic_mas_;
        number_ = obj.number_;
        dynamic_mas_ = obj.dynamic_mas_;
        for (int i = 0; i < MAS_LEN; i++) {
            static_mas_[i] = obj.static_mas_[i];
        }
        obj.dynamic_mas_ = nullptr;
        return *this;
    }

    ~Base() {
        //std::cout << "Destructor" << std::endl;
        delete[] dynamic_mas_;
    }

    int getNumber() const { return number_; }

    const int *getStaticMas() const { return static_mas_; } // Так лучше не делать, наверное (удалить не могут)

    const int *getDynamicMas() const { return dynamic_mas_; } // // Так лучше не делать, ибо могут удалить dynamic_mas_

    void setNumber(int number) { number_ = number; }

    void setNumberInStaticMas(int number, int index) { static_mas_[index] = number; }

    void setNumberInDynamicMas(int number, int index) { dynamic_mas_[index] = number; }

    int operator++() {
        number_++;
        return number_;
    } // ++obj

    int operator++(int) {
        int a = number_;
        number_++;
        return a;
    } // obj++

    int operator[](int index) const {
        return static_mas_[index];
    } // obj[5]

    explicit operator bool() const {
        return number_ != 0;
    } // (bool)obj

    explicit operator int() const {
        return number_;
    } // (int)obj

    friend std::ostream &operator<<(std::ostream &stream, const Base &obj) {
        stream << obj.number_;
        return stream;
    } // std::cout << obj

    // friend std::istream &operator>>(std::istream &stream, Base &obj);
    // std::cin >> obj

    // friend Base operator+(const Base &obj1, const Base &obj2);
    // obj1 + obj2

    // Base &operator+=(const Base &str);
    // obj1 += obj2

    friend bool operator==(const Base &obj1, const Base &obj2) { // Не может быть константной, ибо это не метод
        return obj1.number_ == obj2.number_;
    } // obj1 == obj2
};

Base getNewBase(int number) {
    Base res(number);
    return res;
}

int main() {
    Base obj1; //First constructor
    Base obj2(1); //Second constructor
    Base obj3(obj1); // First constructor -> Copy constructor
    Base obj4(getNewBase(7)); // Second constructor
    Base &&obj5 = getNewBase(7); // Second constructor
    Base obj6(obj5); // First constructor -> Copy constructor
    obj1 = obj2; // Copy operator
    obj2 = getNewBase(7); // (Second constructor), Move operator
}

