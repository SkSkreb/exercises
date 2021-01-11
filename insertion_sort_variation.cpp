#include <iostream>
#include <algorithm>
#include <vector>
#include <random>


#define MAX_RAND 6000
#define MIN_RAND 0

using namespace std;

template <typename Func_get_begin, typename Func_get_end>
void insertion_sort_variation(Func_get_begin get_begin, Func_get_end get_end)
{
    while (!std::is_sorted(get_begin(), get_end()))
    {
        auto iter = get_begin();
        auto key = *iter;
        while (iter != get_end())
        {
            key = *iter;
            iter = std::partition(get_begin(), std::next(iter),
                                  [&key](const auto& b){
                return b<=key;
                // if the element is less or equal to key, then move it to beginning.
            });
        }
    }
}
template <typename T>
std::vector<T> take_random_vector(int length, T min_rand_value, T max_rand_value)
{
    random_device rnd_device;
    mt19937 mersenne_engine(rnd_device());
    uniform_int_distribution<T> dist(min_rand_value, max_rand_value);
    auto gen = std::bind(dist, mersenne_engine); // returns rundom numbers
    vector<T> a;
    a.resize(length);
    generate(a.begin(), a.end(), gen);
    return a;
}

int main()
{
    constexpr int MIN_RANDOM_NUMBER {MIN_RAND},
    MAX_RANDOM_NUMBER {MAX_RAND},
    VECTOR_LENGTH{150};
    auto a(std::move(
               take_random_vector(
                   VECTOR_LENGTH, MIN_RANDOM_NUMBER, MAX_RANDOM_NUMBER))
           ); // take random vector
    auto b(a); // test_vector for std::sort()
    auto a_end_fptr = [&a]{return a.end();}; //returns ptr to lambda function-member vector::end
    insertion_sort_variation([&a]{return std::begin(a);}, a_end_fptr); // sort
    std::sort(b.begin(),b.end()); //sorted vector
    if(a!=b) throw 56; // test vector compare. 56 -- is a number of this line
    constexpr int COLUMNS{7}; //print like list of n COLUMNS; n = 7
    unsigned int counter{0};
    for(auto element: a)
    {
        cout<< element<< [&counter]{return counter%COLUMNS==0?'\n':'\t';}();
        ++counter;
    }

    return 0;
}
