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

constexpr inline bool odd(int n)
{
	return n & 1;
}

constexpr inline int half(int n)
{
	return n / 2;
}


template <typename A> constexpr A power_accumulate_semigroup(A r, A a, int n)
{
	// precondition(n >= 0);
	if (n == 0) return r;
	while (true) {
		if (odd(n)) {
			r = r * a;
			if (n == 1) return r;
		}
		n = half(n);
		a = a * a;
	}
}

template <typename A> constexpr A power_semigroup(A a, int n)
{
	// precondition(n > 0);
	while (!odd(n)) 
	{
		a = a * a;
		n = half(n);
	}
	if (n == 1) return a;
	return power_accumulate_semigroup(a, a * a, half(n - 1));
}

template <typename A> constexpr A power_monoid(A a, int n)
{
	// precondition(n >= 0);
//	if (n == 0) return A(1);
	return power_semigroup(a, n);
}

template<int N, typename M> constexpr auto powN(M const& m)
{
	static_assert(N > 0, "powN not defined for exponents less than 0");
	M rv{ m };
	for (int n = 0; n < N - 1; ++n)
		rv = rv * m;
	return rv;
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
//	v = powN<N>(act) * v;
	v = power_monoid(act, N) * v;
	return std::accumulate(v.begin(), v.end(), 0ll);
}

int main()
{
	auto in = get_input();
	std::cout << "pt1 " << simulate_fish<80>(in) << "\n";
	std::cout << "pt2 " << simulate_fish<256>(in) << "\n";
}