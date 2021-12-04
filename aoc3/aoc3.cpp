#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <span>
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
    return std::pair{rv, ln.size()};
}

bool more_ones(uint16_t b, std::vector<uint16_t> const& v)
{
    return std::count_if(v.begin(), v.end(), [&](auto u){ return u & b ;}) > v.size() / 2;
}

auto count_ones(uint16_t b, std::vector<uint16_t> const& v)
{
    return std::count_if(v.begin(), v.end(), [&](auto u){ return u & b ;}) ;
}

unsigned pt1(auto const& v, size_t w)
{
    uint16_t r { 0 };
    uint16_t b { 1 };
    for( auto n = 0; n < w; ++n)
    {
        r |= more_ones(b, v) ? b : 0;
        b <<= 1;
    }
    uint16_t msk {1};
    msk <<= w;
    --msk;
    return r * (~r & msk);
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

unsigned pt2(auto const& v, size_t w)
{
    auto v0{v};
    auto v1{v};

    uint16_t b { 1 };
    b <<= (w - 1) ;
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
#if 0
unsigned pt22(auto v, auto w)
{
    uint16_t b { 1 };
    b <<= (w - 1) ;
    auto i = std::partition(v.begin(), v.end(), [b](auto vl){ return vl& b;});
    std::span<uint16_t> o2{v.data(), v.size()};
    std::span<uint16_t> co2{v.data(), v.size()};
    if(std::distance(i, v.end()) > std::distance(v.begin(), i)) // more or equal 1
    {
        o2 = std::span<uint16_t>{&*i, std::distance(i, v.end())};
        co2 = std::span<uint16_t>{v.data(), std::distance(v.begin(), i)};
    }
    else
    {
        co2 = std::span<uint16_t>{i, v.end()};
        o2 = std::span<uint16_t>{v.begin(), i};
    }
    auto bo2 { b >> 1} ;
    while(o2.size() > 1)
    {
        auto io2 = std::partition(o2.begin(), o2.end(), [bo2](auto vl){ return vl & bo2;});
        if(std::distance(io2, o2.end()) > std::distance(o2.begin(), io2)) // more or equal 1
            o2 = std::span<uint16_t>{io2, o2.end()};
        else
            o2 = std::span<uint16_t>{o2.begin(), io2};
        bo2 >>= 1;
    }
    auto bco2 { b >> 1} ;
    while(co2.size() > 1)
    {
        auto ico2 = std::partition(co2.begin(), co2.end(), [bco2](auto vl){ return vl & bco2;});
        if(std::distance(ico2, co2.end()) > std::distance(co2.begin(), ico2)) // more or equal 1
            co2 = std::span<uint16_t>{ico2, co2.end()};
        else
            co2 = std::span<uint16_t>{co2.begin(), ico2};
        bco2 >>= 1;
    }

    return o2.front() * co2.front();
}
#endif
int main()
{
    auto[v, w] = get_input();
    std::cout << "pt1 = " << pt1(v, w) << "\n";
    std::cout << "pt2 = " << pt2(v, w) << "\n";
//    std::cout << "pt22 = " << pt22(v, w) << "\n";
}