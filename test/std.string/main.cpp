#include <iostream>
#include <string>

int main()
{
    std::string s = "Hello World";

    printf("%s\n", s.c_str());
    printf("%d\n", static_cast<int>(s.length()));

    return 0;
}
