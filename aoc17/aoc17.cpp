#include <iostream>
#include <string>
#include <string_view>
#include <optional>

#include "ctre.hpp"

template<typename T> T sv_to_t ( std::string_view sv)
{
	T t { 0 };
	std::from_chars(sv.data(), sv.data() + sv.size(), t);
	return t;
}

struct tgt_area
{
    int x1_;
    int y1_;
    int x2_;
    int y2_;
};

auto get_input() -> tgt_area
{
    constexpr auto rx = ctll::fixed_string{ R"(target area: x=(-?\d+)\.\.(-?\d+), y=(-?\d+)\.\.(-?\d+))" };
    std::string ln;
    std::getline(std::cin, ln);
    if( auto[m, x1, x2, y1, y2] = ctre::match<rx>(ln); m)
        return { sv_to_t<int>(x1.to_view()), sv_to_t<int>(y1.to_view()), sv_to_t<int>(x2.to_view()), sv_to_t<int>(y2.to_view())};
    else
        std::cout << "parse error : " << ln << "\n";
    return {0, 0, 0, };
}

struct probe
{
    int xv_;
    int yv_;
    int x_;
    int y_;
    void step()
    {
        x_ += xv_;
        y_ += yv_;
        if( xv_ > 0)
            --xv_;
        else
        if( xv_ < 0)
            ++xv_;
        --yv_;
    }
};

std::pair<int, int> x_range(tgt_area& tgt)
{
    int xf {0};
    int xt{ tgt.x2_ + 1};
    return {xf, xt};
}

std::optional<int> fly(int xi, int yi, tgt_area tgt)
{
    if(tgt.y1_ < tgt.y2_)
        std::swap(tgt.y1_, tgt.y2_);
    probe p{ xi, yi, 0, 0 };
    int my{ yi };
    bool h{ false };
    while (1)
    {
        p.step();
        if (p.x_ >= tgt.x1_ && p.x_ <= tgt.x2_ && p.y_ <= tgt.y1_ && p.y_ >= tgt.y2_)
            return { my };
        if (p.y_ > my)
            my = p.y_;
        if (p.y_ < tgt.y2_)
            break;
    }
    return std::nullopt;
}

int pt1(tgt_area tgt)
{
    if(tgt.y1_ < tgt.y2_)
        std::swap(tgt.y1_, tgt.y2_);
    auto xr { x_range(tgt)};

    int ym {0};
    for( int xi = xr.first; xi < xr.second; ++xi)
    {
        int yi {0};
        while(yi < 1000)
        {
            auto yml = fly(xi, yi, tgt);
            if (yml && yml.value() > ym)
                ym = yml.value();
            ++yi;
        }
    }
    return ym;
}

int pt2(tgt_area tgt)
{
    if (tgt.y1_ < tgt.y2_)
        std::swap(tgt.y1_, tgt.y2_);
    auto xr{ x_range(tgt) };

    int cnt{ 0 };
    for (int xi = xr.first; xi < xr.second; ++xi)
    {
        int yi{ -1000 };
        while (yi < 1000)
        {
            auto yml = fly(xi, yi, tgt);
            if (yml)
                ++cnt;
            ++yi;
        }
    }
    return cnt;
}

int main()
{
    auto tgt {get_input()};
    std::cout << "pt1 = " << pt1(tgt) << "\n";
    std::cout << "pt2 = " << pt2(tgt) << "\n";
}
