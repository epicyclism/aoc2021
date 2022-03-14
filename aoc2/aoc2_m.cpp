#include <iostream>
#include <vector>
#include <utility>
#include <numeric>

using pt = std::pair<int, int>;

auto get_input()
{
	std::vector<pt> rv;
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

int pt1(auto& in)
{
	auto p1 = std::accumulate(in.begin(), in.end(), pt{ 0, 0 });
	return p1.first * p1.second;
}

int main()
{
	auto in{ get_input() };

}