#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stack>
#include <array>

using namespace std::string_literals;

auto get_input()
{
    std::vector<std::string> v;
    std::string ln;
    while(std::getline(std::cin, ln))
        v.push_back(ln);
    return v;
}

struct ocvv
{
    char o_;
    char c_;
    int v1_;
    int v2_;
};

constexpr ocvv ocvvs [] = {{'(', ')', 3, 1}, {'[', ']', 57, 2}, {'{', '}', 1197, 3}, {'<', '>', 25137, 4}};

bool open(char c)
{
    return std::find_if(std::begin(ocvvs), std::end(ocvvs), [&](auto& v) { return v.o_ == c; }) != std::end(ocvvs);
}

bool match(char o, char c)
{
    return std::find_if(std::begin(ocvvs), std::end(ocvvs), [&](auto& v ) { return v.o_ == o; })->c_ == c;
}

int value(char c)
{
    return std::find_if(std::begin(ocvvs), std::end(ocvvs), [&](auto& v) { return v.c_ == c; })->v1_;
}

int score(std::string_view ln)
{
    std::stack<char> st;
    for(auto c : ln)
    {
        if( open(c))
            st.push(c);
        else
        if( match(st.top(), c))
            st.pop();
        else
            return value(c);
    }
    return 0;
}

int value2(char c)
{
    return std::find_if(std::begin(ocvvs), std::end(ocvvs), [&](auto& v) { return v.o_ == c; })->v2_;
}

int64_t completion(std::string_view ln)
{
    std::stack<char> st;
    for(auto c : ln)
    {
        if( open(c))
            st.push(c);
        else
        if( match(st.top(), c))
            st.pop();
        else
            return 0; // syntax error, ok
    }
    int64_t scr { 0};
    while( !st.empty())
    {
        scr *= 5;
        scr += value2(st.top());
        st.pop();
    }
    return scr;
}

int pt1(auto& v)
{
    return std::accumulate(v.begin(), v.end(), 0, [](auto e, auto s){ return e + score(s);});
}

int pt2(auto& v)
{
    std::vector<int64_t> r;
    for(auto& ln : v)
    {
        auto cs = completion(ln);
        if(cs)
            r.push_back(cs);
    }
    std::sort(r.begin(), r.end());
    return r[r.size() / 2];
}

int main()
{
    auto v { get_input()};
    std::cout << "pt1 = " << pt1(v) << "\n";
    std::cout << "pt2 = " << pt2(v) << "\n";
}