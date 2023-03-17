#include <iostream>
using namespace std;

void *mymemmove(void *dest, const void *src, size_t count)
{
    if ((dest == nullptr) || (src == nullptr))
    {
        return nullptr;
    }
    void *res = dest;
    if (dest < src)
    {
        while (count--)
        {
            *(char *)dest = *(char *)src;
            dest = (char *)dest + 1;
            src = (char *)src + 1;
        }
    }
    else
    {
        while (count--)
        {
            *((char *)dest + count) = *((char *)src + count);
        }
    }
    return res;
}

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    mymemmove(a + 2, a, 16);

    for (int i = 0; i < 10; i++)
    {
        cout << a[i] << endl;
    }
    return 0;
}