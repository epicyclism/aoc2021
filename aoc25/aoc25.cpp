#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>

struct bed_t
{
    std::vector<char> v_;
    int stride_;
};

auto get_input()
{
    bed_t b;
    std::string ln;
    while(std::getline(std::cin, ln))
        b.v_.insert(b.v_.end(), ln.begin(), ln.end());
    b.stride_ = ln.size();
    return b;
}

std::ostream& operator<<(std::ostream& o, bed_t const& b)
{
    auto it = b.v_.begin();
    while( it != b.v_.end())
    {
        std::copy(it, it + b.stride_, std::ostream_iterator<char>(o));
        o << "\n";
        it += b.stride_;
    }
    return o;
}

constexpr char east  { '>' };
constexpr char south { 'v' };
constexpr char space { '.'};

// returns 'p' if cannot move
int next_east(bed_t const& b, int p)
{
    auto t {p};
    if (b.v_[p] == east)
    {
        if( p % b.stride_ == b.stride_ - 1)
            t = t / b.stride_ * b.stride_;
        else
            ++t;
    }
    if ( b.v_[t] == space)
        return t;
    return p;
}

int next_south(bed_t const& b, int p)
{
    auto t {p};
    if(b.v_[p] == south)
    {
        if( t >= b.v_.size() - b.stride_)
            t %= b.stride_;
        else
            t += b.stride_;
    }
    if ( b.v_[t] == space)
        return t;
    return p;
}

int step(bed_t& b)
{
    int cnt {0};
    std::vector<char> bo(b.v_);
    for(int n = 0; n < b.v_.size(); ++n)
    {
        auto nxt = next_east(b, n);
        if( nxt != n)
        {
            bo[nxt]= b.v_[n];
            bo[n] = space;
            ++cnt;
        }
    }
    b.v_.swap(bo);
    std::copy(b.v_.begin(), b.v_.end(), bo.begin());
    for(int n = 0; n < b.v_.size(); ++n)
    {
        auto nxt = next_south(b, n);
        if( nxt != n)
        {
            bo[nxt]= b.v_[n];
            bo[n] = space;
            ++cnt;
        }
    }
    b.v_.swap(bo);

    return cnt;
}

int pt1(auto b)
{
    int steps { 1 };
    while(step(b))
       ++steps;
    return steps;
}

int main()
{
    auto in { get_input()};
    std::cout << "pt1 = " << pt1(in) << "\n";
}