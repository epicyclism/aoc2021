#include <iostream>
#include <string>
#include <array>
#include <vector>

#include <ctre.hpp>

struct row
{
    std::array<std::string, 10> in_;
    std::array<std::string, 4>  out_;
};

std::vector<row> get_input()
{
	constexpr auto rx_input = ctll::fixed_string{ R"(([abcdefg]+) ([abcdefg]+) ([abcdefg]+) ([abcdefg]+) ([abcdefg]+) ([abcdefg]+) ([abcdefg]+) ([abcdefg]+) ([abcdefg]+) ([abcdefg]+) | ([abcdefg]+) ([abcdefg]+) ([abcdefg]+) ([abcdefg]+))" };

    std::vector<row> rv;
    std::string ln;
    while(std::getline(std::cin, ln))
    {
        if( auto[m, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, d1, d2, d3, d4] = ctre::match<rx_input>(ln); m)
        {
            rv.push_back(row{p1.to_string(), p2.to_string(),p3.to_string(),p4.to_string(),p5.to_string(),p6.to_string(),p7.to_string(),p8.to_string(),p9.to_string(),p10.to_string(),d1.to_string(),d2.to_string(),d3.to_string(),d4.to_string()});
        }
        else
            std::cout << "parse error at " << ln << "\n";
    }

    return rv;
}

int pt1(auto v)
{
    return 0;
}

int main()
{
    auto v = get_input();
    std::cout << "got " << v.size() << " rows\n";
    std::cout << "pt1 = " << pt1(v) << "\n";
}