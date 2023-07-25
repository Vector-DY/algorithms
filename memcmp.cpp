#include <iostream>
#include <assert.h>

int mymemcpy(const void *str1, const void *str2, size_t count)
{
    assert(str1);
    assert(str2);

    while (count-- && *(char *)str1 == *(char *)str2) {
        str1 = (char *)str1 + 1;
        str2 = (char *)str2 + 1;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

void test1()
{
    char *str1 = "abcdefg";
    char *str2 = "abcdefg";

    std::cout << mymemcpy(str1, str2, 7) << std::endl;
}

void test2() 
{
    char *str1 = "abcdefg";
    char *str2 = "abcaaaa";
    std::cout << mymemcpy(str1, str2, 6) << std::endl;
}

int main(int argc, char* argv[])
{
    test1();
    test2();
    return 0;
}