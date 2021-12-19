#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
#include <iterator>
#include <optional>
#include <cstdlib>

#include "ctre.hpp"

using pt = std::tuple<int, int, int>;
using beacon = std::vector<int>;

struct scanner
{
    pt origin_;
    bool placed_;
    std::vector<pt> bs_;  // beacon relative positions
    std::vector<beacon> ds_; // for each beacon, sorted array of distances to others in group
};

std::ostream& operator<<(std::ostream& ostr, pt const& p)
{
    ostr << std::get<0>(p) << ", " << std::get<1>(p) << ", " << std::get<2>(p);
    return ostr;
}

template<typename T> T sv_to_t ( std::string_view sv)
{
	T t { 0 };
	std::from_chars(sv.data(), sv.data() + sv.size(), t);
	return t;
}

int distance(pt const& a, pt const& b)
{
    return std::abs(std::get<0>(a) - std::get<0>(b)) + std::abs(std::get<1>(a) - std::get<1>(b)) + std::abs(std::get<2>(a) - std::get<2>(b));
}

std::vector<std::pair<size_t, size_t>> overlap(std::vector<beacon> const& l, std::vector<beacon> const& r)
{
    std::vector<std::pair<size_t, size_t>> rv;
    for(auto i1 = l.begin(); i1 != l.end(); ++i1)
    {
        for(auto i2 = r.begin(); i2 != r.end(); ++i2)
        {
            beacon i;
            std::set_intersection((*i1).begin(), (*i1).end(), (*i2).begin(), (*i2).end(), std::back_inserter(i));
            if( i.size() > 6)
                rv.push_back({std::distance(l.begin(), i1), std::distance(r.begin(), i2)});
        }
    }
    if( rv.size() < 12)
        rv.clear();
    return rv;
}

std::vector<scanner> get_input()
{
    constexpr auto rxsc = ctll::fixed_string{ R"(--- scanner (\d+) ---)" };
    constexpr auto rxbn = ctll::fixed_string{ R"((-?\d+),(-?\d+),(-?\d+))" };

    std::vector<scanner> vs;
    std::string ln;
    while(std::getline(std::cin, ln))
    {
        if( ctre::match<rxsc>(ln))
            vs.push_back({});
        if(auto[m, x, y, z] = ctre::match<rxbn>(ln); m)
            vs.back().bs_.push_back({sv_to_t<int>(x.to_view()), sv_to_t<int>(y.to_view()), sv_to_t<int>(z.to_view())});
    }
    for(auto& s: vs)
    {
        s.placed_ = false;
        for(auto& b1 : s.bs_)
        {
            s.ds_.push_back({});
            for( auto& b2 : s.bs_)
            {
                auto d {distance(b1, b2)};
                if( d != 0)
                    s.ds_.back().push_back(d);
            }
            std::sort(s.ds_.back().begin(), s.ds_.back().end());
        }
    }
    vs[0].placed_ = true;
    return vs;
}

void print(auto const& vv)
{
    for( auto& v : vv)
    {
        for( auto i : v)
            std::cout << i << " ";
        std::cout << "\n";
    }
}

pt txform(int n, pt p)
{
    switch(n)
    {
        case 0:
            return p;
        case 1:
            return {-std::get<0>(p), std::get<1>(p), std::get<2>(p)};
        case 2:
            return {std::get<0>(p), -std::get<1>(p), std::get<2>(p)};
        case 3:
            return {std::get<0>(p), std::get<1>(p), -std::get<2>(p)};
        case 4:
            return {-std::get<0>(p), -std::get<1>(p), std::get<2>(p)};
        case 5:
            return {-std::get<0>(p), std::get<1>(p), -std::get<2>(p)};
        case 6:
            return {std::get<0>(p), -std::get<1>(p), -std::get<2>(p)};
        case 7:
            return {-std::get<0>(p), -std::get<1>(p), -std::get<2>(p)};

        case 8:
            return {std::get<1>(p), std::get<0>(p), std::get<2>(p)};
        case 9:
            return {-std::get<1>(p), std::get<0>(p), std::get<2>(p)};
        case 10:
            return {std::get<1>(p), -std::get<0>(p), std::get<2>(p)};
        case 11:
            return {std::get<1>(p), std::get<0>(p), -std::get<2>(p)};
        case 12:
            return {-std::get<1>(p), -std::get<0>(p), std::get<2>(p)};
        case 13:
            return {-std::get<1>(p), std::get<0>(p), -std::get<2>(p)};
        case 14:
            return {std::get<1>(p), -std::get<0>(p), -std::get<2>(p)};
        case 15:
            return {-std::get<1>(p), -std::get<0>(p), -std::get<2>(p)};

        case 16:
            return {std::get<2>(p), std::get<0>(p), std::get<1>(p)};
        case 17:
            return {-std::get<2>(p), std::get<0>(p), std::get<1>(p)};
        case 18:
            return {std::get<2>(p), -std::get<0>(p), std::get<1>(p)};
        case 19:
            return {std::get<2>(p), std::get<0>(p), -std::get<1>(p)};
        case 20:
            return {-std::get<2>(p), -std::get<0>(p), std::get<1>(p)};
        case 21:
            return {-std::get<2>(p), std::get<0>(p), -std::get<1>(p)};
        case 22:
            return {std::get<2>(p), -std::get<0>(p), -std::get<1>(p)};
        case 23:
            return {-std::get<2>(p), -std::get<0>(p), -std::get<1>(p)};
        
        case 24:
            return {std::get<2>(p), std::get<1>(p), std::get<0>(p)};
        case 25:
            return {-std::get<2>(p), std::get<1>(p), std::get<0>(p)};
        case 26:
            return {std::get<2>(p), -std::get<1>(p), std::get<0>(p)};
        case 27:
            return {std::get<2>(p), std::get<1>(p), -std::get<0>(p)};
        case 28:
            return {-std::get<2>(p), -std::get<1>(p), std::get<0>(p)};
        case 29:
            return {-std::get<2>(p), std::get<1>(p), -std::get<0>(p)};
        case 30:
            return {std::get<2>(p), -std::get<1>(p), -std::get<0>(p)};
        case 31:
            return {-std::get<2>(p), -std::get<1>(p), -std::get<0>(p)};
        
        case 32:
            return {std::get<1>(p), std::get<2>(p), std::get<0>(p)};
        case 33:
            return {-std::get<1>(p), std::get<2>(p), std::get<0>(p)};
        case 34:
            return {std::get<1>(p), -std::get<2>(p), std::get<0>(p)};
        case 35:
            return {std::get<1>(p), std::get<2>(p), -std::get<0>(p)};
        case 36:
            return {-std::get<1>(p), -std::get<2>(p), std::get<0>(p)};
        case 37:
            return {-std::get<1>(p), std::get<2>(p), -std::get<0>(p)};
        case 38:
            return {std::get<1>(p), -std::get<2>(p), -std::get<0>(p)};
        case 39:
            return {-std::get<1>(p), -std::get<2>(p), -std::get<0>(p)};

        case 40:
            return {std::get<0>(p), std::get<2>(p), std::get<1>(p)};
        case 41:
            return {-std::get<0>(p), std::get<2>(p), std::get<1>(p)};
        case 42:
            return {std::get<0>(p), -std::get<2>(p), std::get<1>(p)};
        case 43:
            return {std::get<0>(p), std::get<2>(p), -std::get<1>(p)};
        case 44:
            return {-std::get<0>(p), -std::get<2>(p), std::get<1>(p)};
        case 45:
            return {-std::get<0>(p), std::get<2>(p), -std::get<1>(p)};
        case 46:
            return {std::get<0>(p), -std::get<2>(p), -std::get<1>(p)};
        case 47:
            return {-std::get<0>(p), -std::get<2>(p), -std::get<1>(p)};
    }
    return p;
}

pt diff( pt const& l, pt const& r)
{
    return{std::get<0>(l) - std::get<0>(r), std::get<1>(l) - std::get<1>(r), std::get<2>(l) - std::get<2>(r)};
}

pt plus( pt const& l, pt const& r)
{
    return{std::get<0>(l) + std::get<0>(r), std::get<1>(l) + std::get<1>(r), std::get<2>(l) + std::get<2>(r)};
}

int pt1(std::vector<scanner>& sc)
{
    while( std::any_of(sc.begin(), sc.end(), [](auto s){ return !s.placed_;}))
    {
        for( auto it = sc.begin(); it != sc.end(); ++it)
        {
            for( auto it2 = sc.begin(); it2 != sc.end(); ++it2)
            {
                if ( it != it2 && (*it).placed_ && !(*it2).placed_ )
                {
                    auto ols {overlap((*it).ds_, (*it2).ds_)};
                    if(!ols.empty())
                    {
//                        std::cout << "scanner " << std::distance(sc.begin(), it) << " overlaps with " << std::distance(sc.begin(), it2) << "\n";
                        for( int tx = 0; tx < 48; ++tx)
                        {
                            if( diff((*it).bs_[ols[0].first], txform(tx, (*it2).bs_[ols[0].second])) == 
                                diff((*it).bs_[ols[1].first], txform(tx, (*it2).bs_[ols[1].second])))
                            {
                                (*it2).origin_ = diff((*it).bs_[ols[0].first], txform(tx, (*it2).bs_[ols[0].second]));
                                for(auto& p : (*it2).bs_)
                                    p = plus((*it2).origin_, txform(tx, p));
                                (*it2).placed_ = true;
                            }
                        } 
                    }
                }
            }
        }
    }
#if 0
    for( auto& s : sc)
        std::cout << (s.placed_ ? " p " : "np ") << s.origin_ << "\n";
#endif
    std::vector<pt> beacons;
    for( auto& s : sc)
        for( auto& b : s.bs_)
            beacons.push_back(b);
    std::sort(beacons.begin(), beacons.end());
    beacons.erase(std::unique(beacons.begin(), beacons.end()), beacons.end());
    return beacons.size();
}

int pt2(std::vector<scanner>& sc)
{
    int mx {0};
    for(auto it = sc.begin(); it != sc.end() - 1; ++it)
        for(auto it2 = sc.begin() + 1; it2 != sc.end(); ++it2)
            {
                auto d = distance((*it).origin_, (*it2).origin_);
                if( d > mx)
                    mx = d;
            }
    return mx;
}

int main()
{
    auto br { get_input()};
    std::cout << "pt1 = " << pt1(br) << "\n";
    std::cout << "pt2 = " << pt2(br) << "\n";
}