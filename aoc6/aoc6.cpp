#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <sstream>
#include <algorithm>

std::vector<int> get_input()
{
    std::string ln;
    std::getline(std::cin, ln);
    std::transform(ln.begin(), ln.end(), ln.begin(), [](auto c){ return c == ',' ? ' ' : c;});
    std::stringstream istr (ln);
    std::vector<int> v;
    std::copy(std::istream_iterator<int>(istr), std::istream_iterator<int>(), std::back_inserter(v));
    return v;
}

int64_t simulate_a_fish(int ndays)
{
    std::vector<int> vf{3,4,3,1,2};
    std::vector<int> vt;
//    vf.push_back(8);
    while(ndays)
    {
        for(auto i : vf)
        {
            if( i == 0)
            {
                vt.push_back(6);
                vt.push_back(8);
            }
            else
                vt.push_back(i - 1);
        }
        vf.swap(vt);
        std::cout << vf.size() << "\n";
        --ndays;
    }
    return vf.size();
}

int main()
{
    auto v = get_input();
    std::cout << "got " << v.size() << " fish.\n";
    std::cout << "after 18 " << simulate_a_fish(18) << "\n";
}