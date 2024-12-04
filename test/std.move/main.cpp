#include <iostream>
#include <string>

int main()
{
    std::string str = "hello world";
    std::cout << "str: " << str << std::endl;
    std::string&& t = std::move(str);
    std::cout << "t: " << t << std::endl;
    std::cout << "str: " << str << std::endl;

    std::string&& s = std::move("hello world");
    std::cout << "s: " << s << std::endl;

    return 0;
}
