#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>

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
        b[12] == 'B' && b[15] == 'B' &&
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

void generate(state_t const& s, std::vector<state_t>& vr)
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
            if (std::all_of(b.begin() + std::min(f, tt), b.begin() + std::max(f, tt), [](auto c) { return c == '.'; }))
            {
                scr += std::abs(f - tt);
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
                        record_move_to_room(n, 13, 'D');
                break;
            default:
                break;
            }
        }
        // in the burrows, if not right one then can leave
        constexpr std::array toprow{ 0, 1, 3, 5, 7, 9, 10 };
        if (b[15] != 'A' && b[11] == '.')
        {
            for (auto t : toprow)
                record_move_to_top(15, t, b[15]);
        }
        if (b[16] != 'B' && b[12] == '.')
        {
            for (auto t : toprow)
                record_move_to_top(16, t, b[16]);
        }
        if (b[17] != 'C' && b[13] == '.')
        {
            for (auto t : toprow)
                record_move_to_top(17, t, b[17]);
        }
        if (b[18] != 'D' && b[14] == '.')
        {
            for (auto t : toprow)
                record_move_to_top(18, t, b[18]);
        }
        if (b[11] != 'A' || (b[15] != 'A' && b[11] != '.'))
        {
            for (auto t : toprow)
                record_move_to_top(11, t, b[11]);
        }
        if (b[12] != 'B' || (b[16] != 'B' && b[12] != '.'))
        {
            for (auto t : toprow)
                record_move_to_top(12, t, b[12]);
        }
        if (b[13] != 'C' || (b[17] != 'C' && b[13] != '.'))
        {
            for (auto t : toprow)
                record_move_to_top(13, t, b[13]);
        }
        if (b[14] != 'D' || (b[18] != 'D' && b[14] != '.'))
        {
            for (auto t : toprow)
                record_move_to_top(14, t, b[14]);
        }
}

int pt1(auto in)
{
    std::cout << in << "\n";
    std::vector<state_t> vo;
    int mx{ 0 };
    vo.push_back({ in, 0 });
    while (!vo.empty())
    {
        std::vector<state_t> vi;
        for (auto& st : vo)
            generate(st, vi);
        for (auto& st : vi)
        {
            if (is_finished(st) && st.second > mx)
                mx = st.second;
        }
        std::erase_if(vi, [](auto& st2) { return is_finished(st2); });
        vo.swap(vi);
    }
#if 0
    for (auto& st : vo)
    {
        std::cout << st.second << "\n";
        std::cout << st.first << "\n";
    }
#endif
    return mx;
}

int main()
{
    auto in { get_input()};
    std::cout << "pt1 = " << pt1(in) << "\n";
}