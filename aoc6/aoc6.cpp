#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <array>

std::vector<int> get_input()
{
    std::string ln;
    std::getline(std::cin, ln);
    std::transform(ln.begin(), ln.end(), ln.begin(), [](auto c){ return c == ',' ? ' ' : c;});
    std::stringstream istr (ln);
    std::vector<int> v;
    std::copy(std::istream_iterator<int>(istr), std::istream_iterator<int>(), std::back_inserter(v));
    return v;
}

int64_t simulate_fish(std::vector<int> v, int nd)
{
    std::array<int64_t, 9> cnts {0};
    for (auto i : v)
        ++cnts[i];
    for (auto n : cnts)
        std::cout << n << ", ";
    std::cout << "\n";
    for (int g = 0; g < nd; ++g)
    {
        std::rotate(cnts.begin(), cnts.begin() + 1, cnts.end());
        cnts[6] += cnts[8];
    }
    return std::accumulate(cnts.begin(), cnts.end(), 0ll);
}

int main()
{
    auto v = get_input();
    std::cout << "example after 80 days  " << simulate_fish(std::vector<int>{ 3, 4, 3, 1, 2 }, 80) << "\n";
    std::cout << "pt1 after 80 days      " << simulate_fish(v, 80) << "\n";
    std::cout << "example after 256 days " << simulate_fish(std::vector<int>{ 3, 4, 3, 1, 2 }, 256) << "\n";
    std::cout << "pt2 after 256 days     " << simulate_fish(v, 256) << "\n";
}