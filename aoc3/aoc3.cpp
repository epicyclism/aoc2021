#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <charconv>

auto get_input()
{
    std::vector<uint16_t> rv;
    std::string ln;
    while( std::getline(std::cin, ln))
    {
        uint16_t u{0};
        std::from_chars(ln.data(), ln.data() + ln.size(), u, 2);
        rv.push_back(u);
    }
    return rv;
}

bool more_ones(uint16_t b, std::vector<uint16_t> const& v)
{
    return std::count_if(v.begin(), v.end(), [&](auto u){ return u & b ;}) > v.size() / 2;
}

auto count_ones(uint16_t b, std::vector<uint16_t> const& v)
{
    return std::count_if(v.begin(), v.end(), [&](auto u){ return u & b ;}) ;
}

unsigned pt1(auto const& v)
{
    uint16_t r { 0 };
    uint16_t b { 1 };
    for( int n = 0; n < 12; ++n)
    {
        r |= more_ones(b, v) ? b : 0;
        b <<= 1;
    }
    return r * (~r & 0xfff);
}

void keep(uint16_t b, std::vector<uint16_t>& v)
{
    if ( v.size() > 1)
        std::erase_if(v, [&](auto u){ return !(u & b);});
}

void lose(uint16_t b, std::vector<uint16_t>& v)
{
    if( v.size() > 1)
        std::erase_if(v, [&](auto u){ return u & b;});
}

unsigned pt2(auto const& v)
{
    auto v0{v};
    auto v1{v};

    uint16_t b { 0x800 };
    for( int n = 0; n < 12; ++n)
    {
        auto nb = count_ones(b, v1);
        if(nb >= v1.size() - nb)
            keep(b, v1);
        else
            lose(b, v1);
        nb = count_ones(b, v0);
        if(nb >= v0.size() - nb)
            lose(b, v0);
        else
            keep(b, v0);
        b >>= 1;
    }
    return v0[0] * v1[0];
}

int main()
{
    auto v = get_input();
    std::cout << "pt1 = " << pt1(v) << "\n";
    std::cout << "pt2 = " << pt2(v) << "\n";
}