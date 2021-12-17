#include <iostream>
#include <string>
#include <string_view>

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
    int xf { 0};
    // find xf
    while(1)
    {
        probe p { xf, 0, 0, 0};
        while(p.xv_ != 0)
        {
            p.step();
            if( p.x_ >= tgt.x1_)
                goto next;
        }
        ++xf;
    }
next:
    // then xt
    int xt {xf};
    while(1)
    {
        probe p { xt, 0, 0, 0};
        bool h {false};
        while(p.xv_ != 0)
        {
            p.step();
            if( p.x_ >= tgt.x1_ && p.x_ < tgt.x2_)
                h = true;
        }
        ++xt;
        if(!h)
            break;
    }
    return {xf, xt};
}

int pt1(tgt_area tgt)
{
    if(tgt.y1_ < tgt.y2_)
        std::swap(tgt.y1_, tgt.y2_);
    std::cout << tgt.x1_ << ", " << tgt.y1_ << " - " << tgt.x2_ << ", " << tgt.y2_ << "\n";
    auto xr { x_range(tgt)};
    std::cout << "xrange " << xr.first << " to " << xr.second << "\n";

    int ym {0};
    for( int xi = xr.first; xi < xr.second; ++xi)
    {
        int yi {9};
        while(yi < 10)
        {
            int yml{0};
            probe p{ xi, yi, 0, 0};
            while(p.xv_ != 0)
            {
                p.step();
                std::cout << p.x_ << " - " << p.y_ << "\n";
                if( p.y_ > yml)
                    yml = p.y_;
                if( p.x_ >= tgt.x1_ && p.x_ <= tgt.x2_ && p.y_ <= tgt.y1_ && p.y_ >= tgt.y2_)
                {
                    std::cout << "hit\n";
                    if( yml > ym)
                        ym = yml;
                    break;
                }
            }
            std::cout << yi << ". " << yml << "\n";
            ++yi;
        }
    }
    return ym;
}


int main()
{
    auto tgt {get_input()};
    std::cout << "tgt " << tgt.x1_ << ", " << tgt.y1_ << " to " << tgt.x2_ << ", " << tgt.y2_ << "\n";
    std::cout << "pt1 = " << pt1(tgt) << "\n";
}