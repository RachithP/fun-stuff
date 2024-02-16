// Figuring out why/what std_forward is needed/does.

// References
// [1] https://stackoverflow.com/questions/3582001/what-are-the-main-purposes-of-stdforward-and-which-problems-does-it-solve
// [2] https://bajamircea.github.io/coding/cpp/2016/04/07/move-forward.html
// [3] http://thbecker.net/articles/rvalue_references/section_08.html

#include <iostream>
#include <utility>

// we need to have both E&&, and E& functions to receive lvalues and rvalues, but using templated function eliminates
// this requirement as the compiler auto-deduces the type.

// calling E(a,b,c) throws error.
// void E(int&& a, int&& b, int&& c) but not (1,2,3)
// {
//     std::cout << "E&&: address of i is " << &a << std::endl;
// }

// calling E(1,2,3) throws error, but not E(a,b,c).
// void E(int& a, int& b, int& c)
// {
//     std::cout << "E&: address of i is " << &a << std::endl;
// }

// the reason we use A&&, instead of A or A&, is because of special template argument deduction rule as explained in (3)
template <typename A, typename B, typename C>
void E(A&& a, B&& b, C&& c)
{
    std::cout << "E&&: address of i is " << &a << std::endl;
}

template <typename A, typename B, typename C>
void f(A&& a, B&& b, C&& c)
{
    std::cout << "f: address of i is " << &a << std::endl;
    E(std::forward<A>(a), std::forward<B>(b), std::forward<C>(c));
}

// This is one example explained in [1] as to why using const A& fails.
// This fails to comply with having E(int&, int&, int&); and calling f(i/4,j/5,k/6) call)
// because, a,b,c will be const and passing const variables to non-const arguments will throw an error.
// template <typename A, typename B, typename C>
// void f(const A& a, const B& b, const C& c)
// {
//     std::cout << "address of a is " << &a << std::endl;
//     E(a, b, c);
// }


int main()
{
    int i = 1, j = 2, k = 3;
    std::cout << "main: address of i is " << &i << std::endl;
    f(i, j, k);

    f(4,5,6);

    return 0;
}