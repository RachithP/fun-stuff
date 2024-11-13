#include <stdint.h> 

#include <concepts>
#include <iostream>
#include <map>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>


template <typename TClass>
struct FuncInfo : public FuncInfo<decltype(&TClass::operator())> {};

template <typename TClass, typename TReturn, typename... TArgs>
struct FuncInfo<TReturn(TClass::*)(TArgs...)> : public FuncInfo<TReturn(*)(TArgs...)> {};

template <typename TClass, typename TReturn, typename... TArgs>
struct FuncInfo<TReturn(TClass::*)(TArgs...) const> : public FuncInfo<TReturn(*)(TArgs...)> {};

template <typename TReturn, typename... TArgs>
struct FuncInfo<TReturn(*)(TArgs...)> {};

template<typename TFunc, typename TReturn, typename... TArgs>
auto delineate(TFunc&& func, const FuncInfo<TReturn(*)(TArgs&...)>& fi)
{
    std::cout << "delineate call" << std::endl;
    return [func](TArgs... args) -> TReturn {
        return func(args...);   
    };
}

template <typename TFunc>
auto debunk(TFunc&& func)
{
    std::cout << "debunk call" << std::endl;
    return delineate(std::forward<TFunc>(func), FuncInfo<TFunc>());
}


template <typename TFunc>
auto raw_delineate(TFunc&& func)
{
    std::cout << "raw_delineate call" << std::endl;
    return [func]<typename... TArgs>(TArgs&&... args) -> auto {
        return func(std::forward<TArgs>(args)...);
    };
}


int main ()
{
    // int a = 1;
    // float b = 2;
    // auto f_const = raw_delineate(
    //     [] (const int& a, const float& b) -> float {
    //         std::cout << "executing f_const function" << std::endl;
    //         return a+b;
    //     });
    // auto c = f_const(1,2);
    // auto d = f_const(a,b);
    // std::cout << "checking if return type is same as expected: " << std::is_same<float, decltype(c)>::value << std::endl;

    // auto f = raw_delineate(
    //     [] (int a, float b) -> float {
    //         std::cout << "executing f function" << std::endl;  
    //         return a+b;
    //     });
    // auto g = f(1,2);
    // auto h = f(a,b);
    // std::cout << "checking if return type is same as expected: " << std::is_same<int, decltype(g)>::value << std::endl;
    // std::cout << "checking if return type is same as expected: " << std::is_same<float, decltype(g)>::value << std::endl;

    auto f_comp = raw_delineate(
        [] (const std::vector<float>& a, const std::map<std::string, std::vector<double>>& action) -> std::map<std::string, std::vector<uint8_t>> {
            std::cout << "executing f_comp function" << std::endl;
            return { {"A", std::vector<uint8_t>{1,2,3}} };
        });
    std::map<std::string, std::vector<double>> map_var = {{"a",std::vector<double>{1,2,3}}, {"b",std::vector<double>{4,5,6}}}; 
    auto i = f_comp(std::vector<float>{1,2,3}, map_var);
    // auto j = f_comp(std::vector<float>{1,2,3}, { {"a",std::vector<double>{1,2,3}}, {"b",std::vector<double>{4,5,6}} });

    std::cout << "checking if return type is same as expected: " << std::is_same<std::map<std::string, std::vector<uint8_t>>, decltype(i)>::value << std::endl;

    auto f_compl = raw_delineate(
        [] (const std::vector<std::string>& b, const std::string& name, std::string other_name) -> std::vector<uint8_t> {
            std::cout << "executing f_compl function" << std::endl;  
            return std::vector<uint8_t>{1,2,3};
        });
    auto k = f_compl(std::vector<std::string>{"x", "y"}, "abc", "xyz");
    std::cout << "checking if return type is same as expected: " << std::is_same<std::vector<uint8_t>, decltype(k)>::value << std::endl;

    return 0;
}
