#include <iostream>
//#include <vector>
//#include <iterator>
#include <string>
//#include <sstream>
#include <algorithm>
#include <numeric>
#include <array>

#if 0
std::vector<int> get_input(/)
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
#else
auto get_input()
{
    std::array<int64_t, 9> ra{};
    std::string ln;
    std::getline(std::cin, ln);
//    std::for_each(ln.begin(), ln.end(), [&ra](auto c) { if (std::isdigit(c)) ++ra[c - '0']; });
    for(auto c : ln)
         if (std::isdigit(c))
             ++ra[c - '0'];
    return ra;
}

auto simulate_fish(auto cnts, int ng)
{
    for (int g = 0; g < ng; ++g)
    {
        std::rotate(cnts.begin(), cnts.begin() + 1, cnts.end());
        cnts[6] += cnts[8];
    }
    return std::accumulate(cnts.begin(), cnts.end(), 0ll);
}

int main()
{
    auto fish_cnts = get_input();
    std::cout << "example after 80 days  " << simulate_fish(std::array{ 0LL, 1LL, 1LL, 2LL, 1LL, 0LL, 0LL, 0LL, 0LL}, 80) << "\n";
    std::cout << "pt1 after 80 days      " << simulate_fish(fish_cnts, 80) << "\n";
    std::cout << "example after 256 days " << simulate_fish(std::array{ 0LL, 1LL, 1LL, 2LL, 1LL, 0LL, 0LL, 0LL, 0LL }, 256) << "\n";
    std::cout << "pt2 after 256 days     " << simulate_fish(fish_cnts, 256) << "\n";
}
#endif