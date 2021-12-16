#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

#if 0
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
    return std::inner_product(v.begin(), v.end() - 1, v.begin() + 1, 0, std::plus<>(), std::less<>());
}

int pt2(auto v)
{
    return std::inner_product(v.begin(), v.end() - 3, v.begin() + 3, 0, std::plus<>(), std::less<>());
}

int main()
{
    auto in = get_input();
    std::cout << "pt1 = " << pt1(in) << "\n";
    std::cout << "pt2 = " << pt2(in) << "\n";
}
#else
int main()
{
    std::vector<int> v;
    std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::back_inserter(v));
    std::cout << "pt1 " << std::transform_reduce(v.begin(), v.end() - 1, v.begin() + 1, 0, std::plus<>(), std::less<>()) << "\n";
    std::cout << "pt2 " << std::transform_reduce(v.begin(), v.end() - 3, v.begin() + 3, 0, std::plus<>(), std::less<>()) << "\n";
}
#endif