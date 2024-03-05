#include <cstring>
#include <iostream>
#include <string>

class A {
public:
    
    char* val_ = nullptr;

    A(const char& val)
    {
        val_ = new char[1];
        *val_ = val;
        std::cout << *val_ << ":Constuctor" << std::endl;
    }
    
    ~A()
    {
        if (val_) {
            std::cout << *val_ << ":Destuctor" << std::endl;
        } else {
            std::cout << "Empty:Destuctor" << std::endl;
        }
        delete[] val_;
        val_ = nullptr;
    }

    A(const A& other)
    {
        // deep copy
        val_ = new char[1];
        *val_ = *other.val_;
        std::cout << *val_ << ":Copy Constuctor" << std::endl;
    }

    A& operator=(const A& other)
    {
        if(&other == this) return *this;

        delete[] val_;
        val_ = new char[1];
        *val_ = *other.val_;
        std::cout << *val_ << ":Copy Assignment" << std::endl;
        return *this; 
    }

    A(A&& other): val_(other.val_)
    {
        other.val_ = nullptr;   
        std::cout << *val_ << ":Move Constuctor" << std::endl;
    }

    A& operator=(A&& other)
    {
        delete[] val_;
        val_ = other.val_;
        
        other.val_ = nullptr;

        std::cout << *val_ << ":Move Assignment" << std::endl;
        return *this;
    }
};

int main()
{
    // char* chars = new char[4];
    // std::strcpy(chars, "ABC");
    const char* chars = "ABCD";

    A a(chars[0]);
    A c = a;

    A b = A(chars[1]);
    A d = std::move(b);

    A e = A('X');

    return 0;
}
