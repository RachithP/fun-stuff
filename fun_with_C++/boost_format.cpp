#include <boost/format.hpp>
#include <iostream>
#include <format>
#include <string>

int main()
{
    void* ptr = new std::string("5");

    std::cout << "boost: " << (boost::format("0x%016x")%reinterpret_cast<uint64_t>(ptr)).str() << std::endl;
    std::cout << "std:   " << std::format("{:#018x}", reinterpret_cast<uint64_t>(ptr)) << std::endl;

    ptr = nullptr;
    return 0;
}
