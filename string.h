#ifndef _MYSTRING_
#define _MYSTRING_

class String
{
public:
    String(const char *cstr = 0);
    String(const String &str);
    String &operator=(const String &str);
    char *get_c_str() const { return m_data; }
    ~String();

private:
    char *m_data;
};

#include <cstring>

inline String::String(const char *cstr)
{
    if (cstr)
    {
        m_data = new char[strlen(cstr) + 1];
        strcpy(m_data, cstr);
    }
    else
    {
        m_data = new char[1];
        *m_data = '\0';
    }
}

inline String::~String()
{
    delete[] m_data;
}

inline String &String::operator=(const String &str)
{
    if (this == &str)
    {
        return *this;
    }
    delete[] m_data;
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
    return *this;
}

inline String::String(const String &str)
{
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
}

#include <iostream>
using namespace std;

ostream &operator<<(ostream &os, const String &str)
{
    os << str.get_c_str();
    return os;
}

#endif