#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <string_view>
#include <algorithm>

#include <ctre.hpp>

struct rule
{
    std::string key_;
    char        val_;
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

void step(std::string& s, std::vector<rule> const& rules)
{
    int n {0};
    while( n < s.size() - 1)
    {
        std::string_view v { s.data() + n, 2};
        auto ra = std::find_if(rules.begin(), rules.end(), [v](auto& p){ return p.key_== v;});
        if( ra != rules.end())
        {
            s.insert(n + 1, 1, (*ra).val_);
            ++n;
        }
        ++n;
    }
//    std::cout << s << "\n";
}

int pt1( auto const& d)
{
    std::string s{ d.first};
    for( int n = 0; n < 10; ++n)
        step(s, d.second);
    std::array<int, 26> freq{0};
    for(auto c : s)
        ++freq[c - 'A'];
    for( int n = 0; n < 26; ++n)
        std::cout << char('A' + n) << " - " << freq[n] << "\n";
    auto mn { s.size()};
    auto mx { 0};
    for( auto i : freq)
    {
        if( i != 0 && i < mn)
            mn = i;
        if( i > mx)
            mx = i;
    }
    std::cout << mn << " " << mx << "\n";
    return mx - mn;
}

int main()
{
    auto d = get_input();
    std::cout << "template = " << d.first << "\n";
    std::cout << "and got " << d.second.size() << " rules\n";

    std::cout << "pt1 = " << pt1(d) << "\n";
}