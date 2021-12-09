#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <array>
#include <algorithm>
#include <numeric>
#include <queue>

std::pair<std::vector<char>, int> get_input()
{
    std::vector<char> v;
    std::string ln;
    while(getline(std::cin, ln))
    {
        std::copy(ln.begin(), ln.end(), std::back_inserter(v));
    }

    return {v, int(ln.size())};
}

std::vector<int> find_low_points(std::vector<char> const& v, int s)
{
    std::vector<int> vr;
    auto can_see_set = [&](auto i) -> std::array<int, 4>
    {
        std::array<int, 4> css { i - 1, i + 1, i - s, i + s};
        if( i % s == 0)
            css[0] = -1;
        if(i % s == s - 1)
            css[1] = -1;
        if( i < s)
            css[2] = -1;
        if(i >= v.size() - s)
            css[3] = -1;
        return css;
    };
    for(auto ind = 0; ind < v.size(); ++ind)
    {
        auto cur = v[ind];
        auto css = can_see_set(ind);
        bool inc = true;
        for(auto off : css)
        {
            if( off >= 0 && cur >= v[off])
                inc = false;
        }
        if(inc)
            vr.push_back(ind);
    }
    return vr;
}

int pt1(std::vector<char> const& v, int s)
{
    auto lp = find_low_points(v, s);
    int cnt {0};
    for( auto p : lp)
        cnt += v[p] + 1 - '0';
    return cnt;
}

std::vector<bool> bfs(int id_from, std::vector<char>& g, int s)
{
    auto can_see_set = [&](auto i) -> std::array<int, 4>
    {
        std::array<int, 4> css { i - 1, i + 1, i - s, i + s};
        if( i % s == 0)
            css[0] = -1;
        if(i % s == s - 1)
            css[1] = -1;
        if( i < s)
            css[2] = -1;
        if(i >= g.size() - s)
            css[3] = -1;
        return css;
    };
    std::vector<bool>   visited(g.size());
    std::queue<int> q;
    q.push(id_from);
    g[id_from] = 'X';
    while( !q.empty())
    {
        auto u = q.front(); q.pop();
        visited[u] = true;
        g[u] = '_';
        for(auto v : can_see_set(u))
        {
            if( v >= 0 && g[v] != '9' && !visited[v])
                q.push(v);
        }
    }
    return visited;
}

int pt2(std::vector<char> v, int s)
{
    auto lp = find_low_points(v, s);
    std::vector<int> basin_sizes;
    for( auto p : lp)
    {
        auto rs = bfs(p, v, s);
        basin_sizes.push_back( std::count(rs.begin(), rs.end(), true));
    }
    std::sort(basin_sizes.begin(), basin_sizes.end(), std::greater<>());
    return std::accumulate(basin_sizes.begin(), basin_sizes.begin() + 3, 1, std::multiplies<>());
}

int main()
{
    auto[v, s] = get_input();
    std::cout << "pt1 = " << pt1(v, s) << "\n";
    std::cout << "pt2 = " << pt2(v, s) << "\n";
}