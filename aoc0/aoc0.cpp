#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>

#if 1
constexpr int players = 452;
constexpr int marbles = 71250;
#else
constexpr int players = 9;
constexpr int marbles = 25 ;
#endif

template<typename I> I mymod(I n, I sz)
{
	while (n >= sz)
		n -= sz;
	while (n < 0)
		n += sz;
	return n;
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

void pt1(int64_t np, int64_t nm)
{
	std::vector<uint64_t> pl;
	pl.resize(np);
	std::list<uint64_t> cir;
	cir.push_back(0);
	auto cm = std::begin(cir);
	int64_t cp = 0;

	for (int m = 1; m < nm; ++m)
	{
		// winner?
		if (m % 23 == 0)
		{
			pl[cp] += m;
			cm = move(cir, cm, -7);
//			cm = mymod( cm, static_cast<int64_t>(cir.size()));
			pl[cp] += *cm;
			cm = cir.erase(cm);
//			cm = mymod( cm, static_cast<int64_t>(cir.size()));
		}
		else
		{
			cm = move(cir, cm, 2);
//			cm = mymod( cm, static_cast<int64_t>(cir.size()));
			cm = cir.insert(cm, m);
		}
		// report
#if 0
		std::cout << "[" << cp+1 << "] ";
		auto cmv = *cm;
		for (auto v : cir)
		{
			if (v == cmv)
				std::cout << " [" << v << "] ";
			else
				std::cout << "  " << v << "  ";
		}
		std::cout << "\n";
#endif
		++cp;
		if (cp == np)
			cp = 0;
	}
	std::cout << "High score for " << np << " players and " << nm << " marbles = " << *std::max_element(std::begin(pl), std::end(pl)) << "\n";
}

int main()
{
	pt1( 9,   25 + 1);
#if 1
	pt1(10, 1618 + 1);
	pt1(13, 7999 + 1);
	pt1(17, 1104 + 1);
	pt1(21, 6111 + 1);
	pt1(30, 5807 + 1);
	pt1(players, marbles + 1);
	pt1(players, marbles * 100 + 1);
#endif
}
 
