#include <iostream>
#include <string>
#include <map>
#include <array>

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

struct deterministic_dice
{
    void inc()
    {
        if( now_ == 100)
            now_ = 0;
        ++now_;
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

void play(int& p, int& s, deterministic_dice& dd)
{
    auto m = dd.roll();
    p = p + m;
    while( p > 10)
        p -= 10;
    s += p;
}

int pt1 (auto in)
{
    deterministic_dice dd;
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
    }
    return 0;
}

struct state_t
{
    int p1_p_; // p1 place
    int p1_s_; // p1 score
    int p2_p_; // p2 place
    int p2_s_; // p2 score
    auto operator<=>(state_t const&) const = default;
};

using result_t = std::pair<int64_t, int64_t>;
using cache_t = std::map<state_t, result_t>;

constexpr auto rolls()
{
    std::array<int, 27> r;
    auto i{ r.begin() };
    for( int a = 1; a < 4; ++a)
        for( int b = 1; b < 4; ++b)
            for (int c = 1; c < 4; ++c)
            {
                *i = a + b + c;
                ++i;
            }
    return r;
}

result_t play2(state_t st, cache_t& c)
{
    if (c.contains(st))
        return (*c.find(st)).second;
    result_t r{ 0, 0 };
    for (auto n : rolls()) // player 1
    {
        state_t s2{ st };
        s2.p1_p_ += n;
        while (s2.p1_p_ > 10)
            s2.p1_p_ -= 10;
        s2.p1_s_ += s2.p1_p_;
        if (s2.p1_s_ >= 21) // win!
            ++r.first;
        else // player 2
        {
            for (auto m : rolls())
            {
                state_t s3{ s2 };
                s3.p2_p_ += m;
                while (s3.p2_p_ > 10)
                    s3.p2_p_ -= 10;
                s3.p2_s_ += s3.p2_p_;
                if (s3.p2_s_ >= 21) // win!
                    ++r.second;
                else // recurse
                {
                    auto rt = play2(s3, c);
                    r.first += rt.first;
                    r.second += rt.second;
                }
            }
        }
    }
    c.insert(std::make_pair(st, r));
    return r;;
}

int64_t pt2(auto in)
{
    cache_t c;

    auto r = play2({ in.first, 0, in.second, 0 }, c);
    return std::max(r.first, r.second);
}

int main()
{
    auto in { get_input()};
    std::cout << "pt1 = " << pt1(in) << "\n";
    std::cout << "pt2 = " << pt2(in) << "\n";
}