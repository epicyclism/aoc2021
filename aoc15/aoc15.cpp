#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>

using vertex_t = int;
using edge_t  = struct{ int wt_; int to_;};
using graph_t = std::vector<std::vector<edge_t>>;

void add_vertex(vertex_t id, graph_t& g)
{
    while( g.size() <= id)
        g.push_back({});
}

void add_edge(vertex_t from, vertex_t to, int weight, graph_t& g)
{
    add_vertex(from, g);
    add_vertex(to, g);
    g[from].push_back({weight, to});
}

std::vector<int> dijkstra(vertex_t from, graph_t const& g)
{
    std::vector <int> d(g.size(), -1);
    using pq_t = std::pair<size_t, int>;
    auto pq_t_cmp = [](auto& l, auto& r){ return l.second > r.second;};
    std::priority_queue<pq_t, std::vector<pq_t>, decltype(pq_t_cmp)> q(pq_t_cmp);
    q.push({from, 0});
    d[from] = 0;
    while (!q.empty())
    {
        auto p = q.top(); q.pop();

        for( auto v : g[p.first])  
        {
            if (d[v.to_] == -1 || d[v.to_] > d[p.first] + v.wt_)
            {
                d[v.to_] = d[p.first] + v.wt_;
                q.push({v.to_, d[v.to_]});
            }
        }
    }

    return d;
}

std::pair<int, std::vector<char>> get_input()
{
    std::vector<char> rv;
    std::string ln;
    while(std::getline(std::cin, ln))
        std::transform(ln.begin(), ln.end(), std::back_inserter(rv), [](auto c){ return c - '0';});
    return {ln.size(), rv};
}

graph_t build_graph(int stride, std::vector<char> const& data)
{
    graph_t g;
    for( size_t v = 0; v < data.size(); ++v)
    {
        // left
        if( v % stride != 0)
            add_edge(v, v - 1, data[v - 1], g);
        // right
        if( v % stride != stride - 1)
            add_edge(v, v + 1, data[v + 1], g);
        // up
        if( v > stride)
            add_edge(v, v - stride, data[v - stride], g);
        // down
        if( v < data.size() - stride)
            add_edge(v, v + stride, data[v + stride], g);
    }
    return g;
}

int pt1(int stride, std::vector<char> const& data)
{
    auto g { build_graph(stride, data)};
    auto d = dijkstra(0, g);
    return d[g.size() - 1];
}

void print(int stride, std::vector<char> const& v)
{
    auto it = v.begin();
    for( int n = 0; n < v.size() / stride; ++n)
    {
        std::copy(it, it + stride, std::ostream_iterator<int>(std::cout));
        std::cout << "\n";
        it += stride;
    }
}

graph_t build_graph5(int stride, std::vector<char> const& data)
{
    std::vector<char> g5;
    g5.reserve(data.size() * 25);
    for( int iv = 0; iv < 5; ++iv)
    {
        size_t v = 0;
        while( v < data.size())
        {
            auto ih = iv;
            for(int i = 0; i < 5; ++i)
            {
                std::transform(data.begin() + v, data.begin() + v + stride, std::back_inserter(g5), [ih](auto c){ return (c - 1 + ih) % 9 + 1;});
                ++ih;
            }
            v += stride;
        }
    }
    return build_graph(stride * 5, g5);
}

int pt2(int stride, std::vector<char> const& data)
{
    auto g { build_graph5(stride, data)};
    auto d = dijkstra(0, g);
    return d[g.size() - 1];
}

int main()
{
    auto[ stride, data] = get_input();

    std::cout << "pt1 = " << pt1(stride, data) << "\n";
    std::cout << "pt2 = " << pt2(stride, data) << "\n";
}