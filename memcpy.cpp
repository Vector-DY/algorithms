#include <iostream>
using namespace std;

void *mymemcpy(void *dest, const void *src, size_t count)
{
    if ((dest == nullptr) || (src == nullptr))
    {
        return nullptr;
    }
    void *res = dest;
    while (count--)
    {
        *(char *)dest = *(char *)src;
        dest = (char *)dest + 1;
        src = (char *)src + 1;
    }
    return res;
}

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    mymemcpy(a + 2, a, 16);

    for (int i = 0; i < 10; i++)
    {
        cout << a[i] << endl;
    }
    return 0;
}