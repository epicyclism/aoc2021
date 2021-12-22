#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <charconv>
#include <algorithm>

#include "ctre_inc.h"

struct pt
{
    int x_;
    int y_;
};
struct line
{
    pt from_;
    pt to_;
};

auto get_input()
{
    constexpr auto rx_line = ctll::fixed_string{ R"((\d+),(\d+) -> (\d+),(\d+))" };
    std::string ln;
    std::vector<line> out;
    while(std::getline(std::cin, ln))
    {
        if(auto[m, x1, y1, x2, y2] = ctre::match<rx_line>(ln); m)
            out.push_back({sv_to_t<int>(x1.to_view()), sv_to_t<int>(y1.to_view()), sv_to_t<int>(x2.to_view()), sv_to_t<int>(y2.to_view())});
    }
    return out;
}

constexpr size_t stride { 1024 };
void draw_vertical(auto& a, auto l)
{
    auto top { l.from_};
    auto bottom{ l.to_};
    if( top.y_ > bottom.y_) 
        std::swap(top, bottom);
    while(top.y_ <= bottom.y_)
    {
        ++a[top.y_ * stride + top.x_];
        ++top.y_;
    }
}

void draw_horizontal(auto& a, auto l)
{
    auto left { l.from_};
    auto right{ l.to_};
    if( left.x_ > right.x_) 
        std::swap(left, right);
    while(left.x_ <= right.x_)
    {
        ++a[left.y_ * stride + left.x_];
        ++left.x_;
    }
}

void draw_diagonal(auto& a, auto l)
{
    auto left { l.from_};
    auto right{ l.to_};
    if( left.x_ > right.x_) 
        std::swap(left, right);
    auto inc = left.y_ > right.y_ ? -1 : 1;
    while( left.x_ <= right.x_)
    {
       ++a[left.y_ * stride + left.x_];
       left.y_ += inc;
       ++left.x_;
    }
}

auto pt1(auto const& in)
{
    std::vector<int> arena ( stride * stride);
    for(auto& l : in)
        if( l.from_.x_ == l.to_.x_)
            draw_vertical(arena, l);
        else
        if(l.from_.y_ == l.to_.y_)
            draw_horizontal(arena, l);

    return std::count_if(arena.begin(), arena.end(), [](auto v){ return v > 1;});
}

auto pt2(auto const& in)
{
    std::vector<int> arena ( stride * stride);
    for(auto& l : in)
        if( l.from_.x_ == l.to_.x_)
            draw_vertical(arena, l);
        else
        if(l.from_.y_ == l.to_.y_)
            draw_horizontal(arena, l);
        else
            draw_diagonal(arena, l);

    return std::count_if(arena.begin(), arena.end(), [](auto v){ return v > 1;});
}

int main()
{
    auto in = get_input();

    std::cout << "pt1 = " << pt1(in) << "\n";
    std::cout << "pt2 = " << pt2(in) << "\n";
}