#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <type_traits>

using burrow_t  = std::array<char, 19>;
using burrow2_t = std::array<char, 27>;

std::ostream& operator<<(std::ostream& o, burrow_t const& b)
{
    o << "#############\n";
    o << "#";
    for(int n = 0; n < 11; ++n)
        o << b[n];
    o << "#\n";
    o << "###";
    o << b[11];
    o << "#";
    o << b[12];
    o << "#";
    o << b[13];
    o << "#";
    o << b[14];
    o << "###\n";
    o << "  #";
    o << b[15];
    o << "#";
    o << b[16];
    o << "#";
    o << b[17];
    o << "#";
    o << b[18];
    o << "#  \n";
    o << "  #########  \n";

    return o;
}

std::ostream& operator<<(std::ostream& o, burrow2_t const& b)
{
    o << "#############\n";
    o << "#";
    for(int n = 0; n < 11; ++n)
        o << b[n];
    o << "#\n";
    o << "###";
    o << b[11];
    o << "#";
    o << b[12];
    o << "#";
    o << b[13];
    o << "#";
    o << b[14];
    o << "###\n";
    o << "  #";
    o << b[15];
    o << "#";
    o << b[16];
    o << "#";
    o << b[17];
    o << "#";
    o << b[18];
    o << "#  \n";
    o << "  #";
    o << b[19];
    o << "#";
    o << b[20];
    o << "#";
    o << b[21];
    o << "#";
    o << b[22];
    o << "#  \n";
    o << "  #";
    o << b[23];
    o << "#";
    o << b[24];
    o << "#";
    o << b[25];
    o << "#";
    o << b[26];
    o << "#  \n";
    o << "  #########  \n";

    return o;
}

burrow_t get_input()
{
    burrow_t b ;
    b.fill('.');
    std::string ln;
    std::getline(std::cin, ln); // top
    std::getline(std::cin, ln); // burrow
    for (int n = 0; n < 11; ++n)
        b[n] = ln[n + 1];
    std::getline(std::cin, ln); // first row
    b[11] = ln[3];
    b[12] = ln[5];
    b[13] = ln[7];
    b[14] = ln[9];
    std::getline(std::cin, ln);
    b[15] = ln[3];
    b[16] = ln[5];
    b[17] = ln[7];
    b[18] = ln[9];
    std::getline(std::cin, ln);
    return b;
}

using state_t  = std::pair<burrow_t, int>;
using state2_t = std::pair<burrow2_t, int>;

bool is_finished(state_t const& s)
{
    auto& b{ s.first };
    return b[11] == 'A' && b[15] == 'A' &&
        b[12] == 'B' && b[16] == 'B' &&
        b[13] == 'C' && b[17] == 'C' &&
        b[14] == 'D' && b[18] == 'D';
}
bool is_finished(state2_t const& s)
{
    auto& b{ s.first };
#if 0
    return  b[11] == 'A' && b[15] == 'A' && b[19] == 'A' && b[23] == 'A' &&
            b[12] == 'B' && b[16] == 'B' && b[20] == 'B' && b[24] == 'B' &&
            b[13] == 'C' && b[17] == 'C' && b[21] == 'C' && b[35] == 'C' &&
            b[14] == 'D' && b[18] == 'D' && b[22] == 'D' && b[26] == 'D' ;
#else
    return b[11] == 'A' && b[15] == 'A' &&
        b[12] == 'B' && b[16] == 'B' &&
        b[13] == 'C' && b[17] == 'C' &&
        b[14] == 'D' && b[18] == 'D';
#endif
}

int scr_from_type(char c)
{
    constexpr int scr[]{ 1, 10, 100, 1000 };
    return scr[c - 'A'];
}

int top_from_room(int r)
{
    constexpr int tp[]{ 2, 4, 6, 8 };
    if(r > 22)
        return tp[r - 23];
    if(r > 18)
        return tp[r-19];
    if (r > 14)
        return tp[r - 15];
    return tp[r - 11];
}

std::array<int, 2> tgt_from_pod(char c)
{
    constexpr std::array<std::array<int, 2>, 4> ts{ 11, 15, 12, 16, 13, 17, 14, 18 };
    return ts[c - 'A'];
}

std::array<int, 4> tgt_from_pod2(char c)
{
    constexpr std::array<std::array<int, 4>, 4> ts{ 11, 15, 19, 23, 12, 16, 20, 24, 13, 17, 21, 25, 14, 18, 22, 26 };
    return ts[c - 'A'];
}

int scr_from_from(int f)
{
    auto scr {1};
    if( f > 14)
        ++scr;
    if(f > 18)
        ++scr;
    if(f > 22)
        ++scr;
    return scr;
}

void generate(state_t& s, std::vector<state_t>& vr)
{
    auto& b{ s.first };
    auto record_move_to_top = [&](int f, int t, char c)
    {
        auto scr {scr_from_from(f)};
        int ft = top_from_room(f);
        if (std::all_of(b.begin() + std::min(ft, t), b.begin() + std::max(ft, t), [](auto c) { return c == '.'; }))
        {
            scr += std::abs(t - ft);
            scr *= scr_from_type(c);
            state_t st{ s };
            st.first[f] = '.';
            st.first[t] = c;
            st.second += scr;
            vr.emplace_back(st);
        }
    };
    auto record_move_to_room = [&](int f, int t, char c)
    {
        auto scr {scr_from_from(t)};
        int tt = top_from_room(t);
        b[f] = '.';
        if (std::all_of(b.begin() + std::min(f, tt), b.begin() + std::max(f, tt), [](auto c) { return c == '.'; }))
        {
            scr += std::abs(f - tt);
            scr *= scr_from_type(c);
            state_t st{ s };
            st.first[t] = c;
            st.second += scr;
            vr.emplace_back(st);
        }
        b[f] = c;
    };
    auto record_move_room_to_room = [&](int f, int t, char c)
    {
        auto scr {scr_from_from(f)};
        scr += scr_from_from(t);
        int ff = top_from_room(f);
        int tt = top_from_room(t);
        if (std::all_of(b.begin() + std::min(ff, tt), b.begin() + std::max(ff, tt), [](auto c) { return c == '.'; }))
        {
            scr += std::abs(ff - tt);
            scr *= scr_from_type(c);
            state_t st{ s };
            st.first[f] = '.';
            st.first[t] = c;
            st.second += scr;
            vr.emplace_back(st);
        }
    };
    for (int n = 0; n < 11; ++n)
    {
        switch (b[n])
        {
        case 'A':
            if (b[15] == '.')
                record_move_to_room(n, 15, 'A');
            else
                if (b[11] == '.' && b[15] == 'A')
                    record_move_to_room(n, 11, 'A');
            break;
        case 'B':
            if (b[16] == '.')
                record_move_to_room(n, 16, 'B');
            else
                if (b[12] == '.' && b[16] == 'B')
                    record_move_to_room(n, 12, 'B');
            break;
        case 'C':
            if (b[17] == '.')
                record_move_to_room(n, 17, 'C');
            else
                if (b[13] == '.' && b[17] == 'C')
                    record_move_to_room(n, 13, 'C');
            break;
        case 'D':
            if (b[18] == '.')
                record_move_to_room(n, 18, 'D');
            else
                if (b[14] == '.' && b[18] == 'D')
                    record_move_to_room(n, 14, 'D');
            break;
        default:
            break;
        }
    }
    // in the burrows, if not right one then can leave
    constexpr std::array toprow{ 0, 1, 3, 5, 7, 9, 10 };
    auto out_of_col = [&](int f, char c) -> void
    {
        if (b[f] == '.')
            f = f + 4;
        if (b[f] == '.')
            f = f + 4;
        if (b[f] == '.')
            f = f + 4;
        for (auto t : toprow)
            record_move_to_top(f, t, b[f]);
        auto t = tgt_from_pod(b[f]);
        if (b[t[1]] == '.')
            record_move_room_to_room(f, t[1], b[f]);
        else
        if (b[t[0]] == '.')
            record_move_room_to_room(f, t[0], b[f]);
    };
    if (b[15] != 'A' && b[15] != '.')
        out_of_col(11, 'A');
    if (b[16] != 'B' && b[16] != '.')
        out_of_col(12, 'B');
    if (b[17] != 'C' && b[17] != '.')
        out_of_col(13, 'C');
    if (b[18] != 'D' && b[18] != '.')
        out_of_col(14, 'D');
    if (b[11] != 'A' && b[11] != '.')
        out_of_col(11, 'A');
    if (b[12] != 'B' && b[12] != '.')
        out_of_col(12, 'B');
    if (b[13] != 'C' && b[13] != '.')
        out_of_col(13, 'C');
    if (b[14] != 'D' && b[14] != '.')
        out_of_col(14, 'D');
 }

burrow2_t mk_burrow2(burrow_t const& b1)
{
    burrow2_t b2;
    std::copy_n(b1.begin(), 15, b2.begin());
    constexpr std::array r1 { 'D','C','B','A'};
    std::copy_n(r1.begin(), 4, b2.begin() + 15);
    constexpr std::array r2 { 'D','B','A','C'};
    std::copy_n(r2.begin(), 4, b2.begin() + 19);
    std::copy_n(b1.begin() + 15, 4, b2.begin() + 23);
    return b2;
}

void generate(state2_t& s, std::vector<state2_t>& vr)
{
    auto& b{ s.first };
    auto record_move_to_top = [&](int f, int t, char c)
    {
        auto scr {scr_from_from(f)};
        int ft = top_from_room(f);
        if (std::all_of(b.begin() + std::min(ft, t), b.begin() + std::max(ft, t), [](auto c) { return c == '.'; }))
        {
            scr += std::abs(t - ft);
            scr *= scr_from_type(c);
            state2_t st{ s };
            st.first[f] = '.';
            st.first[t] = c;
            st.second += scr;
            vr.emplace_back(st);
        }
    };
    auto record_move_to_room = [&](int f, int t, char c)
    {
        auto scr {scr_from_from(t)};
        int tt = top_from_room(t);
        b[f] = '.';
        if (std::all_of(b.begin() + std::min(f, tt), b.begin() + std::max(f, tt), [](auto c) { return c == '.'; }))
        {
            scr += std::abs(f - tt);
            scr *= scr_from_type(c);
            state2_t st{ s };
            st.first[t] = c;
            st.second += scr;
            vr.emplace_back(st);
        }
        b[f] = c;
    };
    auto record_move_room_to_room = [&](int f, int t, char c)
    {
        auto scr {scr_from_from(f)};
        scr += scr_from_from(t);
        int ff = top_from_room(f);
        int tt = top_from_room(t);
        if (std::all_of(b.begin() + std::min(ff, tt), b.begin() + std::max(ff, tt), [](auto c) { return c == '.'; }))
        {
            scr += std::abs(ff - tt);
            scr *= scr_from_type(c);
            state2_t st{ s };
            st.first[f] = '.';
            st.first[t] = c;
            st.second += scr;
            vr.emplace_back(st);
        }
    };
    for (int n = 0; n < 11; ++n)
    {
        switch (b[n])
        {
        case 'A':
            if (b[23] == '.')
                record_move_to_room(n, 23, 'A');
            else
            if (b[19] == '.' && b[23] == 'A')
                record_move_to_room(n, 19, 'A');
            else
            if (b[15] == '.' && b[19] == 'A' && b[23] == 'A')
                record_move_to_room(n, 15, 'A');
            else
            if (b[11] == '.' && b[15] == 'A' && b[19] == 'A' && b[23] == 'A')
                record_move_to_room(n, 11, 'A');
            break;
        case 'B':
            if (b[24] == '.')
                record_move_to_room(n, 24, 'B');
            else
            if (b[20] == '.' && b[24] == 'B')
                record_move_to_room(n, 20, 'B');
            else
            if (b[16] == '.' && b[20] == 'B' && b[24] == 'B')
                record_move_to_room(n, 16, 'B');
            else
            if (b[12] == '.' && b[16] == 'B' && b[20] == 'B' && b[24] == 'B')
                record_move_to_room(n, 12, 'B');
           break;
        case 'C':
            if (b[25] == '.')
                record_move_to_room(n, 25, 'C');
            else
            if (b[21] == '.' && b[25] == 'C')
                record_move_to_room(n, 21, 'C');
            else
            if (b[17] == '.' && b[21] == 'C' && b[25] == 'C')
                record_move_to_room(n, 17, 'C');
            else
            if (b[13] == '.' && b[17] == 'C' && b[21] == 'C' && b[25] == 'C')
                record_move_to_room(n, 13, 'C');
            break;
        case 'D':
            if (b[26] == '.')
                record_move_to_room(n, 26, 'D');
            else
            if (b[22] == '.' && b[26] == 'D')
                record_move_to_room(n, 22, 'D');
            else
            if (b[18] == '.' && b[22] == 'D' && b[26] == 'D')
                record_move_to_room(n, 18, 'D');
            else
            if (b[14] == '.' && b[18] == 'D' && b[22] == 'D' && b[26] == 'D')
                record_move_to_room(n, 14, 'D');
            break;
        default:
            break;
        }
    }
    // in the burrows, if not right one then can leave
    constexpr std::array toprow{ 0, 1, 3, 5, 7, 9, 10 };
    auto out_of_col = [&](int f, char c) -> void
    {
        if (b[f] == '.')
            f = f + 4;
        if (b[f] == '.')
            f = f + 4;
        if (b[f] == '.')
            f = f + 4;
        for (auto t : toprow)
            record_move_to_top(f, t, b[f]);
        auto t = tgt_from_pod2(b[f]);
        if (b[t[3]] == '.')
            record_move_room_to_room(f, t[3], b[f]);
        else
        if (b[t[2]] == '.')
            record_move_room_to_room(f, t[2], b[f]);
        else
        if (b[t[1]] == '.')
            record_move_room_to_room(f, t[1], b[f]);
        else
        if (b[t[0]] == '.')
            record_move_room_to_room(f, t[0], b[f]);
    };
    if (b[23] != 'A' && b[23] != '.')
        out_of_col(11, 'A');
    if (b[24] != 'B' && b[24] != '.')
        out_of_col(12, 'B');
    if (b[25] != 'C' && b[25] != '.')
        out_of_col(13, 'C');
    if (b[26] != 'D' && b[26] != '.')
        out_of_col(14, 'D');
    if (b[19] != 'A' && b[19] != '.')
        out_of_col(11, 'A');
    if (b[20] != 'B' && b[20] != '.')
        out_of_col(12, 'B');
    if (b[21] != 'C' && b[21] != '.')
        out_of_col(13, 'C');
    if (b[22] != 'D' && b[22] != '.')
        out_of_col(14, 'D');
    if (b[15] != 'A' && b[15] != '.')
        out_of_col(11, 'A');
    if (b[16] != 'B' && b[16] != '.')
        out_of_col(12, 'B');
    if (b[17] != 'C' && b[17] != '.')
        out_of_col(13, 'C');
    if (b[18] != 'D' && b[18] != '.')
        out_of_col(14, 'D');
    if (b[11] != 'A' && b[11] != '.')
        out_of_col(11, 'A');
    if (b[12] != 'B' && b[12] != '.')
        out_of_col(12, 'B');
    if (b[13] != 'C' && b[13] != '.')
        out_of_col(13, 'C');
    if (b[14] != 'D' && b[14] != '.')
        out_of_col(14, 'D');

}

int pt1(auto in)
{
    std::vector<state_t> vo;
    int mn{ 1000000000 };
    vo.push_back({ in, 0 });
    std::map<burrow_t, int> mp;
    while (!vo.empty())
    {
        std::vector<state_t> vi;
        for (auto& st : vo)
        {
            if (!mp.contains(st.first))
            {
                generate(st, vi);
                mp.insert(st);
            }
            else
                if (mp[st.first] > st.second)
                {
                    generate(st, vi);
                    mp.insert_or_assign(st.first, st.second);
                }
        }
        for (auto& st : vi)
        {
            if (is_finished(st))
            {
                if (st.second < mn)
                    mn = st.second;
            }
        }
        std::erase_if(vi, [](auto& st2) { return is_finished(st2); });
        vo.swap(vi);
    }
    return mn;
}
#if 0
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
#endif

int search_g(auto in)
{
    auto pq_t_cmp = [](auto& l, auto& r){ return l.second > r.second;};
    std::map<decltype(in.first), int> mp;
    std::priority_queue<decltype(in), std::vector<decltype(in)>, decltype(pq_t_cmp)> q(pq_t_cmp);
    q.push(in);
    int n { 0};
    while( !q.empty())
    {
        auto p = q.top(); q.pop();
        if( mp.contains(p.first) && mp[p.first] < p.second)
            continue;
        if( is_finished(p))
            return p.second;
        std::vector<decltype(in)> vi; 
        generate(p, vi);
#if 0
        std::cout << "<=========================  " << n <<  "  =============================>\n";
        for( auto const& s : vi)
            std::cout << s.first << "\n";
#endif
        for( auto& s : vi)
        {
            if(!mp.contains(s.first))
            {
                q.push(s);
                mp.insert(s);
            }
            else
            if(mp[s.first] > s.second)
            {
                mp.insert_or_assign(s.first, s.second);
                q.push(s);
            }
        }
        ++n;
    }
    return -1;
}

int pt1g(burrow_t in)
{
    std::cout << "\n\n==================== pt1g =======================\n\n";
    std::cout << in << "\n";
    state_t s{ in, 0};
    return search_g(s);
}

int pt2g(burrow2_t in)
{
    std::cout << "\n\n==================== pt2g =======================\n\n";
    std::cout << in << "\n";
    state2_t s{ in, 0};
    return search_g(s);
}

#if 0
int pt2(auto in)
{
    auto s2 { mk_state2({in, 0})};
    std::cout << s2.first << "\n";
    std::vector<state2_t> vo;
    int mn{ 1000000000 };
    vo.push_back(s2);
    std::map<burrow2_t, int> mp;
    int n { 0};
    while (!vo.empty())
    {
        std::vector<state2_t> vi;
        for (auto& st : vo)
        {
            if (!mp.contains(st.first))
            {
                generate2(st, vi);
                mp.insert(st);
            }
            else
                if (mp[st.first] > st.second)
                {
                    generate2(st, vi);
                    mp.insert_or_assign(st.first, st.second);
                }
        }
        for (auto& st : vi)
        {
            if (is_finished(st))
            {
                if (st.second < mn)
                    mn = st.second;
            }
        }
        std::erase_if(vi, [](auto& st2) { return is_finished(st2); });
        vo.swap(vi);
        std::sort(vo.begin(), vo.end(), [](auto const& l, auto const& r){ return l.second < r.second;});
        ++n;
        std::cout << n << "\n";
    }
    return mn;
}
#endif
constexpr burrow2_t b2t { '.','.','.','.','.','.','.','.','.','.','.','B','C','B','D','A','D','C','A','A','B','C','D','A','B','C','D'};
constexpr burrow2_t b2i { '.','.','.','.','.','.','.','.','.','.','.','A','D','B','C','B','C','D','A','A','B','C','D','A','B','C','D'};

int main()
{
    auto in { get_input()};
//    std::cout << "pt1  = " << pt1(in) << "\n";
    std::cout << "pt1g = " << pt1g(in) << "\n";
//    std::cout << "pt2g = " << pt2g(b2i) << "\n";
    std::cout << "pt2g = " << pt2g(mk_burrow2(in)) << "\n";
//    std::cout << "pt2 = " << pt2(in) << "\n";
}

// pt2 44690 too low
// pt2 test 40663