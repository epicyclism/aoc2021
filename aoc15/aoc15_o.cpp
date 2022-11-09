#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>

using vertex_id_t = uint32_t;
using weight_t = int;
using edge_t  = struct{ vertex_id_t to_; weight_t wt_;};
using graph_t = std::vector<std::vector<edge_t>>;

template <typename... ARGS> void add_edge(graph_t& g, vertex_id_t from, vertex_id_t to, ARGS... args)
{
    if (g.size() < from + 1)
        g.resize(from + 1);
    g[from].emplace_back(to, args...);
}

void add_edge_undirected(graph_t& g, vertex_id_t from, vertex_id_t to, uint32_t wt)
{
    add_edge(g, from, to, wt);
    add_edge(g, to, from, wt);
}

std::vector<weight_t> dijkstra(graph_t const& g, vertex_id_t from)
{
    std::vector <weight_t> d(g.size(), -1);
    using pq_t = std::pair<vertex_id_t, weight_t>;
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

std::pair<std::vector<char>, size_t> get_input()
{
    std::vector<char> rv;
    std::string ln;
    while(std::getline(std::cin, ln))
        std::transform(ln.begin(), ln.end(), std::back_inserter(rv), [](auto c){ return c - '0';});
    return {rv, ln.size()};
}

graph_t build_graph(std::vector<char> const& data, int stride)
{
    graph_t g;
    for( size_t v = 0; v < data.size(); ++v)
    {
        // left
        if( v % stride != 0)
            add_edge(g, v, v - 1, data[v - 1]);
        // right
        if( v % stride != stride - 1)
            add_edge(g, v, v + 1, data[v + 1]);
        // up
        if( v > stride)
            add_edge(g, v, v - stride, data[v - stride]);
        // down
        if( v < data.size() - stride)
            add_edge(g, v, v + stride, data[v + stride]);
    }
    return g;
}

int pt1(std::vector<char> const& data, int stride)
{
    auto g { build_graph(data, stride)};
    auto d = dijkstra(g, 0);
    return d[g.size() - 1];
}

void print(std::vector<char> const& v, int stride)
{
    auto it = v.begin();
    for( int n = 0; n < v.size() / stride; ++n)
    {
        std::copy(it, it + stride, std::ostream_iterator<int>(std::cout));
        std::cout << "\n";
        it += stride;
    }
}

graph_t build_graph5(std::vector<char> const& data, int stride)
{
    std::vector<char> g5;
    g5.reserve(data.size() * 25);
    for (int iv = 0; iv < 5; ++iv)
    {
        size_t v = 0;
        while (v < data.size())
        {
            auto ih = iv;
            for (int i = 0; i < 5; ++i)
            {
                std::transform(data.begin() + v, data.begin() + v + stride, std::back_inserter(g5), [ih](auto c) { return (c - 1 + ih) % 9 + 1; });
                ++ih;
            }
            v += stride;
        }
    }
    return build_graph(g5, stride * 5);
}


int pt2(std::vector<char> const& data, int stride)
{
    auto g { build_graph5(stride, data)};
    graph_t g( d5.first, d5.second );
    auto d = dijkstra(g, 0);
    return d[g.size() - 1];
}

int main()
{
    auto[ data, stride] = get_input();

    std::cout << "pt1 = " << pt1(data, stride) << "\n";
    std::cout << "pt2 = " << pt2(data, stride) << "\n";
}