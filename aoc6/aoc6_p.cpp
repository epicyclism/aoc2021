#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <numeric>
#include <cctype>

template<int X, int Y, typename T = int64_t> struct matrix2	: public std::array<T, X * Y>
{
	constexpr T get(int x, int y) const
	{
		return this->operator[](y * X + x);
	}
	constexpr T& set(int x, int y)
	{
		return this->operator[](y* X + x);
	}
	template<int Z> constexpr friend  auto operator*(matrix2<X, Y, T> const& a, matrix2<Z, Y, T>const& b) -> std::remove_cvref_t<decltype(b)>
	{
		static_assert(X == Z || Z == 1, "matrices don't match for multiplication.");
		std::remove_cvref_t<decltype(b)> rv{ 0 };
		for (auto i = 0; i < Z; ++i)
		{
			for (auto j = 0; j < Y; ++j)
			{
				for (auto k = 0; k < X; ++k)
					rv.set(i, j) += a.get(k, j) * b.get(i, k);
			}
		}
		return rv;
	}
};

constexpr matrix2<9, 9, int64_t> act
{
	0, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0,
};

template<typename T> constexpr T power(T const& t, int n)
{
	if (n == 1)
		return t;
	if (n & 1)
		return power(t * t, n / 2) * t;
	return power(t * t, n / 2);
}

auto get_input()
{
	matrix2<1, 9> ra{};
	std::string ln;
	std::getline(std::cin, ln);
	std::for_each(ln.begin(), ln.end(), [&ra](auto c) { if (std::isdigit(c)) ++ra[c - '0']; });
	return ra;
}

template<int N> int64_t simulate_fish(matrix2<1, 9> v)
{
	v = power(act, N) * v;
	return std::accumulate(v.begin(), v.end(), 0ll);
}

int main()
{
	auto in = get_input();
	std::cout << "pt1 " << simulate_fish<80>(in) << "\n";
	std::cout << "pt2 " << simulate_fish<256>(in) << "\n";
}