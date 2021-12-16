#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>
#include <numeric>
#include <array>

using namespace std::string_view_literals;

constexpr std::array hex { "0000"sv, "0001"sv, "0010"sv, "0011"sv, "0100"sv, "0101"sv, "0110"sv, "0111"sv, "1000"sv, "1001"sv, "1010"sv, "1011"sv, "1100"sv, "1101"sv, "1110"sv, "1111"sv } ;

auto c_to_h (char c) -> size_t
{
    return (c > 'A') ? c - 'A' + 10 : c - '0';
}

auto get_input()
{
    std::string op;
    std::string ln;
    std::getline(std::cin, ln);
    for(auto c : ln)
       op += hex[c_to_h(c)];
    return op;
}

template<int bits> int to_bin(std::string_view s)
{
    return std::accumulate(s.begin(), s.begin() + bits, 0, [](auto s, auto v) { return s * 2 + v - '0';});
}

std::string_view skip(std::string_view s)
{
    auto id = to_bin<3>(s);
    s.remove_prefix(3);
    if( id == 4)
    {
        while( s[0] == '1')
            s.remove_prefix(5);
    }
    else
    {
        auto skip {0};
        if( s[0] == '0')
            skip = to_bin<16>(s) + 16;
        else
        {
            s.remove_prefix(1);
            skip = to_bin<11>(s) + 11;
        }
        s.remove_prefix( 16 + skip);
    }
    return s;
}

int pkt(std::string_view s)
{
    auto v = to_bin<3>(s);
    s.remove_prefix(3);
    std::cout << v << "\n";
    s = skip(s);
    return v + pkt(s);
}

int pt1(std::string_view s)
{
    return pkt(s);
}

int main()
{
    auto in = get_input();
//    std::cout << in << "\n";
    std::cout << "pt1 = " << pt1(in) << "\n";
}
