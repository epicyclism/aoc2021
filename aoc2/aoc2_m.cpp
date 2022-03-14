#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <numeric>

using hd = std::pair<int, int>;

auto get_input()
{
	std::vector<hd> rv;
	while (std::cin)
	{
		std::string d;
		int X;
		std::cin >> d >> X;
		if (d.empty())
			break;
		switch (d[0])
		{
			case 'f':
				rv.emplace_back( X, 0 );
				break;
			case 'u':
				rv.emplace_back(0, -X);
				break;
			case 'd':
				rv.emplace_back(0, X);
				break;
			default:
				std::cout << "TILT\n";
				break;
		}
	}
	return rv;
}

int pt1(auto const& in)
{
	auto p1 = std::accumulate(in.begin(), in.end(), hd{ 0, 0 }, [](auto const& sum, auto const& val) { return hd{ sum.first + val.first, sum.second + val.second}; });
	return p1.first * p1.second;
}

using ahd = std::tuple<int, int, int>;

int pt2(auto const& in)
{
	auto p2 = std::accumulate(in.begin(), in.end(), ahd{ 0, 0, 0 }, [](auto const& sum, auto const& val) { return ahd{ std::get<0>(sum) + val.second, std::get<1>(sum) + val.first, std::get<2>(sum) + std::get<0>(sum) * val.first}; });
	return std::get<1>(p2) * std::get<2>(p2);
}

int main()
{
	auto in{ get_input() };
	std::cout << "pt1 = " << pt1(in) << "\n";
	std::cout << "pt2 = " << pt2(in) << "\n";
}