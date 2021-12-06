#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <charconv>
#include <numeric>

#include "ctre.hpp"

struct pd
{
    int a_;
    int h_;
    int d_;
};

pd operator+(pd const& l, pd const& r)
{
    return {0, l.h_ + r.h_, l.d_ + r.d_};
}

pd operator*(pd const& l, pd const& r)
{
    return {l.a_ + r.d_, l.h_ + r.h_, l.d_ + ( l.a_ * r.h_)};
}

template<typename T> T sv_to_t ( std::string_view sv)
{
	T t { 0 };
	std::from_chars(sv.data(), sv.data() + sv.size(), t);
	return t;
}

auto get_input()
{
    constexpr auto rx = ctll::fixed_string{ R"((down|forward|up) (\d+))" };
    std::string ln;
    std::vector<pd> v;
    while(std::getline(std::cin, ln))
    {
	    if(auto[m, d, p] =  ctre::match<rx>(ln); m)
		{
            auto pi = sv_to_t<int>(p.to_view());
            switch(d.to_view()[0])
            {
                case 'd':
                    v.emplace_back(pd{0, 0, pi});
                    break;
                case 'f':
                    v.emplace_back(pd{0, pi, 0});
                    break;
                case 'u':
                    v.emplace_back(pd{0, 0, -pi});
                    break;
                default: // CANNOT HAPPEN DUE REGEX
                    break;
            }
        }
        else
            std::cout << "Input tilt at : " << ln << "\n";
    }
    return v;
}

int pt1(auto const& v)
{
    auto r = std::accumulate(v.begin(), v.end(), pd{});
    return r.h_ * r.d_;;
}

int pt2(auto const& v)
{
    auto r = std::accumulate(v.begin(), v.end(), pd{}, std::multiplies<>());
    return r.h_ * r.d_;;
}

int main()
{
    auto v = get_input();
    std::cout << "pt1 = " << pt1(v) << "\n";
    std::cout << "pt2 = " << pt2(v) << "\n";
}