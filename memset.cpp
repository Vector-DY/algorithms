#include <iostream>
#include <assert.h>
void *mymemset(void *dest, int val, size_t count)
{
    assert(dest);
    void *res = dest;
    while (count--) {
        *(char *)dest = val;
        dest = (char *)dest + 1;
    }
    return  res;
}

int main()
{
	char arr[10];
	mymemset(arr,'a',10 * sizeof(char));
	for (int i = 0; i < 10; i++)
	{
		std::cout << arr[i] << std::endl;
	}
	return 0;
}
