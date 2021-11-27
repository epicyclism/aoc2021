#include <cstdint>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

#include "../../compile-time-regular-expressions/single-header/ctre.hpp"

constexpr auto deal_new_stack_rx = ctll::fixed_string{ R"(deal into new stack)" };
constexpr auto cut_rx = ctll::fixed_string{ R"(cut (-?\d+))" };
constexpr auto deal_increment_rx = ctll::fixed_string{ R"(deal with increment (-?\d+))" };

using int_t = int64_t;

template<int_t N> int_t mod(int_t m)
{
    while (m < 0)
        m += N;
    return m % N;
}

template<typename T, T N> T multiply_mod(T a, T b)
{
    T result{ 0 };

    while (b)
    {
        if (b % 2 == 1)
        {
            result += a;
            result = mod<N>(result);
        }
        b /= 2;
        a += a;
        a = mod<N>(a);
    }
    return result;
}

template<int_t N> struct ab_t
{
    int_t a_ = 1;
    int_t b_ = 0;
    ab_t<N>& operator*= (ab_t<N> rh)
    {
        a_ = multiply_mod<int_t, N>(a_, rh.a_);
        auto bt = multiply_mod<int_t, N>(b_, rh.a_);
        b_ = mod<N>(rh.b_ + bt);
        return *this;
    }
    friend ab_t<N> operator* (ab_t<N> lh, ab_t<N> const& rh)
    {
        lh *= rh;
        return lh;
    }
};

template<int_t N>
std::ostream& operator<<(std::ostream& ostr, ab_t<N> const& ab)
{
    ostr << "{ " << ab.a_ << ", " << ab.b_ << " }";
    return ostr;
}

enum op_type { deal_new_stack, cut, deal_inc, };

struct op
{
    op_type ot_;
    int val_;
    op(op_type ot, int val = 0) : ot_(ot), val_(val)
    {}
    template<int_t N> ab_t<N> get() const
    {
        switch (ot_)
        {
        case deal_new_stack:
            return { N - 1, N - 1 };
        case cut:
            return { 1, N - val_};
        case deal_inc:
            return { val_, 0 };
        default:
            return {};
        }
    }
};

auto get_input()
{
    std::vector<op> rv;
    std::string ln;
    while (std::getline(std::cin, ln))
    {
        if (auto m = ctre::match<deal_new_stack_rx>(ln); m)
            rv.emplace_back(deal_new_stack);
        else
            if (auto [m, v] = ctre::match<cut_rx>(ln); m)
                rv.emplace_back(cut, std::stoi(v.to_string()));
            else
                if (auto [m, v] = ctre::match<deal_increment_rx>(ln); m)
                    rv.emplace_back(deal_inc, std::stoi(v.to_string()));
                else
                    std::cout << "Parse error : " << ln << '\n';
    }
    return rv;
}

template<int_t N>
int_t act(ab_t<N> param, int_t val)
{
    return mod<N>(multiply_mod<int_t, N>(val, param.a_) + param.b_);
}

template<int_t N> ab_t<N> condense(std::vector<op> const& sh)
{
    ab_t<N> rv{};
    for (auto& o : sh)
        rv *= o.get<N>();
    return rv;
}

template<typename T> T exponentiate(T value, int_t power)
{
    T result{};

    while (power)
    {
        if (power % 2 == 1)
            result *= value;
        power /= 2;
        value *= value;
    }
    return result;
}

template<typename T, int_t N> T exponentiate_mod(T value, int_t power)
{
    T result{1};

    while (power)
    {
        if (power % 2 == 1)
            result = multiply_mod<T, N>(result, value);
        power /= 2;
        value = multiply_mod<T, N>(value, value);
    }
    return result;
}

template<int_t N> ab_t<N> invert(ab_t<N> op)
{
    int_t ai = exponentiate_mod<int_t, N>(op.a_, N - 2);
    int_t bi = multiply_mod<int_t, N>(op.b_, ai);
    bi = mod<N>(-1 * bi) ;

    return { ai, bi};
}

int main()
{
    auto in = get_input();
    auto op1 = condense<10007>(in);
    auto pt1 = act(op1, 2019);
    std::cout << "pt1  = " << pt1 << '\n';
    auto op2 = condense<119315717514047LL>(in);
    auto op3 = exponentiate(op2, 101741582076661LL);
    auto op4 = invert<119315717514047LL>(op3);
    auto pt2 = act(op4, 2020);
    auto x2 = act(op3, pt2);
    std::cout << "pt2  = " << pt2 << " (" << x2 << ")\n";
}
