#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>
#include <numeric>
#include <array>
#include <vector>
#include <tuple>

using namespace std::string_view_literals;

constexpr std::array hex { "0000"sv, "0001"sv, "0010"sv, "0011"sv, "0100"sv, "0101"sv, "0110"sv, "0111"sv, "1000"sv, "1001"sv, "1010"sv, "1011"sv, "1100"sv, "1101"sv, "1110"sv, "1111"sv } ;

auto c_to_h (char c) -> size_t
{
    return (c >= 'A') ? c - 'A' + 10 : c - '0';
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

std::tuple<std::string_view, int64_t, int64_t> pkt(std::string_view s)
{
    int64_t val{ -1 };
    if (s.size() < 6)
        return { {}, 0, val };
    int64_t ver = to_bin<3>(s);
    s.remove_prefix(3); // version
    auto id = to_bin<3>(s);
    s.remove_prefix(3);
    if (id == 4) // literal
    {
        val = 0;
        while (s[0] == '1')
        {
            s.remove_prefix(1);
            val *= 16;
            val += to_bin<4>(s);
            s.remove_prefix(4);
        }
        val *= 16;
        val += to_bin<5>(s);
        s.remove_prefix(5);
    }
    else // operator
    {
        auto eval = [](int64_t v1, int64_t v2, char id) -> int64_t
        {
            if (v1 == -1)
                return v2;
            switch (id)
            {
            case 0: // sum
                return v1 + v2;
            case 1: // product
                return v1 * v2;
            case 2: // min
                return (v1 < v2) ? v1 : v2;
            case 3: // max
                return (v1 > v2) ? v1 : v2;
            case 5: // gt
                return (v1 > v2) ? int64_t{ 1 } : int64_t{ 0 };
            case 6: // lt
                return (v1 < v2) ? int64_t{ 1 } : int64_t{ 0 };
            case 7: // eq
                return (v1 == v2) ? int64_t{ 1 } : int64_t{ 0 };
            }
            return 0;
        };
        if (s[0] == '0') // n bytes
        {
            int cnt = to_bin<16>(s);
            s.remove_prefix(16);
            std::string_view s2{ s.begin(), s.begin() + cnt };
            while (s2.size() > 6)
            {
                auto[s3, vr, vl] = pkt(s2);
                s2 = s3;
                ver += vr;
                val = eval(val, vl, id);
            }
            s.remove_prefix(cnt);
        }
        else // n pkts
        {
            s.remove_prefix(1);
            int cnt = to_bin<11>(s);
            s.remove_prefix(11);
            for (int n = 0; n < cnt; ++n)
            {
                auto[s2, vr, vl] = pkt(s);
                s = s2;
                ver += vr;
                val = eval(val, vl, id);
            }
        }
    }
    return { s, ver, val };
}

int main()
{
    auto in = get_input();
    auto p12 = pkt(in);
    std::cout << "pt1 = " << std::get<1>(p12) << "\n";
    std::cout << "pt2 = " << std::get<2>(p12) << "\n";
}