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
        std::string_view op{ ln.begin(), ln.begin() + 3 };
        std::string_view de{ ln.begin() + 4, ln.begin() + 5 };
        if (ln.size() < 6) // inp
        {
            p.push_back({ opcode::inp, reg_f_sv(de), reg::w, 0 });
        }
        else
        {
            std::string_view src{ ln.begin() + 6, ln.end() };
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
            std::cout << "z = " << r[3] << "\n";
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
                r[reg_to_off(i.a_)] = r[reg_to_off(i.a_)] == i.i_;
            else
                r[reg_to_off(i.a_)] = r[reg_to_off(i.a_)] == r[reg_to_off(i.b_)];
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
    std::array<int64_t, 14> mn{ 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    std::cout << "zf = " << proc(p, mn) << "\n";
}

int main()
{
    auto in{ get_input() };
    pt1(in);
}
