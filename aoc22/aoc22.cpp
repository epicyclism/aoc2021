#include <iostream>
#include <vector>
#include <string>
#include <bitset>

#include "ctre_inc.h"

struct inst
{
    bool on_;
    int xf_;
    int xt_;
    int yf_;
    int yt_;
    int zf_;
    int zt_;
};

auto get_input()
{
    std::vector<inst> vr;
    constexpr auto rx = ctll::fixed_string{ R"((on|off) x=(-?\d+)\.\.(-?\d+),y=(-?\d+)\.\.(-?\d+),z=(-?\d+)\.\.(-?\d+))" };
    std::string ln;
    while(std::getline(std::cin, ln))
    {
        auto[m, oo, xf, xt, yf, yt, zf, zt] = ctre::match<rx>(ln);
        vr.push_back({oo.to_view() == "on", sv_to_t<int>(xf.to_view()), sv_to_t<int>(xt.to_view()), sv_to_t<int>(yf.to_view()), sv_to_t<int>(yt.to_view()), sv_to_t<int>(zf.to_view()), sv_to_t<int>(zt.to_view())});
    }
    return vr;
}

template<int F, int T> auto in_range(inst const& i)
{
    return i.xf_ >= F && i.xf_ <= T && i.xt_ >= F && i.xt_ <= T &&
            i.yf_ >= F && i.yf_ <= T && i.yt_ >= F && i.yt_ <= T &&
            i.zf_ >= F && i.zf_ <= T && i.zt_ >= F && i.zt_ <= T ;
}

template<int F, int T> auto in_range (int x, int y, int z)
{
    return x >= F && x <= T && y >= F && y <= T && z >= F && z <= T;
}

template<int F, int T> auto to_off(int x, int y, int z)
{
    return (x - F) + ((y - F) * (T - F + 1)) + ((z - F) * (T - F + 1) * (T - F + 1));
}

void test()
{
    std::cout << 101 * 101 * 101 << "\n";
    std::cout << "0, 0, 0 = " << to_off<-50, 50>(0, 0, 0) << "\n";
    std::cout << "-50, -50, -50 = " << to_off<-50, 50>(-50, -50, -50) << "\n";
    std::cout << "50, 50, 50 = " << to_off<-50, 50>(50, 50, 50) << "\n";
}

int pt1(auto& in)
{
    std::bitset<101*101*101> bs;

    for(auto& i : in)
    {
        if( in_range<-50, 50>(i))
        {
            std::cout << "in " << i.xf_ << ", " << i.xt_ << "\n";
            for(auto x = i.xf_; x <= i.xt_; ++x)
                for(auto y = i.yf_; y <= i.yt_; ++y)
                    for(auto z = i.zf_; z <= i.zt_; ++z)
                        if( in_range<-50, 50>(x, y, z))
                            bs.set(to_off<-50, 50>(x, y, z), i.on_);
        }
    }
    return bs.count();
}

int main()
{
    auto in { get_input()};
    std::cout << "got " << in.size() << " instructions\n";
    test();
    std::cout << "pt1 = " << pt1(in) << "\n";
}