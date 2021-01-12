#include <iostream>
#include <algorithm>
#include <random>
#include <functional>
#include <cassert>
#include <vector>

using namespace std;

template <typename Forward_iterator>
void selection_sort(Forward_iterator begin, Forward_iterator end)
{
    for(auto iter(begin);iter!=end;++iter)
    {
        std::swap(*std::min_element(iter,end), *iter);
    }
}
template <typename T>
std::vector<T> take_random_vector(unsigned int length, T min_rand_value, T max_rand_value)
{
    random_device rnd_device;
    mt19937 mersenne_engine(rnd_device());
    uniform_int_distribution<T> dist(min_rand_value, max_rand_value);
    auto gen = std::bind(dist, mersenne_engine); // returns random numbers
    vector<T> a;
    a.resize(length);
    generate(a.begin(), a.end(), gen);
    return a;
}
template <typename Sort_func, typename T = int>
bool sort_tester(Sort_func sortf,
                 T min_random_value = 0,T max_random_value = 5000, unsigned int length = 150)
{
    auto a(std::move(
               take_random_vector<T>(
                   min_random_value, max_random_value, length))
           ); // take random vector
    auto b(a);
    sortf(a.begin(), a.end()); // testing sort
    std::sort(b.begin(),b.end()); // standart sort
    assert(a==b);
    return true;
}

int main()
{
    typedef vector<int>::iterator iter ;
    cout<< (sort_tester(selection_sort<iter>)?"true\n":"unreachable\n");
    return 0;
}

