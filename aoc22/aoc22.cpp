#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <numeric>
#include <optional>
#include <compare>
#include <map>
#include "ctre_inc.h"

struct pt
{
    int x_;
    int y_;
};

struct region
{
    int xf_;
    int xt_;
    int yf_;
    int yt_;
    int zf_;
    int zt_;
    auto operator<=>(region const&)  const = default;
};

std::ostream& operator<<(std::ostream& o, region const& i)
{
    o << i.xf_ << ".." << i.xt_ << "," << i.yf_ << ".." << i.yt_ << "," << i.zf_ << ".." << i.zt_;
    return o;
}

auto get_input()
{
    std::vector<std::pair<bool, region>> vr;
    constexpr auto rx = ctll::fixed_string{ R"((on|off) x=(-?\d+)\.\.(-?\d+),y=(-?\d+)\.\.(-?\d+),z=(-?\d+)\.\.(-?\d+))" };
    std::string ln;
    while(std::getline(std::cin, ln))
    {
        auto[m, oo, xf, xt, yf, yt, zf, zt] = ctre::match<rx>(ln);
        vr.push_back({ oo.to_view() == "on", {sv_to_t<int>(xf.to_view()), sv_to_t<int>(xt.to_view()), sv_to_t<int>(yf.to_view()), sv_to_t<int>(yt.to_view()), sv_to_t<int>(zf.to_view()), sv_to_t<int>(zt.to_view())} });
    }
    return vr;
}

template<int F, int T> auto in_range(region const& i)
{
    return i.xf_ >= F && i.xf_ <= T && i.xt_ >= F && i.xt_ <= T &&
            i.yf_ >= F && i.yf_ <= T && i.yt_ >= F && i.yt_ <= T &&
            i.zf_ >= F && i.zf_ <= T && i.zt_ >= F && i.zt_ <= T ;
}

template<int F, int T> auto to_off(int x, int y, int z)
{
    return (x - F) + ((y - F) * (T - F + 1)) + ((z - F) * (T - F + 1) * (T - F + 1));
}

int pt1(auto const& in)
{
    std::bitset<101*101*101> bs;

    for(auto& i : in)
    {
        auto& r{ i.second };
        if( in_range<-50, 50>(r))
            for(auto x = r.xf_; x <= r.xt_; ++x)
                for(auto y = r.yf_; y <= r.yt_; ++y)
                    for(auto z = r.zf_; z <= r.zt_; ++z)
                            bs.set(to_off<-50, 50>(x, y, z), i.first);
    }
    return bs.count();
}

std::optional<region> intersect(region const& i1, region const& i2)
{
    region ic{  i1.xf_ < i2.xf_ ? i2.xf_ : i1.xf_,
                i1.xt_ < i2.xt_ ? i1.xt_ : i2.xt_,
                i1.yf_ < i2.yf_ ? i2.yf_ : i1.yf_,
                i1.yt_ < i2.yt_ ? i1.yt_ : i2.yt_,
                i1.zf_ < i2.zf_ ? i2.zf_ : i1.zf_,
                i1.zt_ < i2.zt_ ? i1.zt_ : i2.zt_};
    if ( ic.xt_ > ic.xf_ && ic.yt_ > ic.yf_ && ic.zt_ > ic.zf_)
        return ic;
    return std::nullopt;
}

int64_t sz(region const& i)
{
    return (i.xt_ - i.xf_ + 1) * (i.yt_ - i.yf_ + 1) * (i.zt_ - i.zf_ + 1);
}

int64_t pt2(auto const& in)
{
    struct cube
    {
        region r_;
        std::vector<cube> h_;
        void cut(region const& c)
        {
            for (auto& h : h_)
                h.cut(c);
            if (r_ != c)
            {
                auto ii = intersect(r_, c);
                if (ii)
                {
                    h_.push_back({ ii.value() });
                }
            }
        }
        int64_t cnt() const
        {
            return sz(r_) - std::accumulate(h_.begin(), h_.end(), 0LL, [](auto s, auto& c) { return s + c.cnt(); });
        }
        void print() const
        {
            std::cout << sz(r_) << "\n";
            std::cout << " -->\n";
            for (auto& c : h_)
                c.print();
            std::cout << "<--\n";
        }
    };
    std::vector<cube> vc;
    for (auto& i : in)
    {
        for (auto& c : vc)
            c.cut(i.second);
        if (i.first)
            vc.push_back({ i.second });
    }
    for (auto& c : vc)
    {
        std::cout << "----\n" << c.cnt() << "\n-----\n";
        c.print();
    }
    return std::accumulate(vc.begin(), vc.end(), 0LL, [](auto s, auto& c) { return s + c.cnt(); });
}

int main()
{
    auto in { get_input()};
    std::cout << "got " << in.size() << " instructions\n";
    std::cout << "pt1 = " << pt1(in) << "\n";
    std::cout << "pt2 = " << pt2(in) << "\n";
}