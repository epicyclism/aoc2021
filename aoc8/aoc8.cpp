#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdint>

#include <ctre.hpp>

struct row
{
    std::array<std::string, 10> in_;
    std::array<std::string, 4>  out_;
};

std::vector<row> get_input()
{
	constexpr auto rx_input_elt = ctll::fixed_string{ R"(([abcdefg]+))" };
    std::vector<row> rv;
    std::string ln;
    while (std::getline(std::cin, ln))
    {
        int n{ 0 };
        row r;
        for (auto m : ctre::range<rx_input_elt>(ln))
        {
            if (n < 10)
                r.in_[n] = m.to_string();
            else
                r.out_[n - 10] = m.to_string();
            ++n;
        }
        rv.push_back(r);
    }

    return rv;
}

int pt1(auto const& v)
{
    int cnt{ 0 };
    for (auto const& r : v)
        cnt += std::count_if(r.out_.begin(), r.out_.end(), [](auto& s) { return s.size() == 7 || s.size() == 4 || s.size() == 3 || s.size() == 2; });
    return cnt;
}

constexpr std::array<int8_t, 7> bits{ 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40 };

int8_t to_bits(std::string const& s)
{
    return std::accumulate(s.begin(), s.end(), int8_t{ 0 }, [](auto s, auto c) { return s | bits[c - 'a']; });
}

auto get_key(auto const& as)
{
    std::array<int8_t, 10> rv{ 0 };
    // first the ones we know
    for (auto& s : as)
    {
        switch (s.size())
        {
        case 2: // '1'
            rv[1] = to_bits(s);
            break;
        case 3: // '7'
            rv[7] = to_bits(s);
            break;
        case 4: // '4'
           rv[4] = to_bits(s);
           break;
        case 7: // '8'
           rv[8]= to_bits(s);
           break;
        default:
            break;
        }
    }
    auto cf = rv[1];
    auto bd = rv[4] & ~cf;
    for (auto& s : as)
    {
        auto sb = to_bits(s);
        switch (s.size())
        {
        case 5:
            if ((sb & cf) == cf) // '3'
                rv[3] = sb;
            else
            if ((sb & bd) == bd) // '5'
                rv[5] = sb;
            else               // '2'
                rv[2] = sb;
            break;
        case 6:
            if ((sb & (cf | bd)) == (bd | cf)) // '9'
                rv[9] = sb;
            else
            if ((sb & cf) == cf) //  '0'
                rv[0] = sb;
            else
                rv[6] = sb; // '6'
            break;
        default:
            break;
        }
    }
    return rv;
}

int pt2(auto const& v)
{
    int cnt{ 0 };
    for (auto& r : v)
    {
        int c{ 0 };
        auto key = get_key(r.in_);
        for (auto& s : r.out_)
        {
            c *= 10;
            c += std::distance(key.begin(), std::find(key.begin(), key.end(), to_bits(s)));
        }
        cnt += c;
    }
    return cnt;
}

int main()
{
    auto v = get_input();
    std::cout << "pt1 = " << pt1(v) << "\n";
    std::cout << "pt2 = " << pt2(v) << "\n";
}