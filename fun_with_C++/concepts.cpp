// Different ways to define use concepts.
// Disclaimer: Does not encapsulate all possible ways, just some. Add more ways as encountered/learnt.

#include <type_traits>
#include <iostream>
#include <memory>

template <typename T>
concept check = requires (T v)
{
    // {std::is_integral_v<T>};
    {std::is_floating_point_v<T>};
};

// —------ Different ways to use concepts —-----

// template <typename T>
// float square(T num) requires check<T> {
//     return num * num;
// }

// template <typename T> requires check<T>
// float square(T num) {
//     return num*num;
// }

// float square(check auto num) {
//     return num * num;
// }

template <check T>
float square(T num) {
    return num * num;
}

void hello(int x, int* p) {
    std::cout << "value: " << x << std::endl;
    std::cout << "address: " << &x << std::endl;

    std::cout << "pointing value: " << *p << std::endl;
    std::cout << "pointer value: " << p << std::endl;
    std::cout << "pointer address: " << &p << std::endl;
}

template <typename T>
class engine {

public:
    engine(T& p) {
        p_ = p;
        std::cout << "pointing value: " << *p_ << std::endl;
        std::cout << "pointer value: " << p_ << std::endl;
        std::cout << "pointer address: " << &p_ << std::endl;     
    }
private:
    T& p_ = nullptr;
};

// void bye(T& p) {
//     std::cout << "pointing value: " << *p << std::endl;
//     std::cout << "pointer value: " << p << std::endl;
//     std::cout << "pointer address: " << &p << std::endl;
// }

int main() {

    int a = 2;
    std::cout << square(a) << std::endl;

    // int b = 4;
    // std::cout << "value: " << b << std::endl;
    // std::cout << "address: " << &b << std::endl;
    // hello(b, &b);

    std::unique_ptr<int> c = std::make_unique<int>(8);
    std::cout << "value: " << *c << std::endl;
    std::cout << "address: " << c << std::endl;
    std::cout << "pointer address: " << &c << std::endl;
    // bye(c);

    engine<int> o = engine<int>(c);

    return 0;
}