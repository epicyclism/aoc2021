#include <iostream>
#include <string>
#include <vector>
#include <numeric>

auto get_input()
{
    std::vector<int> rv;
    std::string ln;
    while(std::getline(std::cin, ln))
       rv.push_back(std::stoi(ln));
    return rv;
}

int pt1(auto v)
{
    return std::inner_product(v.begin(), v.end() - 1, v.begin() + 1, 0, std::plus<>(), [](auto l, auto r){ return r > l;});
}

int pt2(auto v)
{
    return std::inner_product(v.begin(), v.end() - 3, v.begin() + 3, 0, std::plus<>(), [](auto l, auto r){ return r > l;});
}

int main()
{
    auto in = get_input();
    std::cout << "pt1 = " << pt1(in) << "\n";
    std::cout << "pt2 = " << pt2(in) << "\n";
}