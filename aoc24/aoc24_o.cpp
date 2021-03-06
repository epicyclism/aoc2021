#include <iostream>
#include <array>
#include <vector>
#include <queue>
#include <string>
#include <string_view>

#include "ctre_inc.h"

using regs = std::array<int64_t, 4>;

enum class reg { w, x, y, z, i };
int reg_to_off(reg r)
{
    return static_cast<int>(r);
}

enum class opcode { inp, add, mul, div, mod, eql, tilt };

opcode op_f_sv(std::string_view s)
{
    if (s == "inp")
        return opcode::inp;
    if (s == "add")
        return opcode::add;
    if (s == "mul")
        return opcode::mul;
    if (s == "div")
        return opcode::div;
    if (s == "mod")
        return opcode::mod;
    if (s == "eql")
        return opcode::eql;
    return opcode::tilt;
}

reg reg_f_sv(std::string_view s)
{
    switch (s[0])
    {
    case 'w':
        return reg::w;
    case 'x':
        return reg::x;
    case 'y':
        return reg::y;
    case 'z':
        return reg::z;
    }
    return reg::i;
}

struct inst
{
    opcode  op_ = opcode::tilt;
    reg     a_ = reg::w;
    reg     b_ = reg::i;
    int64_t i_ = 0;
};

using program = std::vector<inst>;

auto get_input()
{
    program p;
    std::string ln;
    while (std::getline(std::cin, ln))
    {
        std::string_view op{ ln.data(), 3 };
        std::string_view de{ ln.data() + 4, 1 };
        if (ln.size() < 6) // inp
        {
            p.push_back({ opcode::inp, reg_f_sv(de), reg::w, 0 });
        }
        else
        {
            std::string_view src{ ln.data() + 6, ln.size() - 6 };
            auto sc = reg_f_sv(src);
            if (sc == reg::i)
            {
                p.push_back({ op_f_sv(op), reg_f_sv(de), sc, sv_to_t<int64_t>(src) });

            }
            else
            {
                p.push_back({ op_f_sv(op), reg_f_sv(de), sc, 0 });
            }
        }
    }
    return p;
}

regs execute(program p, std::queue<int64_t>& in, int64_t init_z = 0)
{
    regs r;
    r.fill(0);
    r[3] = init_z;;
    for (auto const& i : p)
    {
        switch (i.op_)
        {
        case opcode::inp:
            r[reg_to_off(i.a_)] = in.front();
            in.pop();
            break;
        case opcode::add:
            if (i.b_ == reg::i)
                r[reg_to_off(i.a_)] += i.i_;
            else
                r[reg_to_off(i.a_)] += r[reg_to_off(i.b_)];
            break;
        case opcode::mul:
            if (i.b_ == reg::i)
                r[reg_to_off(i.a_)] *= i.i_;
            else
                r[reg_to_off(i.a_)] *= r[reg_to_off(i.b_)];
            break;
        case opcode::div:
            if (i.b_ == reg::i)
                r[reg_to_off(i.a_)] /= i.i_;
            else
                r[reg_to_off(i.a_)] /= r[reg_to_off(i.b_)];
            break;
        case opcode::mod:
            if (i.b_ == reg::i)
                r[reg_to_off(i.a_)] %= i.i_;
            else
                r[reg_to_off(i.a_)] %= r[reg_to_off(i.b_)];
            break;
        case opcode::eql:
            if (i.b_ == reg::i)
                r[reg_to_off(i.a_)] = (r[reg_to_off(i.a_)] == i.i_ ? 1 : 0);
            else
                r[reg_to_off(i.a_)] = (r[reg_to_off(i.a_)] == r[reg_to_off(i.b_)] ? 1 : 0);
            break;
        default:
            break;
        }
    }
    return r;
}

int64_t proc(program const& p, auto input)
{
    std::queue<int64_t> q;
    for (auto i : input)
        q.push(i);
    auto r = execute(p, q);
    return r[3];
}

void pt1(program const& p)
{
    std::array<int64_t, 14> mn { 1,1,4,9,9,6,2,9,6,9,8,9,7,1 };
    std::cout << "zf = " << proc(p, mn) << "\n";
    std::array<int64_t, 14> mn2{ 9,3,4,9,9,6,2,9,6,9,8,9,9,9 };
    std::cout << "zf = " << proc(p, mn2) << "\n";
    std::array<int64_t, 14> mn3{ 9,9,2,6,4,1,2,8,9,1,1,2,6,9 };
    std::cout << "zf = " << proc(p, mn3) << "\n";
}

//11499618121471
void pt2(program const& p)
{
    for(int d = 8; d > 0; --d)
    for(int e = 9; e > 0; --e)
        for(int f = 9; f > 0; --f)
            for(int g = 9; g > 0; --g)
                for (int h = 9; h > 0; --h)
                    for (int i = 9; i > 0; --i)
                        for (int j = 9; j > 0; --j)
                            for (int k = 9; k > 0; --k)
                                for (int l = 9; l > 0; --l)
                                    for (int m = 9; m > 0; --m)
                                        for (int n = 9; n > 0; --n)
                                        {
                                            std::array<int64_t, 14> mn{ 1,1,4,d,e,f, g, h, i, j, k, l, m, n };
                                            if (proc(p, mn) == 0)
                                                std::cout << "1149" << d << e << f << g << h << i << j << k << l << m << n << " gets 0\n";
                                        }
}

int main()
{
    auto in{ get_input() };
    pt1(in);
    pt2(in);
}

// 11499618121471 too high
// 11494118121471 too high