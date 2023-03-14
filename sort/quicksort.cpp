#include <iostream>
#include <vector>

template <class T>
bool greater(const T &x, const T &y)
{
    return x > y;
}

template <class T>
bool less(const T &x, const T &y)
{
    return x < y;
}

template <class T>
void quick_sort(std::vector<T> arr, typename std::vector<T>::iterator left, typename std::vector<T>::iterator right, bool (*t)(const T &, const T &))
{
    if (arr.size() == 0)
    {
        return;
    }
}