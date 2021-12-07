#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <array>
#include <limits>

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

int pt1(std::vector<int> const& v)
{
    const auto [min, max] = std::minmax_element(v.begin(), v.end());

    auto cost {std::numeric_limits<int>::max()};
    for(auto off = *min; off != *max; ++off)
    {
        auto this_cost = std::accumulate(v.begin(), v.end(), 0, [&](auto s, auto v){ return std::abs(v - off) + s;});
        if( this_cost < cost)
            cost = this_cost;
    }
    return cost;
}

int pt2(std::vector<int> const& v)
{
    const auto [min, max] = std::minmax_element(v.begin(), v.end());

    auto eu = [](int v) -> int { return v * (1 + v) / 2 ;};
    auto cost {std::numeric_limits<int>::max()};
    for(auto off = *min; off != *max; ++off)
    {
        auto this_cost = std::accumulate(v.begin(), v.end(), 0, [&](auto s, auto v){ return eu(std::abs(v - off)) + s;});
        if( this_cost < cost)
            cost = this_cost;
    }
    return cost;
}

int main()
{
    auto v = get_input();
    std::cout << "pt1 = " << pt1(v) << "\n";
    std::cout << "pt2 = " << pt2(v) << "\n";
}