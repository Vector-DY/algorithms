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
bool selection_sort(std::vector<T> &arr, bool (*t)(const T &, const T &))
{
    if (arr.size() == 0)
    {
        return false;
    }
    for (int i = 0; i < arr.size(); i++)
    {
        int min = i;
        for (int j = i + 1; j < arr.size(); j++)
        {
            if (t(arr[min], arr[j]))
            {
                min = j;
            }
        }
        if (min != i)
        {
            T temp = arr[min];
            arr[min] = arr[i];
            arr[i] = temp;
        }
    }
    return true;
}

int main()
{
    std::vector<double> arr{3.2005, 4.49494, 6.5699, 3.111, 2.222, 0.5, 100, 99, 886, 1, 3.2};
    selection_sort(arr, greater<double>);
    for (int i = 0; i < arr.size(); i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    selection_sort(arr, less<double>);
    for (int i = 0; i < arr.size(); i++)
    {
        std::cout << arr[i] << " ";
    }
}