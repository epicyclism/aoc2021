#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <map>

using burrow_t = std::array<char, 19>;

constexpr std::array<std::array<int, 3>, 19> can_move{
    1, -1 ,-1,  // 0
    0, 2, -1,   // 1
    1, 3, 11,   // 2
    2, 4, -1,   // 3
    3, 4, 12,   // 4
    4, 6, -1,   // 5
    5, 7, 13,   // 6
    6, 8, -1,   // 7
    7, 9, 14,   // 8
    8, 10, -1,  // 9
    9, -1, -1,  //10
    2, 15, -1,  //11
    4, 16, -1,  //12
    6, 17, -1,  //13
    8, 18, -1,  //14
    11, -1, -1, //15
    12, -1, -1, //16
    13, -1, -1, //17
    14, -1, -1, //18 
};

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

using state_t = std::pair<burrow_t, int>;

bool is_finished(state_t const& s)
{
    auto& b{ s.first };
    return b[11] == 'A' && b[15] == 'A' &&
        b[12] == 'B' && b[16] == 'B' &&
        b[13] == 'C' && b[17] == 'C' &&
        b[14] == 'D' && b[18] == 'D';
}

int scr_from_type(char c)
{
    constexpr int scr[]{ 1, 10, 100, 1000 };
    return scr[c - 'A'];
}

int top_from_room(int r)
{
    constexpr int tp[]{ 2, 4, 6, 8 };
    if (r > 14)
        return tp[r - 15];
    return tp[r - 11];
}

std::array<int, 2> tgt_from_pod(char c)
{
    constexpr std::array<std::array<int, 2>, 4> ts{ 11, 15, 12, 16, 13, 17, 13, 18 };
    return ts[c - 'A'];
}

void generate(state_t& s, std::vector<state_t>& vr)
{
    auto& b{ s.first };
    auto record_move_to_top = [&](int f, int t, char c)
    {
        auto scr = 1;
        if (f > 14)
            ++scr;
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
        auto scr = 1;
        if (t > 14)
            ++scr;
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
        auto scr = 2;
        if (f > 14)
            ++scr;
        if (t > 14)
            ++scr;
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
    if (b[15] != 'A' && b[15] != '.')
    {
        auto f = 11;
        if (b[11] == '.')
            f = 15;
        for (auto t : toprow)
            record_move_to_top(f, t, b[f]);
        auto t = tgt_from_pod(b[f]);
        if (b[t[1]] == '.')
            record_move_room_to_room(f, t[1], b[f]);
        else
            if (b[t[0]] == '.')
                record_move_room_to_room(f, t[0], b[f]);
    }
    if (b[16] != 'B' && b[16] != '.')
    {
        auto f = 12;
        if (b[12] == '.')
            f = 16;
        for (auto t : toprow)
            record_move_to_top(f, t, b[f]);
        auto t = tgt_from_pod(b[f]);
        if (b[t[1]] == '.')
            record_move_room_to_room(f, t[1], b[f]);
        else
            if (b[t[0]] == '.')
                record_move_room_to_room(f, t[0], b[f]);
    }
    if (b[17] != 'C' && b[17] != '.')
    {
        auto f = 13;
        if (b[13] == '.')
            f = 17;
        for (auto t : toprow)
            record_move_to_top(f, t, b[f]);
        auto t = tgt_from_pod(b[f]);
        if (b[t[1]] == '.')
            record_move_room_to_room(f, t[1], b[f]);
        else
            if (b[t[0]] == '.')
                record_move_room_to_room(f, t[0], b[f]);
    }
    if (b[18] != 'D' && b[18] != '.')
    {
        auto f = 14;
        if (b[14] == '.')
            f = 18;
        for (auto t : toprow)
            record_move_to_top(f, t, b[f]);
        auto t = tgt_from_pod(b[f]);
        if (b[t[1]] == '.')
            record_move_room_to_room(f, t[1], b[f]);
        else
            if (b[t[0]] == '.')
                record_move_room_to_room(f, t[0], b[f]);
    }
    if (b[11] != 'A' && b[11] != '.')
    {
        for (auto t : toprow)
            record_move_to_top(11, t, b[11]);
        if (b[11] != '.')
        {
            auto t = tgt_from_pod(b[11]);
            if (b[t[1]] == '.')
                record_move_room_to_room(11, t[1], b[11]);
            else
                if (b[t[0]] == '.')
                    record_move_room_to_room(11, t[0], b[11]);
        }
    }
    if (b[12] != 'B' && b[12] != '.')
    {
        for (auto t : toprow)
            record_move_to_top(12, t, b[12]);
        if (b[12] != '.')
        {
            auto t = tgt_from_pod(b[12]);
            if (b[t[1]] == '.')
                record_move_room_to_room(12, t[1], b[12]);
            else
                if (b[t[0]] == '.')
                    record_move_room_to_room(12, t[0], b[12]);
        }
    }
    if (b[13] != 'C' && b[13] != '.')
    {
        for (auto t : toprow)
            record_move_to_top(13, t, b[13]);
        if (b[13] != '.')
        {
            auto t = tgt_from_pod(b[13]);
            if (b[t[1]] == '.')
                record_move_room_to_room(13, t[1], b[13]);
            else
                if (b[t[0]] == '.')
                    record_move_room_to_room(13, t[0], b[13]);
        }
    }
    if (b[14] != 'D' && b[14] != '.')
    {
        for (auto t : toprow)
            record_move_to_top(14, t, b[14]);
        if (b[14] != '.')
        {
            auto t = tgt_from_pod(b[14]);
            if (b[t[1]] == '.')
                record_move_room_to_room(14, t[1], b[14]);
            else
                if (b[t[0]] == '.')
                    record_move_room_to_room(14, t[0], b[14]);
        }
    }
}

int pt1(auto in)
{
    std::cout << in << "\n";
    std::vector<state_t> vo;
    int mn{ 1000000000 };
    vo.push_back({ in, 0 });
    std::map<burrow_t, int> mp;
    int n = 0;
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
#if 0
        if (vi.empty())
        {
            std::cout << n << " --------------\n";
            for (auto& st : vo)
            {
                std::cout << st.second << "\n";
                std::cout << st.first << "\n";
            }
        }
#endif
        vo.swap(vi);
        ++n;
    }
    return mn;
}

int main()
{
    auto in { get_input()};
    std::cout << "pt1 = " << pt1(in) << "\n";
}