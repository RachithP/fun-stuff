
//
// compile on linux
// clang++ -std=c++20 -stdlib=libc++ -I/home/rachithp/code/github/spear/third_party/boost boost_format.cpp -Wl, -rpath /home/rachithp/softwares/llvm/llvm-project/build/lib/x86_64-unknown-linux-gnu
//

#include <boost/format.hpp>
#include <format>
#include <iostream>

int main()
{
    void* ptr = new double(5);

    std::cout << "boost: " << (boost::format("0x%016x")%reinterpret_cast<uint64_t>(ptr)).str() << std::endl;
    std::cout << "std:   " << std::format("{:#018x}", reinterpret_cast<uint64_t>(ptr)) << std::endl;

    ptr = nullptr;
    return 0;
}
