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
int next(bed_t const& b, int p)
{
    auto t {p};
    if (b.v_[p] == east)
    {
        if( p % b.stride_ == b.stride_ - 1)
            t = t / b.stride_ * b.stride_;
        else
            ++t;
        std::cout << "east " << p << " to " << t << "\n";
    }
    else
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
    std::vector<char> bo ( b.v_.size(), 'x');
    for(int n = 0; n < b.v_.size(); ++n)
    {
        auto nxt = next(b, n);
        if( nxt != n)
        {
            std::cout << n << " (" << b.v_[n] << ") -> " << nxt << "\n";
            ++cnt;
            bo[nxt] = b.v_[n];
        }
        else
            bo[n] = b.v_[n];       
    }
    b.v_.swap(bo);
    return cnt;
}

int pt(auto b)
{
    int steps { 1 };
    while(step(b))
    {
        std::cout << b << "\n";
        ++steps;
    }
    return steps;
}

int main()
{
    auto in { get_input()};
    std::cout << "stride = " << in.stride_ << "\n";
    std::cout << in << "\n";
    std::cout << "pt = " << pt(in) << "\n";
}