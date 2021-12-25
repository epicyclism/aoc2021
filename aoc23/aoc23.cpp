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

bool is_finished(burrow_t const& b)
{
    return b[11] == 'A' && b[15] == 'A' &&
        b[12] == 'B' && b[16] == 'B' &&
        b[13] == 'C' && b[17] == 'C' &&
        b[14] == 'D' && b[18] == 'D';
}

bool is_finished(burrow2_t const& b)
{
    return  b[11] == 'A' && b[15] == 'A' && b[19] == 'A' && b[23] == 'A' &&
            b[12] == 'B' && b[16] == 'B' && b[20] == 'B' && b[24] == 'B' &&
            b[13] == 'C' && b[17] == 'C' && b[21] == 'C' && b[25] == 'C' &&
            b[14] == 'D' && b[18] == 'D' && b[22] == 'D' && b[26] == 'D' ;
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

int room_from_c(char c)
{
    constexpr std::array top{ 2, 4, 6, 8};
    return top[c - 'A'];
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
    auto record_move_to_top = [&](int f, int t, char ch)
    {
        auto scr {scr_from_from(f)};
        int ft = top_from_room(f);
        if (std::all_of(b.begin() + std::min(ft, t), b.begin() + std::max(ft, t) + 1, [](auto c) { return c == '.'; }))
        {
            scr += std::abs(t - ft);
            scr *= scr_from_type(ch);
            state_t st{ s };
            if(st.first[t] != '.')
            {
                std::cout << "record move to top bug. " << f << " -> " << t << "\n";
                std::cout << st.first << "\n";
            }
            st.first[f] = '.';
            st.first[t] = ch;
            st.second += scr;
            vr.emplace_back(st);
        }
    };
    auto record_move_to_room = [&](int f, int t, char ch)
    {
        auto scr {scr_from_from(t)};
        int tt = top_from_room(t);
        b[f] = '.';
        if (std::all_of(b.begin() + std::min(f, tt), b.begin() + std::max(f, tt) + 1, [](auto c) { return c == '.'; }))
        {
            scr += std::abs(f - tt);
            scr *= scr_from_type(ch);
            state_t st{ s };
            if(st.first[t] != '.')
            {
                std::cout << "record_move_to_room bug. " << f << " -> " << t << "\n";
                std::cout << st.first << "\n";
            }
            st.first[f] = '.';
            st.first[t] = ch;
            st.second += scr;
            vr.emplace_back(st);
        }
        b[f] = ch;
    };
    auto record_move_room_to_room = [&](int f, int t, char ch) -> bool
    {
        auto scr {scr_from_from(f)};
        scr += scr_from_from(t);
        int ff = top_from_room(f);
        int tt = top_from_room(t);
        bool br { false};
        if (std::all_of(b.begin() + std::min(ff, tt), b.begin() + std::max(ff, tt) + 1, [](auto c) { return c == '.'; }))
        {
            scr += std::abs(ff - tt);
            scr *= scr_from_type(ch);
            state_t st{ s };
            if(st.first[t] != '.')
            {
                std::cout << "record_move_room_to_room bug. " << f << " -> " << t << "\n";
                std::cout << st.first << "\n";
            }
            st.first[f] = '.';
            st.first[t] = ch;
            st.second += scr;
            vr.emplace_back(st);
            br = true;
        }
        return br;
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
    auto out_of_col = [&](int f) -> void
    {
        if (b[f] == '.')
            f = f + 4;
        auto t = tgt_from_pod(b[f]);
        bool tt {false};
        if (b[t[1]] == '.')
            tt = record_move_room_to_room(f, t[1], b[f]);
        else
        if (b[t[0]] == '.')
            tt = record_move_room_to_room(f, t[0], b[f]);
        if( !tt)
        {
            for (auto t : toprow)
                record_move_to_top(f, t, b[f]);
        }
    };
    if (b[15] != 'A' && b[15] != '.')
        out_of_col(11);
    if (b[16] != 'B' && b[16] != '.')
        out_of_col(12);
    if (b[17] != 'C' && b[17] != '.')
        out_of_col(13);
    if (b[18] != 'D' && b[18] != '.')
        out_of_col(14);
    if (b[11] != 'A' && b[11] != '.')
        out_of_col(11);
    if (b[12] != 'B' && b[12] != '.')
        out_of_col(12);
    if (b[13] != 'C' && b[13] != '.')
        out_of_col(13);
    if (b[14] != 'D' && b[14] != '.')
        out_of_col(14);
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
    auto record_move_to_top = [&](int f, int t, char ch)
    {
        auto scr {scr_from_from(f)};
        int ft = top_from_room(f);
        if( b[f] != ch)
        {
            std::cout << "record_move_to_top bug, bad from " << f << "\n";
            std::cout << b << "\n";
        }
        if (std::all_of(b.begin() + std::min(ft, t), b.begin() + std::max(ft, t) + 1, [](auto c) { return c == '.'; }))
        {
            scr += std::abs(t - ft);
            scr *= scr_from_type(ch);
            state2_t st{ s };
            if(st.first[t] != '.')
            {
                std::cout << "record move to top bug. " << f << " -> " << t << "\n";
                std::cout << st.first << "\n";
            }
            st.first[f] = '.';
            st.first[t] = ch;
            st.second += scr;
            vr.emplace_back(st);
        }
    };
    auto record_move_to_room = [&](int f, int t, char ch)
    {
        auto scr {scr_from_from(t)};
        int tt = top_from_room(t);
        if( b[f] != ch)
        {
            std::cout << "rrecord_move_to_room bug, bad from " << f << "\n";
            std::cout << b << "\n";
        }
        b[f] = '.';
        if (std::all_of(b.begin() + std::min(f, tt), b.begin() + std::max(f, tt) + 1, [](auto c) { return c == '.'; }))
        {
            scr += std::abs(f - tt);
            scr *= scr_from_type(ch);
            state2_t st{ s };
            if(st.first[t] != '.')
            {
                std::cout << "record move to room bug. " << f << " -> " << t << "\n";
                std::cout << st.first << "\n";
            }
            st.first[f] = '.';
            st.first[t] = ch;
            st.second += scr;
            vr.emplace_back(st);
        }
        b[f] = ch;
    };
    auto record_move_room_to_room = [&](int f, int t, char ch) -> bool
    {
        auto scr {scr_from_from(f)};
        scr += scr_from_from(t);
        int ff = top_from_room(f);
        int tt = top_from_room(t);
        bool br { false};
        if( b[f] != ch)
        {
            std::cout << "record_move_room_to_room bug, bad from " << f << "\n";
            std::cout << b << "\n";
        }
        auto tgts = tgt_from_pod2(b[f]);
        bool proceed {true};
        for(auto c : tgts)
        {
            if( b[c] != ch && b[c] != '.')
                proceed = false;
        }
        if (proceed && std::all_of(b.begin() + std::min(ff, tt), b.begin() + std::max(ff, tt) + 1, [](auto c) { return c == '.'; }))
        {
            scr += std::abs(ff - tt);
            scr *= scr_from_type(ch);
            state2_t st{ s };
            if(st.first[t] != '.')
            {
                std::cout << "record move to room bug. " << f << " -> " << t << "\n";
                std::cout << st.first << "\n";
            }
            st.first[f] = '.';
            st.first[t] = ch;
            st.second += scr;
            vr.emplace_back(st);
            br = true;
        }
        return br;
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
        auto t = tgt_from_pod2(b[f]);
        bool br = false;
        if (b[t[3]] == '.')
            br = record_move_room_to_room(f, t[3], b[f]);
        else
        if (b[t[2]] == '.')
            br = record_move_room_to_room(f, t[2], b[f]);
        else
        if (b[t[1]] == '.')
            br = record_move_room_to_room(f, t[1], b[f]);
        else
        if (b[t[0]] == '.')
            br = record_move_room_to_room(f, t[0], b[f]);
        if (!br)
        {
            for (auto t2 : toprow)
                record_move_to_top(f, t2, b[f]);
        }
    };
    if (b[23] != 'A' && b[23] != '.')
        out_of_col(11, b[23]);
    else if (b[19] != 'A' && b[19] != '.')
        out_of_col(11, b[19]);
    else if (b[15] != 'A' && b[15] != '.')
        out_of_col(11, b[15]);
    else if (b[11] != 'A' && b[11] != '.')
        out_of_col(11, b[11]);
    if (b[24] != 'B' && b[24] != '.')
        out_of_col(12, b[24]);
    else if (b[20] != 'B' && b[20] != '.')
        out_of_col(12, b[20]);
    else if (b[16] != 'B' && b[16] != '.')
        out_of_col(12, b[16]);
    else if (b[12] != 'B' && b[12] != '.')
        out_of_col(12, b[12]);
    if (b[25] != 'C' && b[25] != '.')
        out_of_col(13, b[25]);
    else if (b[21] != 'C' && b[21] != '.')
        out_of_col(13, 'C');
    else if (b[17] != 'C' && b[17] != '.')
        out_of_col(13, b[17]);
    else if (b[13] != 'C' && b[13] != '.')
        out_of_col(13, b[13]);
    if (b[26] != 'D' && b[26] != '.')
        out_of_col(14, b[26]);
    else if (b[22] != 'D' && b[22] != '.')
        out_of_col(14, 'D');
    else if (b[18] != 'D' && b[18] != '.')
        out_of_col(14, b[18]);
    else if (b[14] != 'D' && b[14] != '.')
        out_of_col(14, b[14]);
}

int search_g(auto in)
{
    auto pq_t_cmp = [](auto& l, auto& r){ return l.second > r.second;};
    std::map<decltype(in.first), int> mp;
//    std::map<decltype(in), decltype(in)> mpp;
    std::priority_queue<decltype(in), std::vector<decltype(in)>, decltype(pq_t_cmp)> q(pq_t_cmp);
    q.push(in);
    while( !q.empty())
    {
        auto p = q.top(); q.pop();
        if( mp.contains(p.first) && mp[p.first] < p.second)
            continue;
        if( is_finished(p.first))
        {
#if 0
            auto pd {p};
            while(mpp.contains(pd))
            {
                std::cout << pd.second << "\n" << pd.first << "\n";
                pd = mpp[pd];
            }
#endif
            return p.second;
        }
        std::vector<decltype(in)> vi; 
        generate(p, vi);
        for( auto& s : vi)
        {
            if(!mp.contains(s.first))
            {
                q.push(s);
                mp.insert(s);
//                mpp.insert({ s, p});
            }
            else
            if(mp[s.first] > s.second)
            {
                mp.insert_or_assign(s.first, s.second);
//                mpp.insert_or_assign(s, p);
                q.push(s);
            }
        }
    }
//    std::cout << mpp.size() << "\n";
    return -1;
}

int pt1(burrow_t in)
{
    state_t s{ in, 0};
    return search_g(s);
}

int pt2(burrow2_t in)
{
    state2_t s{ in, 0};
    return search_g(s);
}

int main()
{
    auto in { get_input()};
    std::cout << "pt1 = " << pt1(in) << "\n";
    std::cout << "pt2 = " << pt2(mk_burrow2(in)) << "\n";
}
