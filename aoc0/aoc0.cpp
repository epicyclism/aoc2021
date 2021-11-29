#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <array>
#include <iterator>
#include <list>
#include <memory_resource>
#include <algorithm>
#include <charconv>

#include <ctre.hpp>

template<typename T> T sv_to_t ( std::string_view sv)
{
	T t { 0 };
	std::from_chars(sv.data(), sv.data() + sv.size(), t);
	return t;
}

std::pair<int64_t, int64_t> get_input()
{
	std::string ln;
	std::getline(std::cin, ln);
	constexpr auto rx_input = ctll::fixed_string{ R"((\d+) players; last marble is worth (\d+) points)" };
	if(auto[m, ps, ms] =  ctre::match<rx_input>(ln); m)
		return { sv_to_t<int64_t>(ps.to_view()), sv_to_t<int64_t>(ms.to_view())};
	return {0, 0};
}

template<typename I, typename C> I move(C& c, I i, int64_t n)
{
	if (n < 0)
	{
		while (n != 0)
		{
			if (i == c.begin())
				i = c.end();
			--i;
			++n;
		}
	}
	else
	{
		while (n != 0)
		{
			++i;
			if (i == c.end())
				i = c.begin();
			--n;
		}
	}
	return i;
}

int64_t play(int64_t np, int64_t nm)
{
	std::vector<uint64_t> pl;
	pl.resize(np);
	std::list<uint64_t> cir;
	cir.push_back(0);
	auto cm = std::begin(cir);
	int64_t cp = 0;

	for (int m = 1; m <= nm; ++m)
	{
		// winner?
		if (m % 23 == 0)
		{
			pl[cp] += m;
			cm = move(cir, cm, -7);
			pl[cp] += *cm;
			cm = cir.erase(cm);
		}
		else
		{
			cm = move(cir, cm, 2);
			cm = cir.insert(cm, m);
		}
		++cp;
		if (cp == np)
			cp = 0;
	}
	return *std::max_element(std::begin(pl), std::end(pl)) ;
}

int64_t play2(int64_t np, int64_t nm)
{
	std::vector<uint64_t> pl(np);
	std::vector<std::byte> buf(nm * 32);
	std::pmr::monotonic_buffer_resource mbr{buf.data(), buf.size()};
        std::pmr::polymorphic_allocator<uint64_t> pa{&mbr};
        std::pmr::list<uint64_t> cir{pa};
	cir.push_back(0);
	auto cm = std::begin(cir);
	int64_t cp = 0;

	for (int m = 1; m <= nm; ++m)
	{
		// winner?
		if (m % 23 == 0)
		{
			pl[cp] += m;
			cm = move(cir, cm, -7);
			pl[cp] += *cm;
			cm = cir.erase(cm);
		}
		else
		{
			cm = move(cir, cm, 2);
			cm = cir.insert(cm, m);
		}
		++cp;
		if (cp == np)
			cp = 0;
	}
	return *std::max_element(std::begin(pl), std::end(pl)) ;
}

int main()
{
#if defined (TEST)
	constexpr std::pair<int64_t,int64_t> tests [] = { { 9, 25}, {10, 1618}, {13, 7999}, {17, 1104}, {21, 6111}, {30, 5807}};
	for(auto const& pm : tests)
		std::cout << pm.first << ", " << pm.second << " = " << play(pm.first, pm.second) << "\n";
#else
	auto[players, marbles] = get_input();
#if 0
	std::cout << "p1 = " << play(players, marbles) << "\n";
	std::cout << "p2 = " << play(players, marbles * 100) << "\n";
#else
	std::cout << "p1 = " << play2(players, marbles) << "\n";
	std::cout << "p2 = " << play2(players, marbles * 100) << "\n";
#endif
#endif
}
 
