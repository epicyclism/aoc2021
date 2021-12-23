#include <iostream>
#include <string>
#include <array>

using burrow_t = std::array<char, 19>;

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

int main()
{
    auto in { get_input()};
    std::cout << in << "\n";
}