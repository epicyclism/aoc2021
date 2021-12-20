#include <iostream>
#include <iterator>
#include <bitset>
#include <string>
#include <algorithm>

struct image
{
    std::string s_;
    size_t stride_;
};

// dots around the edge
void expand(image& i)
{
    std::string ns {};
    ns.append(2 * (i.stride_ + 4), '.');
    size_t  it = 0;
    while( it < i.s_.size())
    {
        ns += "..";
        ns.append(i.s_, it, i.stride_);
        ns += "..";
        it += i.stride_;
    }
    ns.append(2 * (i.stride_ + 4), '.');
    i.s_.swap(ns);
    i.stride_ += 4;
}

void infinite(image& i, std::bitset<512> const& key)
{
    if (key[0]) // toggle the outer two rings
    {
        char w = i.s_[0] == '#' ? '.' : '#';
        i.s_.replace(0, 2 * i.stride_, 2 * i.stride_, w);
        size_t  it = 0;
        while (it < i.s_.size())
        {
            i.s_.replace(it, 2, 2, w);
            i.s_.replace(it + i.stride_ - 2, 2, 2, w);
            it += i.stride_;
        }
        i.s_.replace(i.s_.size() - 2 * i.stride_, 2 * i.stride_, 2 * i.stride_, w);
    }
}

// assume off is a valid place to walk right around...
uint16_t from(image const& i, size_t off)
{
    uint16_t u { 0};
    u |= i.s_[off - i.stride_ - 1] == '#';
    u<<=1;
    u |= i.s_[off - i.stride_]  == '#';
    u<<=1;
    u |= i.s_[off - i.stride_ + 1] == '#';
    u<<=1;
    u |= i.s_[off - 1] == '#';
    u<<=1;
    u |= i.s_[off] == '#';
    u<<=1;
    u |= i.s_[off + 1] == '#';
    u<<=1;
    u |= i.s_[off + i.stride_ - 1] == '#';
    u<<=1;
    u |= i.s_[off + i.stride_] == '#';
    u<<=1;
    u |= i.s_[off + i.stride_ + 1] == '#';
    return u;
}

std::ostream& operator<<(std::ostream& o, image const& i)
{
    auto it = i.s_.begin();
    while( it < i.s_.end())
    {
        std::copy(it, it + i.stride_, std::ostream_iterator<char>(o));
        o << "\n";
        it += i.stride_;
    }
    return o;
}

image step(image i1, std::bitset<512> const& key)
{
    std::cout<< i1 << "\n";
    image i2;
    i2.stride_ = i1.stride_;
    i2.s_.append(i1.s_.size(), '.');
    for(size_t n = 0; n < i2.s_.size(); ++n)
    {
        if( n >= i2.stride_ && n < (i2.s_.size() - i2.stride_))
        {
            auto r = n % i2.stride_;
            if( r && r != i2.stride_ - 1)
            {
                if(key[from(i1, n)])
                    i2.s_[n] = '#';
            }
        }
    }

    return i2;
}

using input = std::pair<std::bitset<512>, image>;

input get_input()
{
    std::bitset<512> bs;
    image im;
    std::string ln;
    std::getline(std::cin, ln);
    std::reverse(ln.begin(), ln.end());
    bs = std::bitset<512> (ln, 0, ln.size(), '.', '#');
    std::getline(std::cin, ln);
    
    while(std::getline(std::cin, ln))
        im.s_ += ln;
    im.stride_ = ln.size();

    return {bs, im};
}

auto pt1(auto& in)
{
    expand(in.second);
    std::cout << "\n" << in.second << "\n";
    auto i2 = step(in.second, in.first);
    infinite(i2, in.first);
    std::cout << i2 << "\n";
    i2 = step(i2, in.first);
    infinite(i2, in.first);
    std::cout << i2 << "\n";
    return std::count(i2.s_.begin(), i2.s_.end(), '#');
}

int main()
{
    auto in { get_input()};
    std::cout << "\n";
    std::cout << "pt1 = " << pt1(in) << "\n";
}

// 5591 too high