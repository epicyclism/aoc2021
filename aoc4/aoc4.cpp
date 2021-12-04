#include <iostream>
#include <array>
#include <vector>
#include <bitset>
#include <cstdint>
#include <string>
#include <algorithm>
#include <numeric>
#include <optional>
#include <ctre.hpp>

template<typename T> T sv_to_t ( std::string_view sv)
{
	T t { 0 };
	std::from_chars(sv.data(), sv.data() + sv.size(), t);
	return t;
}

constexpr auto brd_w{5};
constexpr auto brd_size {brd_w * brd_w};
    constexpr std::array<std::bitset<brd_size>, 10> wins{
     0b1111100000000000000000000,
     0b0000011111000000000000000,
     0b0000000000111110000000000,
     0b0000000000000001111100000,
     0b0000000000000000000011111,
     0b1000010000100001000010000,
     0b0100001000010000100001000,
     0b0010000100001000010000100,
     0b0001000010000100001000010,
     0b0000100001000010000100001,
};

struct board
{
    std::bitset<brd_size> played_;
    std::array<uint8_t, brd_size> brd_;
    void play(uint8_t v)
    {
        auto f = std::find(brd_.begin(), brd_.end(), v);
        if( f != brd_.end())
        {
            played_.set(std::distance(brd_.begin(), f), true);
//            std::cout << +v << "\n";
        }
//        else
//           std::cout << "(" << +v << ")\n";
    }
    std::optional<size_t> win() const
    {
        for(auto w = 0; w < wins.size(); ++w)
            if( (played_ & wins[w]) == wins[w])
                return w;
        return std::nullopt;
    }
    int compute()
    {
        auto sb = played_.to_string();
        return std::transform_reduce(brd_.begin(), brd_.end(), sb.begin(), 0, std::plus<>(), [&](auto p, auto b){ std::cout << "{" << +p << ", " << b << ")\n"; return b == '0' ? p : 0;});
    }
};

std::ostream& operator<<(std::ostream& o, board const& b)
{
    int c = 0;
    for(auto v : b.brd_)
    {
        o << +v << ' ';
        ++c;
        if( c == brd_w)
        {
             std::cout << "\n";
            c = 0;
        }
    } 
    return o;
}

std::pair<std::vector<uint8_t>, std::vector<board>> get_input ()
{
    constexpr auto rx_call = ctll::fixed_string{ R"((\d+),?)" };
    constexpr auto rx_row  = ctll::fixed_string{ R"( ?(\d+) +(\d+) +(\d+) +(\d+) +(\d+))" };
 
    std::string ln;
    std::vector<uint8_t> call;
    std::getline(std::cin, ln);
    for (auto m: ctre::range<rx_call>(ln))
        call.push_back(sv_to_t<uint8_t>(m.get<0>()));

    std::vector<board> brds;
    std::getline(std::cin, ln);
    board tmp;
    int cell { 0};
    while(std::getline(std::cin, ln))
    {
        if(ln.empty())
        {
            brds.emplace_back(std::move(tmp));
            cell = 0;
        }
        else
        if(auto[m, a, b, c, d, e] = ctre::match<rx_row>(ln); m)
        {
//            std::cout << ln << "\n";
            tmp.brd_[cell++] = sv_to_t<uint8_t>(a.to_view());
            tmp.brd_[cell++] = sv_to_t<uint8_t>(b.to_view());
            tmp.brd_[cell++] = sv_to_t<uint8_t>(c.to_view());
            tmp.brd_[cell++] = sv_to_t<uint8_t>(d.to_view());
            tmp.brd_[cell++] = sv_to_t<uint8_t>(e.to_view());
        }
    }
    brds.emplace_back(std::move(tmp));
    return {call, brds};
}

int pt1(auto nums, auto brds)
{
    for(auto n : nums)
    {
        for(auto& b : brds)
        {
            b.play(n);
            if( auto w = b.win(); w)
            {
                std::cout << b << "\n";
                std::cout << b.compute() << " * " << +n << "\n";
                return b.compute() * n;
            }
        }
    }
    return 0;
}

int main()
{
    auto[c, b] = get_input();
    for( auto& bd : b)
        std::cout << bd << "\n";
    std::cout << "got " << c.size() << " numbers and " << b.size() << " boards.\n";
    std::cout << "pt1 = " << pt1(c, b) << "\n";
}