#include <iostream>
#include <array>
#include <vector>
#include <queue>
#include <string>
#include <string_view>
#include <algorithm>

#include "ctre_inc.h"

using regs = std::array<int64_t, 4>;

enum class reg    { w, x, y, z, i};
int reg_to_off(reg r)
{
    return static_cast<int>(r);
}

enum class opcode { inp, add, mul, div, mod, eql, tilt};

opcode op_f_sv(std::string_view s)
{
    if(s == "inp")
        return opcode::inp;
    if(s == "add")
        return opcode::add;
    if(s == "mul")
        return opcode::mul;
    if(s == "div")
        return opcode::div;
    if(s == "mod")
        return opcode::mod;
    if(s == "eql")
        return opcode::eql;
    return opcode::tilt;
}

reg reg_f_sv(std::string_view s)
{
    switch(s[0])
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
    reg     a_  = reg::w;
    reg     b_  = reg::i;
    int64_t i_  = 0;
};

using program = std::vector<inst> ;

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
            std::string_view src{ ln.data() + 6, ln.size() - 6};
            auto sc = reg_f_sv(src);
            if (sc == reg::i)
            {
                p.push_back({ op_f_sv(op), reg_f_sv(de), sc, sv_to_t<int64_t>(src)});

            }
            else
            {
                p.push_back({ op_f_sv(op), reg_f_sv(de), sc, 0});
            }
        }
    }
    return p;
}

void apply_inst(inst const& i, regs& r)
{
    switch (i.op_)
    {
    case opcode::inp:
        std::cout << "tilt\n";
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
    default:
        break;
    }
}

std::pair<int64_t, int64_t> pt12(program const& p)
{
    struct alu
    {
        regs r_;
        int64_t mx_;
    	int64_t mn_;
    };
    auto my_unique = [](auto& vr)
    {
        auto b {vr.begin()};
        auto e {vr.end()};
        if( b == e)
            return e;
        auto r {b};
        while(++b != e)
            if( !((*b).r_[3] == (*r).r_[3]) && r+1 != b)
            {
                ++r;
                *r = std::move(*b);
            }
            else
            {
                (*r).mx_ = std::max((*r).mx_, (*b).mx_);
                (*r).mn_ = std::min((*r).mn_, (*b).mn_);
            }
        return ++r;
    };
    std::vector<alu> vr;
    vr.push_back({});
    vr.back().r_.fill(0);
    vr.back().mx_ = 0;
    vr.back().mn_ = 0;

    for (auto const& i : p)
    {
        if (i.op_ == opcode::inp)
        {
            std::vector<alu> vrr;
            std::sort(vr.begin(), vr.end(), [](auto const& l, auto const& r){ return l.r_[3] < r.r_[3];});
//            vr.erase(std::unique(vr.begin(), vr.end(), [](auto const& l, auto const& r){ return l.r_[3] == r.r_[3];}), vr.end());
            vr.erase(my_unique(vr), vr.end());
            for (auto& r : vr)
            {
                for (int n = 1; n < 10; ++n)
                {
                    auto rn{ r };
                    rn.r_[reg_to_off(i.a_)] = n;
                    rn.mx_ *= 10;
                    rn.mx_ += n;
        		    rn.mn_ *= 10;
        		    rn.mn_ += n;
                    vrr.emplace_back(rn);
                }
            }
            vr.swap(vrr);
        }
        else
            for (auto& r : vr)
                apply_inst(i, r.r_);
    }
    std::erase_if(vr, [](auto& r) { return r.r_[3] != 0; });
    auto mx = (*std::max_element(vr.begin(), vr.end(), [](auto const& l, auto const& r) { return l.mx_ < r.mx_; })).mx_;
    auto mn = (*std::min_element(vr.begin(), vr.end(), [](auto const& l, auto const& r) { return l.mn_ < r.mn_; })).mn_;
    
    return { mx, mn};
}

int main()
{
    auto in { get_input()};
    auto [p1, p2] = pt12(in) ;
    std::cout << "pt1 = " << p1 << "\n";
    std::cout << "pt2 = " << p2 << "\n";
}