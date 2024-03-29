#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <chrono>

using vertex_id_t = uint32_t;
using weight_t = int;
using edge_t  = struct{ vertex_id_t to_; weight_t wt_;};

class graph_t
{
private:
    const std::vector<char> const& data_;
    const vertex_id_t stride_;
public:
    graph_t(std::vector<char> const& d, size_t s) : data_{ d }, stride_{static_cast<vertex_id_t>( s )}
    {}
    std::vector<edge_t> operator[](vertex_id_t v) const
    {
        std::vector<edge_t> rv;
        // left
        if (v % stride_ != 0)
            rv.emplace_back(v - 1, data_[v - 1]);
        // right
        if (v % stride_ != stride_ - 1)
            rv.emplace_back(v + 1, data_[v + 1]);
        // up
        if (v > stride_)
            rv.emplace_back(v - stride_, data_[v - stride_]);
        // down
        if (v < data_.size() - stride_)
            rv.emplace_back(v + stride_, data_[v + stride_]);
        return rv;
    }
    size_t size() const
    {
        return data_.size();
    }
};

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

int pt1(std::vector<char> const& data, int stride)
{
    graph_t g( data, stride );
    auto d = dijkstra(g, 0);
    return d[g.size() - 1];
}

std::pair<std::vector<char>, size_t>  get_graph5(std::vector<char> const& data, int stride)
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
    return { g5, stride * 5};
}

int pt2(std::vector<char> const& data, int stride)
{
    auto d5 = get_graph5(data, stride);
    graph_t g( d5.first, d5.second );
    auto d = dijkstra(g, 0);
    return d[g.size() - 1];
}

int main()
{
    auto[ data, stride] = get_input();

    auto start = std::chrono::system_clock::now();
    std::cout << "pt1 = " << pt1(data, stride) << "\n";
    std::cout << "pt2 = " << pt2(data, stride) << "\n";
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}