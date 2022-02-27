#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <numeric>
#include <type_traits>
#include <cctype>

template<int X, int Y, typename T = int64_t> struct matrix2
{
	std::array<T, X * Y> arr_;

	T get(int x, int y) const
	{
		return arr_[y * X + x];
	}
	T& set(int x, int y)
	{
		return arr_[y * X + x];
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
				{
//					std::cout << "[ " << i << ", " << j << " ] += [ " << i << ", " << k << " ] * [ " << k << ", " << j << " ]\n";
					rv.set(i, j) += a.get(k, j) * b.get(i, k);
				}
			}
		}

		return rv;
	}
};

constexpr matrix2<9, 9, int64_t> act{
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

constexpr auto actN(int N)
{
	matrix2<9, 9, int64_t> rv{ act };
	for (int n = 0; n < N - 1; ++n)
		rv = rv * act;
	return rv;
}

template<int X, int Y, typename T> void print(matrix2<X, Y, T> const& m)
{
	for (int y = 0; y < Y; ++y)
	{
		for (int x = 0; x < X; ++x)
			std::cout << m.get(x, y) << " ";
		std::cout << "\n";
	}
}

auto get_input()
{
	matrix2<1, 9> ra{};
	std::string ln;
	std::getline(std::cin, ln);
	std::for_each(ln.begin(), ln.end(), [&ra](auto c) { if (std::isdigit(c)) ++ra.arr_[c - '0']; });
	return ra;
}

template<int N> int64_t simulate_fish(matrix2<1, 9> v)
{
	v = actN(N) * v;
	return std::accumulate(v.arr_.begin(), v.arr_.end(), 0ll);
}

int main()
{
	std::cout << "actN(80)\n";
	print(actN(80));
	std::cout << "actN(256)\n";
	print(actN(256));
	auto in = get_input();
	std::cout << "pt1 " << simulate_fish<80>(in) << "\n";
	std::cout << "pt2 " << simulate_fish<256>(in) << "\n";
}