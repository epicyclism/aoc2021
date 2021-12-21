#include <iostream>
#include <string>
#include <algorithm>

#include "ctre.hpp"

template<typename T> T sv_to_t ( std::string_view sv)
{
	T t { 0 };
	std::from_chars(sv.data(), sv.data() + sv.size(), t);
	return t;
}

auto get_input() -> std::pair<int, int> 
{
    constexpr auto rx = ctll::fixed_string{ R"(Player (\d) starting position: (\d+))" };
    std::string ln;
    int a;
    int b;
    while( std::getline(std::cin, ln))
    {
        auto[ m, pl, ps] = ctre::match<rx>(ln);
        if(pl.to_view() == "1")
            a = sv_to_t<int>(ps.to_view());
        else
            b = sv_to_t<int>(ps.to_view());
    }
    return {a, b};
}

struct dirac_dice
{
    void inc()
    {
        ++now_;
        if( now_ == 101)
            now_ = 1;
        ++rolls_;
    }
    int rolls_ = 0;
    int now_ = 1;
    auto roll() -> int
    {
        auto sm { 0};
        for(auto n = 0; n < 3; ++n)
        {
            sm += now_;
            inc();
        }
        return sm;
    }
};

void play(int& p, int& s, dirac_dice& dd)
{
    auto m = dd.roll();
    p = p + m;
    while( p > 10)
        p -= 10;
    s += p;
}

int pt1 (auto in)
{
    dirac_dice dd;
    int p1 {in.first};
    int p2 {in.second};
    int p1s {0};
    int p2s {0};

    while(1)
    {
        play(p1, p1s, dd);
        if(p1s >= 1000)
            return p2s * dd.rolls_;
        play(p2, p2s, dd);
        if( p2s >= 1000)
            return p1s * dd.rolls_;
        std::cout << p1s << " " << p2s << " " << dd.rolls_ << "\n";
    }
    return 0;
}

int pt2 (auto in)
{
    return 0;
}

int main()
{
    auto in { get_input()};
    std::cout << "player 1, " << in.first << "\n";
    std::cout << "player 2, " << in.second << "\n";
    std::cout << "pt1 = " << pt1(in) << "\n";
    std::cout << "pt2 = " << pt2(in) << "\n";
}