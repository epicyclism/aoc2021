#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <array>
#include <string>

constexpr int wd = 10;
using arena_t = std::array<int, wd * wd>;

arena_t get_input()
{
    arena_t a;
    std::string ln;
    auto i = a.begin();
    while(std::getline(std::cin, ln))
    {
        std::transform(ln.begin(), ln.end(), i, [](auto c){ return c - '0';});
        i += wd;
    }
    return a;
}

std::ostream& operator<< (std::ostream& ostr, arena_t const& a)
{
    auto i = a.begin();
    while(i != a.end())
    {
        std::copy(i, i + 10, std::ostream_iterator<int>(ostr, ""));
        ostr << "\n";
        i += 10;
    }
    return ostr;
}

auto can_see_set (arena_t const& a, auto i)
{
//                                       ul       u        ur          l      r       bl         b        br
    std::array<decltype(i), 8> css { i - wd - 1, i - wd, i - wd + 1, i - 1, i + 1, i + wd - 1, i + wd, i + wd + 1};
    if( i % wd == 0)
    {
        css[0] = -1;
        css[3] = -1;
        css[5] = -1;
    }
    if(i % wd == wd - 1)
    {
        css[2] = -1;
        css[4] = -1;
        css[7] = -1;
    }
    if( i < wd)
    {
        css[0] = -1;
        css[1] = -1;
        css[2] = -1;
    }
    if(i >= a.size() - wd)
    {
        css[5] = -1;
        css[6] = -1;
        css[7] = -1;
    }
    return css;
}

int flash(auto& a)
{
    int f { 0};
    for(int i = 0; i < a.size(); ++i)
    {
        if( a[i] > 9)
        {
            ++f;
            auto css = can_see_set(a, i);
            for(auto is : css)
            {
                if( is != -1 && a[is] != 0)
                    ++a[is];
            }
            a[i] = 0;
        }
    }
    return f;
}

int step(auto& a)
{   
    int fl { 0};
    int f { 0};
    std::transform(a.begin(), a.end(), a.begin(), [](auto c){ return c + 1;});
    do
    {
        f = flash(a);
        fl += f;
    } while (f > 0);
    
    return fl;
}

void test(auto a)
{
    std::cout << "Before any steps:\n";
    std::cout << a << "\n";

    for(int n = 1; n < 11; ++n)
    {
        step(a);
        std::cout << "After atep " << n << ":\n";
        std::cout << a << "\n";
    }
}

int pt1(auto a)
{
    int fl { 0 };
    for( int n = 0; n < 100; ++n)
        fl += step(a);
    return fl;
}

int pt2(auto a)
{
    int cnt { 0 };
    while(1)
    {
        ++cnt;
        if( step(a) == 100)
            return cnt;
    }
}

int main()
{
    auto a { get_input()};
    std::cout << "pt1 = " << pt1(a) << "\n";
    std::cout << "pt2 = " << pt2(a) << "\n";
}