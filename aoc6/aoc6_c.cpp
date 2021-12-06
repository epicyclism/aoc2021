    #include <iostream>
    #include <algorithm>
    #include <numeric>
    #include <array>

    constexpr std::array input{
    #include "input.txt"
    };

    constexpr std::array test{ 3, 4, 3, 1, 2 };

    template<typename A> constexpr int64_t simulate_fish(A const& a, int gen)
    {
        std::array<int64_t, 9> cnts{ 0 };
        for (auto i : a)
            ++cnts[i];
        for (int g = 0; g < gen; ++g)
        {
            std::rotate(cnts.begin(), cnts.begin() + 1, cnts.end());
            cnts[6] += cnts[8];
        }
        return std::accumulate(cnts.begin(), cnts.end(), 0i64);
    }

    int main()
    {
        constexpr auto e80{ simulate_fish(test, 80) };
        constexpr auto e256{ simulate_fish(test, 256) };
        constexpr auto i80{ simulate_fish(input, 80) };
        constexpr auto i256{ simulate_fish(input, 256) };

        std::cout << "example after 80 days  " << e80 << "\n";
        std::cout << "pt1 after 80 days      " << e256 << "\n";
        std::cout << "example after 256 days " << i80 << "\n";
        std::cout << "pt2 after 256 days     " << i256 << "\n";
    }