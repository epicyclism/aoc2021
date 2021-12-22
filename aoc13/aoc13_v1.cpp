#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "ctre_inc.h"

struct paper
{
    std::vector<char> contents_;
    int x_; // stride of contents
    int sx_;// size of folded 'paper'
    int sy_;
};

struct fold
{
    bool x_;
    int  v_;
};

void apply_fold(paper& p, fold const& f)
{
    if( f.x_)// fold left along x == f.v_
    {
        int s = f.v_ + 1;
        int d = f.v_ - 1;
        while (s < p.sx_)
        {
            for (int cnt = 0; cnt < p.sy_; ++cnt)
            {
                if (p.contents_[s + p.x_ * cnt] == '#')
                    p.contents_[d + p.x_ * cnt] = '#';
            }
            --d;
            ++s;
        }
        p.sx_ /= 2;
    }
    else // fold up along y == f.v_
    {
        int s = (f.v_ + 1) * p.x_;
        int d = (f.v_ - 1) * p.x_;
        int sn = f.v_ + 1;
        while (sn < p.sy_)
        {
            for (int cnt = 0; cnt < p.sx_; ++cnt)
            {
                if (p.contents_[s + cnt] == '#')
                    p.contents_[d + cnt] = '#';
            }
            d -= p.x_;
            s += p.x_;
            ++sn;
        }
        p.sy_ /= 2;
    }
}

int count_dots(paper const& p)
{
    int cnt{0};
    for( int y = 0; y < p.sy_; ++y)
        for( int x = 0; x < p.sx_; ++x)
            if( p.contents_[y * p.x_ + x] == '#')
                ++cnt;
    return cnt;
}

std::ostream& operator<< (std::ostream& ostr, paper const& p)
{
    for(int y = 0; y < p.sy_; ++y)
    {
        std::copy(p.contents_.begin() + y * p.x_, p.contents_.begin() + y * p.x_ + p.sx_, std::ostream_iterator<char>(ostr));
        ostr << "\n";
    }
    return ostr;
}

std::pair<paper, std::vector<fold>> get_input()
{
    constexpr auto rxpt = ctll::fixed_string{ R"((\d+),(\d+))" };
    constexpr auto rxfd = ctll::fixed_string{ R"(fold along (x|y)=(\d+))" };

    std::string ln;
    std::vector<std::pair<int, int>> tmp;
    while(std::getline(std::cin, ln))
    {
        if( ln.empty())
            break;
        if( auto[m, x, y] = ctre::match<rxpt>(ln); m)
            tmp.push_back({sv_to_t<int>(x.to_view()), sv_to_t<int>(y.to_view())});
    }
    auto mx = std::max_element(tmp.begin(), tmp.end(), [](auto a, auto b){return a.first < b.first ;})->first;
    auto my = std::max_element(tmp.begin(), tmp.end(), [](auto a, auto b){return a.second < b.second ;})->second;

    paper p;
    p.x_ = mx + 1;
    p.sx_ = p.x_;
    p.sy_ = my + 1;
    p.contents_.resize(p.sx_ * p.sy_, '.');
    for( auto& pt: tmp)
        p.contents_[pt.second * p.sx_ + pt.first] = '#';
    std::vector<fold> folds;
    while(std::getline(std::cin, ln))
    {
        if( auto[m, xy, v] = ctre::match<rxfd>(ln); m)
            folds.push_back({xy.to_view() == "x", sv_to_t<int>(v.to_view())});
    }
    return {p, folds} ;
}

int pt1(paper p, fold const& f)
{
    apply_fold(p, f);
    return count_dots(p);
}

void pt2(paper p, std::vector<fold> const& f)
{
    for (auto ff : f)
        apply_fold(p, ff);
    std::cout << p << "\n";
}

int main()
{
    auto [p, f] = get_input();
    std::cout << "pt1 = " << pt1(p, f.front()) << "\n";
    std::cout << "pt2 -\n";
    pt2(p, f);
}
