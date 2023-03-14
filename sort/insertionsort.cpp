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
bool insertion_sort(std::vector<T> &arr, bool (*t)(const T &, const T &))
{
    if (arr.size() == 0)
    {
        return false;
    }

    for (int i = 1; i < (int)arr.size(); i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (t(arr[j], arr[j - 1]))
            {
                T temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            }
        }
    }
    return true;
}

int main()
{
    std::vector<double> arr{3.2005, 4.49494, 6.5699, 3.111, 2.222, 0.5, 100, 99, 886, 1, 3.2};
    insertion_sort(arr, greater<double>);
    for (int i = 0; i < arr.size(); i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    insertion_sort(arr, less<double>);
    for (int i = 0; i < arr.size(); i++)
    {
        std::cout << arr[i] << " ";
    }

    return 0;
}