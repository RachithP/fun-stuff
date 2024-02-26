// Different ways to define use concepts.
// Disclaimer: Does not encapsulate all possible ways, just some. Add more ways as encountered/learnt.

#include <type_traits>
#include <iostream>
#include <memory>

// --------------------------Just different ways of concept syntax --------------------------
// ------------------------------------------------------------------------------------------
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

// -------------------------- using concepts to automatically resolve templates --------------------------
// -------------------------------------------------------------------------------------------------------
template <typename T>
concept check_int = std::same_as<T, int>;

template <typename T>
concept check_float = std::same_as<T, float>;

void func(check_int auto a){
    std::cout << "resolved to int" << std::endl;
}

void func(check_float auto a){
    std::cout << "resolved to float" << std::endl;
}

// -------------------------- using concepts to automatiicaly resolve templates --------------------------
// -------------------------- checking with std::derived_from  -------------------------------------------

class Base
{};

class A : public Base
{};

class B : public A
{};

template <typename T>
concept cbase = std::derived_from<T, Base>;

template <typename T>
// concept ca = std::derived_from<T, A>; // fails error: call of overloaded 'bar(A&)' is ambiguous
concept ca = cbase<T> && std::derived_from<T, A>;

template <typename T>
// concept cb = std::derived_from<T, B>; // fails error: call of overloaded 'bar(B&)' is ambiguous
// concept cb = cbase<T> && std::derived_from<T, B>; // fails error: call of overloaded 'bar(B&)' is ambiguous
concept cb = ca<T> && std::derived_from<T, B>;

void bar(cbase auto a){
    std::cout << "resolved to cbase" << std::endl;
}

void bar(ca auto a){
    std::cout << "resolved to ca" << std::endl;
}

void bar(cb auto a){
    std::cout << "resolved to cb" << std::endl;
}

int main() {

    // int x = 2;
    // float y = 1;
    // std::cout << square(x) << std::endl;
    // func(x); // resolves to the func that has check_int
    // func(y); // resolves to the func that has check_float

    Base base;
    A a;
    B b;

    bar(base);
    bar(a);
    bar(b);

    return 0;
}