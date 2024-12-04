#include <iostream>
#include <list>

int main()
{
    std::list<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    std::cout << "a" << std::endl;
    for (const int& item : a)
    {
        std::cout << item << std::endl;
    }
    std::list<int> b(a);
    a.clear();
    std::cout << "a" << std::endl;
    for (const int& item : a)
    {
        std::cout << item << std::endl;
    }
    std::cout << "b" << std::endl;
    for (const int& item : b)
    {
        std::cout << item << std::endl;
    }

    return 0;
}
