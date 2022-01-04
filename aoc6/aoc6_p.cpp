#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <cctype>

auto get_input()
{
	std::array<int64_t, 10> ra{};
	std::string ln;
	std::getline(std::cin, ln);
	std::for_each(ln.begin(), ln.end(), [&ra](auto c) { if (std::isdigit(c)) ++ra[c - '0']; });
	return ra;
}

template<int X, int Y, typename T = int64_t> struct matrix2
{
	std::array<T, X* Y> data_;

	constexpr T at(size_t x)
	{
		return data_[x];
	}

	constexpr T at(size_t x, size_t y) 
	{
		return data_[y * X + x];
	}
	constexpr friend auto operator*(matrix2<X, Y, T> a, auto const& b) -> matrix2<decltype(b)::X, decltype(b)::Y, T>
	{
		return decltype(b) {};
	}
};


void test()
{
	matrix2<2, 2> a{ 1, 2, 3, 4 };
	matrix2<2, 2> b{ 5, 6, 7, 8 };
	auto c = a * b;
}


int main()
{
	auto in{ get_input() };
	for (auto v : in)
		std::cout << v << " ";
	std::cout << "\n";
	test();
}