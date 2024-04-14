#include <iostream>
#include <list>
#include <algorithm>

int main()
{
    std::list<int> ml = { 1, 2, 3, 4, 5, 6 };
    std::cout << "before: " << std::endl;
    std::cout << "\tlist size: " << ml.size() << std::endl << "\t";
    for (int a : ml)
    {
        std::cout << a << "\t";
    }
    std::cout << std::endl;

    std::list<int>::iterator it = std::remove_if(ml.begin(), ml.end(), [](const int& a) -> bool { return a == 7; });
    std::cout << "it: " << *it << std::endl;

    std::cout << "after remove_if: " << std::endl;
    std::cout << "\tlist size: " << ml.size() << std::endl << "\t";
    for (int a : ml)
    {
        std::cout << a << "\t";
    }
    std::cout << std::endl;

    ml.erase(it, ml.end());

    std::cout << "after pop_back: " << std::endl;
    std::cout << "\tlist size: " << ml.size() << std::endl << "\t";
    for (int a : ml)
    {
        std::cout << a << "\t";
    }
    std::cout << std::endl;
}