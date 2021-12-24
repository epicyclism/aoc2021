#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <string_view>

#include "ctre_inc.h"

using regs = std::array<int64_t, 4>;

enum class reg    { w, x, y, z, i};
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
    opcode  op_;
    reg     a_;
    reg     b_;
    int64_t i_;
};

using program = std::vector<inst> ;

auto get_input()
{
    program p;
    constexpr auto rx = ctll::fixed_string{ R"((inp|add|mul|div|mod|eql) (w|x|y|z) ?(w|x|y|z|-?\d+)?)" };
    std::string ln;
    while(std::getline(std::cin, ln))
    {
        if(auto[m, op, src, des] = ctre::match<rx>(ln); m)
        {
            p.push_back({op_f_sv(op.to_view()), reg_f_sv(src.to_view()), reg_f_sv(des.to_view()), 0});
            if( p.back().b_ == reg::i)
                p.back().i_ = sv_to_t<int64_t>(des.to_view());
        }
        else
            std::cout << "parse fail at : " << ln << "\n";
    }
    return p;
}

int main()
{
    auto in { get_input()};
}