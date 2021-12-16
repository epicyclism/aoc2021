#include <iostream>

int64_t sum(int64_t a)
{
	return a;
}

int64_t sum(int64_t a, int64_t b)
{
	return a + b;
}

int64_t sum(int64_t a, int64_t b, int64_t c)
{
	return a + b + c;
}

int64_t sum(int64_t a, int64_t b, int64_t c, int64_t d)
{
	return a + b + c + d;
}

int64_t sum(int64_t a, int64_t b, int64_t c, int64_t d, int64_t e)
{
	return a + b + c + d + e;
}

int64_t sum(int64_t a, int64_t b, int64_t c, int64_t d, int64_t e, 
	int64_t a0, int64_t b0, int64_t c0, int64_t d0, int64_t e0,
	int64_t a1, int64_t b1, int64_t c1, int64_t d1, int64_t e1,
	int64_t a2, int64_t b2, int64_t c2, int64_t d2, int64_t e2, 
	int64_t a3, int64_t b3, int64_t c3, int64_t d3, int64_t e3, 
	int64_t a4, int64_t b4, int64_t c4, int64_t d4, int64_t e4, 
	int64_t a5, int64_t b5, int64_t c5, int64_t d5, int64_t e5, 
	int64_t a6, int64_t b6, int64_t c6, int64_t d6, int64_t e6, 
	int64_t a7, int64_t b7, int64_t c7, int64_t d7, int64_t e7, 
	int64_t a8, int64_t b8, int64_t c8, int64_t d8, int64_t e8,
	int64_t a9, int64_t b9, int64_t c9 )
{
	return a + b + c + d + e +
		a0 + b0 + c0 + d0 + e0 + 
		a1 + b1 + c1 + d1 + e1 + 
		a2 + b2 + c2 + d2 + e2 + 
		a3 + b3 + c3 + d3 + e3 + 
		a4 + b4 + c4 + d4 + e4 + 
		a5 + b5 + c5 + d5 + e5 + 
		a6 + b6 + c6 + d6 + e6 + 
		a7 + b7 + c7 + d7 + e7 + 
		a8 + b8 + c8 + d8 + e8 + 
		a9 + b9 + c9 ;
}

int64_t prod(int64_t a)
{
	return a;
}

int64_t prod(int64_t a, int64_t b)
{
	return a * b;
}

int64_t prod(int64_t a, int64_t b, int64_t c)
{
	return a * b * c;
}

int64_t prod(int64_t a, int64_t b, int64_t c, int64_t d)
{
	return a * b * c * d;
}

int64_t prod(int64_t a, int64_t b, int64_t c, int64_t d, int64_t e)
{
	return a * b * c * d * e;
}

int64_t min(int64_t a)
{
	return a;
}

int64_t min(int64_t a, int64_t b)
{
	return a < b ? a : b;
}

int64_t min(int64_t a, int64_t b, int64_t c)
{
	return min(a, min(b, c));
}

int64_t min(int64_t a, int64_t b, int64_t c, int64_t d)
{
	return min(a, min(b, c, d));
}

int64_t min(int64_t a, int64_t b, int64_t c, int64_t d, int64_t e)
{
	return min(a, min(b, c, d, e));
}

int64_t max(int64_t a)
{
	return a;
}

int64_t max(int64_t a, int64_t b)
{
	return a > b ? a : b;
}

int64_t max(int64_t a, int64_t b, int64_t c)
{
	return max(a, max(b, c));
}

int64_t max(int64_t a, int64_t b, int64_t c, int64_t d)
{
	return max(a, max(b, c, d));
}

int64_t max(int64_t a, int64_t b, int64_t c, int64_t d, int64_t e)
{
	return max(a, max(b, c, d, e));
}

int64_t gt(int64_t l, int64_t r)
{
	return l > r;
}

int64_t lt(int64_t l, int64_t r)
{
	return l < r;
}

int64_t eq(int64_t l, int64_t r)
{
	return l == r;
}

int main()
{
	auto v = sum(9, prod(gt(981304, 16119042), 11), max(max(max(sum(sum(min(prod(sum(sum(sum(prod(sum(max(max(sum(min(sum(max(min(sum(14481)))))))))))))))))))), 254, sum(prod(12, 3, 4), prod(12, 9, 3), prod(12, 9, 10)), prod(209, 119, 37, 132, 41), prod(3510349, eq(7606021, 4964518)), min(213042455, 220, 814, 16272206), sum(11409284, 41744319988, 883), prod(203, 21, 193), prod(gt(1551006, 1551006), 176), prod(gt(906407934374, 35922), 208), min(13445129436, 1779, 138809768), 3738413164, 2647, 13871, prod(892291911800, lt(sum(8, 14, 2), sum(2, 15, 10))), min(14, 453), prod(12519, lt(454, 68125835026)), sum(2), 15, prod(63284, lt(3042045387, 72)), 5, sum(761, 49827), prod(2150, lt(10482031, 10482031)), prod(1011, lt(sum(13, 15, 4), sum(14, 4, 14))), prod(1, eq(sum(15, 5, 7), sum(9, 11, 9))), prod(944530, eq(2261, 1377617)), sum(3, 96, 6, 847), prod(gt(sum(3, 6, 13), sum(7, 4, 6)), 3899), sum(195, 94, 5037707317, 6262081, 193), min(1775244, 245, 1198, 188, 13), 451897794113, prod(gt(sum(13, 13, 14), sum(8, 2, 12)), 51), prod(44, 134), prod(sum(14, 11, 4), sum(5, 15, 6), sum(12, 10, 8)), max(106, 5095434, 2803, 59122), 3473296998, prod(lt(11670636, 11670636), 90), prod(12, gt(160, 1939731726)), max(2704, 7), prod(133, 109, 130, 151), 3821869291, prod(94), prod(799654886371, gt(417505, 56377)), min(137), prod(2061, eq(1754, 1754)), prod(lt(182866107, 40938011899), 13725986), max(79, 108, 16984535703, 8, 100526648), max(4, 185, 40), prod(gt(64019020, 64019020), 420188), max(339347), prod(1283, lt(1954, 109)));
	std::cout << v << "\n";
}