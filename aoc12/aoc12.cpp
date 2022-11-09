#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <chrono>

using vertex_id_t = uint32_t;
using edge_t = std::pair<vertex_id_t, bool>;
using graph_t = std::vector<std::vector<edge_t>>;

bool all_upper(auto s)
{
	return std::all_of(s.begin(), s.end(), [](auto c) { return std::isupper(c); });
}

// vertices : CH FL RY bi end fe hv ks ng pg start yd
vertex_id_t vertex_id_from_name(std::string_view nm)
{
	static std::map<std::string, vertex_id_t> nm_vertex;
    auto v = nm_vertex.try_emplace(std::string{ nm }, static_cast<vertex_id_t>( nm_vertex.size()));
	return (*v.first).second;
}

template <typename... ARGS> void add_edge(graph_t& g, vertex_id_t from, vertex_id_t to, ARGS... args )
{
    if (g.size() < from + 1)
        g.resize(from + 1);
    g[from].emplace_back(to, args...);
}

void add_edge_undirected(graph_t& g, vertex_id_t from, vertex_id_t to, bool reenter_from, bool reenter_to)
{
	add_edge(g, from, to, reenter_to);
	add_edge(g, to, from, reenter_from);
}

graph_t build_graph()
{
	graph_t g;
	std::string ln;
	while (std::getline(std::cin, ln))
	{
		auto sep = ln.find('-');
		std::string_view from{ ln.begin(), ln.begin() + sep };
		std::string_view to{ ln.begin() + sep + 1, ln.end() };
		add_edge_undirected(g, vertex_id_from_name(from), vertex_id_from_name(to), all_upper(from), all_upper(to));
	}
	return g;
}

int pt1(graph_t const& g)
{
    auto src = vertex_id_from_name("start");
    auto dest = vertex_id_from_name("end");
    std::queue<std::vector<vertex_id_t>> q;
    q.push(std::vector<vertex_id_t>{src});
    int cnt{ 0 };
    while (!q.empty())
    {
        auto u = q.front(); q.pop();
        if (u.back() == dest)
            ++cnt;
        else
        {
            for (auto& v : g[u.back()])
            {
                if (v.second || (std::find(u.begin(), u.end(), v.first) == u.end()))
                {
                    auto u2{ u };
                    u2.push_back(v.first);
                    q.push(u2);
                }
            }
        }
    }

    return cnt;
}

int pt2(graph_t const& g)
{
    auto src = vertex_id_from_name("start");
    auto dest = vertex_id_from_name("end");
    std::queue<std::vector<vertex_id_t>> q;
    q.push(std::vector<vertex_id_t>{src});
    int cnt{ 0 };

    while (!q.empty())
    {
        auto u = q.front(); q.pop();
        if (u.back() == dest)
            ++cnt;
        else
        {
            for (auto& v : g[u.back()])
            {
                if (!v.second) // not rentrant
                {
                    if (v.first != src)
                    {
                        auto c = std::count(u.begin(), u.end(), v.first);
                        if (c == 0)
                        {
                            auto u2{ u };
                            u2.push_back(v.first);
                            q.push(u2);
                        }
                        else
                        if (c == 1 && ((u.front() & 0x80000000) == 0))
                        {
                            auto u2{ u };
                            u2.push_back(v.first);
                            u2.front() |= 0x80000000;
                            q.push(u2);
                        }
                    }
                }
                else
                {
                    auto u2{ u };
                    u2.push_back(v.first);
                    q.push(u2);
                }
            }
        }
    }

    return cnt;
}

int main()
{

	auto g = build_graph();
    std::cout << "pt1 = " << pt1(g) << "\n";
	auto start = std::chrono::system_clock::now();
    std::cout << "pt2 = " << pt2(g) << "\n";
	auto end = std::chrono::system_clock::now();


	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
} 