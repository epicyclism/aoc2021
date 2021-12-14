#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <string_view>
#include <algorithm>
#include <numeric>

#include <ctre.hpp>

struct rule
{
    std::string key_;
    char        val_;
    uint64_t    cnt_;
};

using data_t = std::pair<std::string, std::vector<rule>>;

auto get_input()
{
    constexpr auto rxrule = ctll::fixed_string{ R"((\w+) -> (\w+))" };
    data_t rv;

    if ( !std::getline(std::cin, rv.first))
        std::cout << "parse error on very first line\n";
    std::string ln;
    std::getline(std::cin, ln);
    while(std::getline(std::cin, ln))
    {
        if( auto[m, f, t] = ctre::match<rxrule>(ln); m)
            rv.second.push_back({f.to_string(), t.to_view().front()});
        else
            std::cout << "parse error at " << ln << "\n";
    }
    return rv;
}

uint64_t pt12(auto& d, int steps)
{
    std::vector<rule>& rules{ d.second };
    for (auto& r : rules)
        r.cnt_ = 0;
    std::array<uint64_t, 26> freq{ 0 };
    for (auto c : d.first)
        ++freq[c - 'A'];
    for (auto n = 0; n < d.first.size() - 1; ++n)
    {
        std::string_view v{ d.first.data() + n, 2 };
        auto ra = std::find_if(rules.begin(), rules.end(), [v](auto& p) { return p.key_ == v; });
        ++(*ra).cnt_;
    }
    for (int n = 0; n < steps; ++n)
    {
        std::vector<rule> r2{ rules };
        for (auto& r : r2)
            r.cnt_ = 0;
        for (auto& r : rules)
        {
            char cp[3];
            cp[0] = r.key_[0];
            cp[1] = r.val_;
            cp[2] = r.key_[1];
            std::string_view v{ cp, cp + 2 };
            auto ra = std::find_if(r2.begin(), r2.end(), [v](auto& p) { return p.key_ == v; });
            (*ra).cnt_ += r.cnt_;
            std::string_view v2{ cp + 1, cp + 3 };
            ra = std::find_if(r2.begin(), r2.end(), [v2](auto& p) { return p.key_ == v2; });
            (*ra).cnt_ += r.cnt_;
            freq[r.val_ - 'A'] += r.cnt_;
        }
        rules = r2;
    }
    uint64_t mx{ 0 };
    for (auto i : freq)
        if (i > mx)
            mx = i;
    uint64_t mn{ mx };
    for (auto i : freq)
        if (i != 0 && i < mn)
            mn = i;

    return mx - mn;
}

int main()
{
    auto d = get_input();

    std::cout << "pt1  = " << pt12(d, 10) << "\n";
    std::cout << "pt2 = " << pt12(d, 40) << "\n";
}