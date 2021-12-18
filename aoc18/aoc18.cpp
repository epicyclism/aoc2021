#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <array>
#include <algorithm>
#include <iterator>

using sfn_t = std::vector<char>;
using v_sfn_t = std::vector<sfn_t>;

constexpr char open{-1};
constexpr char close{-2};
constexpr char blank{-3};

auto convert(std::string_view in)
{
    sfn_t r ;
    std::transform(in.begin(), in.end(), std::back_inserter(r), [](auto c) -> char {if(c == '[') return open; if (c == ']') return close; if( c == ',') return c; return c - '0';});
    std::erase(r, ',');
    return r;
}

std::ostream& operator<< (std::ostream& ostr, sfn_t const& n)
{
    bool bc{ false};
    for(auto c : n)
    {
        switch(c)
        {
        case open:
            ostr << '[';
            bc = false;
            break;
        case close:
            ostr << ']';
            bc = false;
            break;
        case blank:
            ostr << 'x';
            bc = false;
            break;
        default:
            if( bc)
            {
//                ostr << ',' << +c;
                ostr << +c;
                bc = false;
            }
            else
            {
                ostr << +c;
                bc = true;
            }
            break;
        }
    }
    return ostr;
}

sfn_t add(sfn_t l, sfn_t const& r)
{
    l.insert(l.begin(), open);
    l.insert(l.end(), r.begin(), r.end());
    l.push_back(close);
    return l;
}

bool explode(sfn_t& s)
{
    int cnt{0};
    auto it = s.begin();
    while(it != s.end())
    {
        switch(*it)
        {
            case open:
                ++cnt;
                break;
            case close:
                --cnt;
                break;
            default:
                break;
        }
        if( cnt == 5)
        {
            auto l = *(it+1);
            auto r = *(it+2);
            *it = 0;
            std::fill_n(it + 1, 3, blank);
            for(auto itl = it - 1; itl != s.begin(); --itl)
            {
                if(*itl >= 0)
                {
                    *itl += l;
                    break;
                }
            }
            for( auto itr = it + 4; itr != s.end(); ++itr)
            {
                if( *itr >= 0)
                {
                     *itr += r;
                     break;
                }
            }
            std::erase(s, blank);
            return true;
        }
        ++it;
    }
    return false;
}

bool split(sfn_t& s)
{
    auto it = s.begin();
    while(it != s.end())
    {
        if( *it > 9)
        {
            char l = *it / 2;
            char r = (*it + 1) / 2;
            *it = open;
            std::array<char, 3> ins {l, r, close};
            s.insert(it + 1, ins.begin(), ins.end());
            return true;
        }
        ++it;
    }
    return false;
}

void reduce(sfn_t& in)
{
    while(explode(in) || split(in))
        ;
}

int mag(sfn_t const& m)
{
    std::vector<int> v(m.size());
    std::copy(m.begin(), m.end(), v.begin());
    bool op {true};
    while(op)
    {
        op = false;
        auto i = v.begin();
        while((i = std::adjacent_find(i, v.end(), [](auto l, auto r){ return l >= 0 && r >= 0;})) != v.end())
        {
            *(i - 1) = 3 * *i + 2 * *(i + 1); // overwrite the open bracket that must precede the number with the local mag
            std::fill_n(i, 3, blank);         // fill the two numbers and close bracket that must follow.
            i += 3;
            op = true;
        }
        std::erase(v, blank);
    }
    return v.front();
}

auto get_input()
{
    v_sfn_t v;
    std::string ln;
    while(std::getline(std::cin, ln))
        v.emplace_back(convert(ln));
    return v;
}

int pt1(v_sfn_t& vs)
{
    sfn_t sum = vs.front();
    for( auto it = vs.begin() + 1; it != vs.end(); ++it)
    {
        sum = add(sum, *it);
        reduce(sum);
    }
    return mag(sum);
}

int pt2(v_sfn_t& vs)
{
    int mx = 0;
    for( size_t n = 0; n < vs.size() - 1; ++n)
        for( size_t m = n + 1; m < vs.size(); ++m)
        {
            sfn_t sum = add(vs[n], vs[m]);
            reduce(sum);
            auto mg = mag(sum);
            if( mg > mx)
                mx = mg;
            sum = add(vs[m], vs[n]);
            reduce(sum);
            mg = mag(sum);
            if( mg > mx)
                mx = mg;
        }
    return mx;
}

int main()
{
    auto in{get_input()};
    std::cout << "pt1 = " << pt1(in) << "\n";
    std::cout << "pt2 = " << pt2(in) << "\n";
}