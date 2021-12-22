#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "ctre_inc.h"

using fold = std::pair<bool, int>;
using dot  = std::pair<int, int>; // y, x!
using folds = std::vector<fold>;
using paper = std::vector<dot>;

std::pair<paper, folds> get_input()
{
    constexpr auto rxpt = ctll::fixed_string{ R"((\d+),(\d+))" };
    constexpr auto rxfd = ctll::fixed_string{ R"(fold along (x|y)=(\d+))" };

    std::string ln;
    paper dots;
    while(std::getline(std::cin, ln))
    {
        if( ln.empty())
            break;
        if( auto[m, x, y] = ctre::match<rxpt>(ln); m)
            dots.push_back({sv_to_t<int>(y.to_view()), sv_to_t<int>(x.to_view())});
    }

    folds f;
    while(std::getline(std::cin, ln))
    {
        if( auto[m, xy, v] = ctre::match<rxfd>(ln); m)
            f.push_back({xy.to_view() == "x", sv_to_t<int>(v.to_view())});
    }
    return {dots, f} ;
}

void apply_fold(paper& p, fold f)
{
    if( f.first) // along x ==
        std::transform(p.begin(), p.end(), p.begin(), [x = f.second](auto pt){if ( pt.second > x) return dot{pt.first, 2 * x - pt.second}; else return pt;});
    else // along y ==
        std::transform(p.begin(), p.end(), p.begin(), [y = f.second](auto pt){if ( pt.first > y) return dot{ 2 * y - pt.first, pt.second}; else return pt;});
}

void print(paper const& p)
{
    int ch {0};
    int y  {0};
    for(auto& pt : p)
    {
        if( pt.first > y)
        {
            std::cout << "\n";
            ch = 0;
            ++y;
        }
        while(ch < pt.second)
        {
            std::cout << " ";
            ++ch;
        }
        ++ch;
        std::cout << "#";
    }
    std::cout << "\n";
}

int count_dots(paper& p)
{
    std::sort(p.begin(), p.end());
    p.erase( std::unique(p.begin(), p.end()), p.end());
    return p.size();
}

int pt1(paper p, fold f)
{
    apply_fold(p, f);
    return count_dots(p);
}

void pt2(paper p, folds const& f)
{
    for (auto ff : f)
        apply_fold(p, ff);
    std::sort(p.begin(), p.end());
    p.erase( std::unique(p.begin(), p.end()), p.end());
    print(p);
}

int main()
{
    auto [p, f] = get_input();
    std::cout << "pt1 = " << pt1(p, f.front()) << "\n";
    std::cout << "pt2 -\n";
    pt2(p, f);
}
