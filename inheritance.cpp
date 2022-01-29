#include <iostream>

class Parent {
protected:
    int *ptr_to_number_;
public:
    Parent() : ptr_to_number_{new int} { *ptr_to_number_ = 0; }

    explicit Parent(int number) : ptr_to_number_{new int} { *ptr_to_number_ = number; }

    Parent(const Parent &obj) : ptr_to_number_{new int} { *ptr_to_number_ = *obj.ptr_to_number_; }

    Parent &operator=(const Parent &obj) { // Не может быть виртуальным
        if (this == &obj) { return *this; }
        *ptr_to_number_ = *obj.ptr_to_number_;
        return *this;
    }

    virtual ~Parent() { delete ptr_to_number_; }

    void setNumber(int number) { *ptr_to_number_ = number; }

    int getNumber() const { return *ptr_to_number_; }

    virtual void sayHi() const { std::cout << "Hi! I am parent" << std::endl; }

    virtual int operator++() {
        (*ptr_to_number_)++;
        return *ptr_to_number_;
    }

    virtual int operator++(int) {
        int a = *ptr_to_number_;
        (*ptr_to_number_)++;
        return a;
    }

    friend std::ostream &operator<<(std::ostream &stream, const Parent &obj) {
        stream << *obj.ptr_to_number_;
        return stream;
    }
};

class Child : public Parent {
private:
    int *ptr_to_another_number_;
public:
    Child() : ptr_to_another_number_{new int} { *ptr_to_another_number_ = 0; }

    Child(int number, int another_number) : Parent(number),
                                            ptr_to_another_number_{new int} { *ptr_to_another_number_ = another_number; }

    Child(const Child &obj) : Parent(obj),
                              ptr_to_another_number_{new int} { *ptr_to_another_number_ = *obj.ptr_to_another_number_; }

    Child &operator=(const Child &obj) {
        if (this == &obj) { return *this; }
        *ptr_to_another_number_ = *obj.ptr_to_another_number_;
        return *this;
    }

    ~Child() override {
        delete ptr_to_another_number_;
    }

    void setAnotherNumber(int number) { *ptr_to_another_number_ = number; }

    int getAnotherNumber() const { return *ptr_to_another_number_; }

    void sayHi() const override { std::cout << "Hi! I am child" << std::endl; }

    int operator++() override {
        (*ptr_to_another_number_)++;
        (*ptr_to_number_)++;
        return *ptr_to_another_number_;
    }

    int operator++(int) override {
        int a = *ptr_to_another_number_;
        (*ptr_to_another_number_)++;
        (*ptr_to_number_)++;
        return a;
    }
};

int main() {
    Child obj(1, 2);
    Parent &link = obj;
    link++;
    link.sayHi();
}
