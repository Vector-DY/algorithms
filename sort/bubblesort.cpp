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
bool bubble_sort(std::vector<T> &arr, bool (*t)(const T &, const T &))
{
    if (arr.size() == 0)
    {
        return false;
    }
    for (int i = 0; i < (int)arr.size(); i++)
    {
        for (int j = 1; j < (int)arr.size() - i; j++)
        {
            if (t(arr[j - 1], arr[j]))
            {
                T temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
    return true;
}

int main()
{
    std::vector<int> arr{3, 4, 6, 3, 2, 5, 100, 99, 886, 1};
    bubble_sort(arr, greater<int>);
    for (int i = 0; i < arr.size(); i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    bubble_sort(arr, less<int>);
    for (int i = 0; i < arr.size(); i++)
    {
        std::cout << arr[i] << " ";
    }

    return 0;
}