#include <iostream>
#include <iterator>
#include <bitset>
#include <string>
#include <map>
#include <algorithm>

using image_t = std::map<std::pair<int, int>, bool>;
using key_t = std::bitset<512>;

bool get(image_t const& i, std::pair<int, int> p, bool inf)
{
    if (i.contains(p))
        return (*i.find(p)).second;
    return inf;
}

// assume off is a valid place to walk right around...
uint16_t from(image_t const& i, std::pair<int, int> p, bool inf)
{
    uint16_t u { 0};
    u |= get(i, { p.first - 1, p.second - 1 }, inf) ? 1 : 0;
    u<<=1;
    u |= get(i, { p.first, p.second - 1 }, inf) ? 1 : 0;
    u<<=1;
    u |= get(i, { p.first + 1, p.second - 1 }, inf) ? 1 : 0;
    u<<=1;
    u |= get(i, { p.first - 1, p.second}, inf) ? 1 : 0;
    u<<=1;
    u |= get(i, { p.first, p.second}, inf) ? 1 : 0;
    u<<=1;
    u |= get(i, { p.first + 1, p.second }, inf) ? 1 : 0;
    u<<=1;
    u |= get(i, { p.first - 1, p.second + 1 }, inf) ? 1 : 0;
    u<<=1;
    u |= get(i, { p.first,  p.second + 1 }, inf) ? 1 : 0;
    u<<=1;
    u |= get(i, { p.first + 1, p.second + 1 }, inf) ? 1 : 0;
    return u;
}

std::ostream& operator<<(std::ostream& o, image_t const& i)
{
    std::pair<int, int> mn{ 0, 0 };
    for (auto& ir : i)
        if (ir.first < mn)
            mn = ir.first;
    auto p{ mn };
    while (i.contains(p))
    {
        while (i.contains(p))
        {
            o << ((*i.find(p)).second ? "#" : ".");
            ++p.first;
        }
        p.first = mn.first;
        o << "\n";
        ++p.second;
    }
    return o;
}

void orbit(image_t& i, const bool inf, const int f, const int t)
{
    std::pair<int, int> p{ f, f };
    // across the top
    while (p.first <= t)
    {
        i.insert(std::make_pair(p, inf));
        ++p.first;
    }
    // across the bottom
    p.second = t;
    p.first = f;
    while (p.first <= t )
    {
        i.insert(std::make_pair(p, inf));
        ++p.first;
    }
    // down
    p.first = f;
    p.second = f;
    while( p.second != t + 1)
    {
        i.insert(std::make_pair(p, inf));
        ++p.second;
    }
    p.first = t;
    p.second = f;
    while( p.second <= t)
    {
        i.insert(std::make_pair(p, inf));
        ++p.second;
    }
}

image_t step(image_t i1, key_t& key, bool inf, int f, int t)
{
    orbit(i1, inf, f, t);
    image_t i2;
    for (auto& p : i1)
        i2.insert(std::make_pair(p.first, key[from(i1, p.first, inf)]));
    return i2;
}

struct input
{
    image_t i_;
    key_t   k_;
    size_t  sz_;
};

input get_input()
{
    key_t bs;
    image_t im;
    std::string ln;
    std::getline(std::cin, ln);
    std::reverse(ln.begin(), ln.end());
    bs = std::bitset<512>(ln, 0, ln.size(), '.', '#');
    std::getline(std::cin, ln);

    std::pair<int, int> pt{ 0, 0 };
    while (std::getline(std::cin, ln))
    {
        for (auto c : ln)
        {
            im.insert(std::make_pair(pt, c == '#'));
            ++pt.first;
        }
        pt.first = 0;
        ++pt.second;
    }
    return {im, bs, ln.size()};
}

auto pt1(auto& in)
{
//    std::cout << "\n" << in.i_ << "\n";
    auto i2 = step(in.i_, in.k_, false, -1, in.sz_);
//    std::cout << i2 << "\n";
    i2 = step(i2, in.k_, in.k_[0], -2, in.sz_ + 1);
//    std::cout << i2 << "\n";
    return std::count_if(i2.begin(), i2.end(), [](auto& r) { return r.second; });
}

auto pt2(auto& in)
{
    auto inf{ false };
    auto f{ -1 };
    auto t{ in.sz_ };
    auto i2 = step(in.i_, in.k_, inf, f, t);
    for (int n = 1; n < 50; ++n)
    {
        if (in.k_[0])
            inf = !inf;
        --f;
        ++t;
        i2 = step(i2, in.k_, inf, f, t);
    }
    return std::count_if(i2.begin(), i2.end(), [](auto& r) { return r.second; });
}

int main()
{
    auto in { get_input()};
    std::cout << "pt1 = " << pt1(in) << "\n";
    std::cout << "pt2 = " << pt2(in) << "\n";
}

// 5591 too high