#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <queue>
#include <map>
#include <cstdint>
#include <algorithm>

#include "ctre_inc.h"

struct graph_t
{
    std::vector<std::vector<int>> al_;

    int nlc_ = 0;
    int nuc_ = 0;
    std::map<std::string, uint32_t> v_;

    bool all_lower(auto s)
    {
        return std::all_of(s.begin(), s.end(), [](auto c){ return std::islower(c);});
    }
    
    uint32_t s_to_c(std::string const& s) const
    {
        if( v_.contains(s))
            return v_.at(s);
        return -1;
    }
    std::string c_to_s(uint32_t c) const
    {
        for( auto p : v_)
        {
            if( p.second == (c & 0x7fffffff))
                return p.first;
        }
        return "x";
    }
    uint32_t s_to_c(std::string s)
    {
        if( v_.contains(s))
            return v_.at(s);
        if( all_lower(s))
        {
            ++nlc_;
            v_.emplace(std::make_pair(s, nlc_));
            return nlc_;
        }
        else
        {
            ++nuc_;
            v_.emplace(std::make_pair(s, 32 * nuc_));
            return 32 * nuc_;
        }
    }

    void add_edge(std::string from, std::string to)
    {
        auto f = s_to_c(from);
        auto t = s_to_c(to);
        if ( al_.size() < f)
            al_.resize(f + 1);
        if ( al_.size() < t)
            al_.resize(t + 1);
        al_[f].push_back(t);
        al_[t].push_back(f);
    }
};

graph_t get_input()
{
    constexpr auto rx = ctll::fixed_string{ R"(([a-zA-Z]+)-([a-zA-Z]+))" };
    std::string ln;
    graph_t g;
    while(std::getline(std::cin, ln))
    {
        if(auto[m, f, t] = ctre::match<rx>(ln); m)
            g.add_edge(f.to_string(), t.to_string());
    }
    return g;
}

int pt1(graph_t const& g)
{
    auto src = g.s_to_c("start");
    auto dest = g.s_to_c("end");
    std::queue<std::vector<uint32_t>> q ; // first entry is this vertex, subsequent are vertices seen on this path
    q.push(std::vector<uint32_t>{src});
    int cnt { 0 };

    while( !q.empty())
    {
        auto u = q.front(); q.pop();
        if(u.back() == dest)
        {
#if 0
            for( auto v : u)
                std::cout << g.c_to_s(v) << " ";
            std::cout << "\n";
#endif
            ++cnt;
        }
        else
        {
            for(auto& v : g.al_[u.back()])
            {
                if( v >= 32 || (std::find(u.begin(), u.end(), v) == u.end()))
                {
                    auto u2 { u };
                    u2.push_back(v); 
                    q.push(u2);
                }
            }
        }
    }

    return cnt;
}

int pt2(graph_t const& g)
{
    auto src = g.s_to_c("start");
    auto dest = g.s_to_c("end");
    std::queue<std::vector<uint32_t>> q ; // first entry is this vertex, subsequent are vertices seen on this path
    q.push(std::vector<uint32_t>{src});
    int cnt { 0 };

    while( !q.empty())
    {
        auto u = q.front(); q.pop();
        if(u.back() == dest)
            ++cnt;
        else
        {
            for(auto& v : g.al_[u.back()])
            {
                if (v < 32)
                {
                    if ( v != src)
                    {
                        auto c = std::count(u.begin(), u.end(), v) ;
                        if ( c == 0)
                        {
                            auto u2 { u };
                            u2.push_back(v);
                            q.push(u2);
                        }
                        else
                        if ( c == 1 && ((u.front() & 0x80000000) == 0))
                        {
                            auto u2 { u };
                            u2.push_back(v); 
                            u2.front () |= 0x80000000;
                            q.push(u2);
                        }
                    }
                }
                else
                {
                    auto u2 { u };
                    u2.push_back(v); 
                    q.push(u2);
                }
            }
        }
    }

    return cnt;
}

int main()
{
    auto g = get_input();
#if 0
    for(auto& v : g.v_)
        std::cout << v.first << " " << v.second << "\n";
#endif
    std::cout << "pt1 = " << pt1(g) << "\n";
    std::cout << "pt2 = " << pt2(g) << "\n";
}