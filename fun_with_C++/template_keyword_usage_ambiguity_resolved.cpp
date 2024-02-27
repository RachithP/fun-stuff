//
// Conclusion: Use template keyword whenever a dependent template is used with angled braces (<>).
//

#include <concepts>
#include <iostream>

// class that mimics rpc::server for the purpose of testing out usage of `Dummy.foo(...)` vs `Dummy.template foo(...)` only
class Dummy
{
public:
    template <typename T>
    void foo(T t) {
        std::cout << "Dummy::foo" << std::endl;
    }
};

template <typename T>
concept CDot = requires(T t) {
    { t.foo( []()->void{} ) } -> std::same_as<void>;                  // works
    // { t.foo<>( []()->void{} ) } -> std::same_as<void>;             // clang doesn't like not using template keyword, but msvc is OK with it
    // { t.template foo( []()->void{} ) } -> std::same_as<void>;      // works
    // { t.template foo<>( []()->void{} ) } -> std::same_as<void>;    // works
};

void bar(CDot auto x) {
    x.foo( []()->void{} );                // works
    // x.template foo( []()->void{} );    // msvc doesn't like this template keyword here, but clang is OK with it
    // x.foo<>( []()->void{} );           // clang doesn't like not using template keyword here, but msvc is OK with it :O
    // x.template foo<>( []()->void{} );  // works
    std::cout << "bar" << std::endl;
}

int main()
{
    Dummy b;
    bar<Dummy>(b);
    bar(b);

    return 0;
}
