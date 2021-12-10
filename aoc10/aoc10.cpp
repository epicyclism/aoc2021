#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stack>

auto get_input()
{
    std::vector<std::string> v;
    std::string ln;
    while(std::getline(std::cin, ln))
        v.emplace_back(std::move(ln));
    return v;
}

bool open(char c)
{
    switch(c)
    {
        case '(':
        case '{':
        case '<':
        case '[':
            return true;
    }
    return false;
}

char match(char c)
{
    switch(c)
    {
        case ')':
            return '(';
        case  '}':
            return '{';
        case '>':
            return '<';
        case ']':
            return '[';
    }
    return 0;
}

int value(char c)
{
    switch(c)
    {
        case ')':
            return 3;
        case ']':
            return 57;
        case '}':
            return 1197;
        case '>':
            return 25137;
    }
    return 0;
}

int score(std::string_view ln)
{
    std::stack<char> st;
    for(auto c : ln)
    {
        if( open(c))
            st.push(c);
        else
        if( match(c) == st.top())
            st.pop();
        else
            return value(c);
    }
    return 0;
}

int value2(char c)
{
    switch(c)
    {
        case '(':
            return 1;
        case '[':
            return 2;
        case '{':
            return 3;
        case '<':
            return 4;
    }
    return 0;
}

int64_t completion(std::string_view ln)
{
    std::stack<char> st;
    for(auto c : ln)
    {
        if( open(c))
            st.push(c);
        else
        if( match(c) == st.top())
            st.pop();
        else
            return 0; // syntax error
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