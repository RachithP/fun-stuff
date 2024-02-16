// Figuring out basics of pointers, smart_pointers.

#include <iostream>
#include <memory>

template <typename T>
class raw_pointer {
public:
    raw_pointer(T* p) {
        p_ = p;
        std::cout << "p_ pointing value: " << *p_ << std::endl;
        std::cout << "p_ pointer value: " << p_ << std::endl;
        std::cout << "p_ pointer address: " << &p_ << std::endl;
    }
private:
    T* p_ = nullptr;
};



template <typename T>
class smart_ptr {
public:
    smart_ptr(std::shared_ptr<int> p) {
        p_ = p;
        std::cout << "p_ pointing value: " << *p_ << std::endl;
        std::cout << "p_ pointer value: " << p_ << std::endl;
        std::cout << "p_ pointer address: " << &p_ << std::endl;
        std::cout << "p_ count value: " << p_.use_count() << std::endl;
    }

    ~smart_ptr(){ std::cout << "~smart_ptr()..." << std::endl;}

private:
    std::shared_ptr<int> p_;
};


int main()
{
    int a = 2;

    int* d = &a;
    std::cout << "pointed value: " << *d << std::endl;
    std::cout << "pointed address: " << d << std::endl;
    std::cout << "pointer address: " << &d << std::endl;
    raw_pointer<int> o = raw_pointer<int>(d);
    std::cout << "\n\n" << std::endl;

    std::shared_ptr<int> e = std::make_shared<int>(6);
    std::cout << "pointed value: " << *e << std::endl;
    std::cout << "pointed address: " << e << std::endl;
    std::cout << "pointer address: " << &e << std::endl;
    std::cout << "count value: " << e.use_count() << std::endl;

    smart_ptr<int>* s = new smart_ptr<int>(e);
    
    std::cout << "count value: " << e.use_count() << std::endl;
    
    delete s;

    std::cout << "count value: " << e.use_count() << std::endl;
    return 0;
}