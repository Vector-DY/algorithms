#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
template <typename T>
class Allocator
{
public:
    T *allocate(int size)
    {
        return (T *)malloc(sizeof(T) * size);
    }
    T *deallocate(T *p)
    {
        free(p);
    }
    void construct(T *p, const T &val)
    {
        new (p) T(val);
    }
    void destroy(T *p)
    {
        p->~T();
    }
};
template <typename T, typename Alloc = Allocator<T>>
class Vector
{
public:
    Vector(int size = 20)
    {
        alloc = new Allocator<T>();
        _begin = alloc->allocate(size);
        _end = _begin + size;
        _now = _begin;
    }
    ~Vector()
    {
        free(_begin);
        delete alloc;
    }
    Vector(const Vector<T> &vec)
    {
        alloc = new Allocator<T>();
        int size = vec.end - vec.begin;
        _begin = alloc->allocate(size);
        _end = _begin + size;
        _now = _begin;

        T *p = vec._begin;
        for (; p != vec._now; p++, _now++)
        {
            alloc->construct(_now, *p);
        }
    }
    Vector &operator=(const Vector<T> &vec)
    {
        if (this == &vec)
            return *this;
        alloc->deallocate(_begin);
        alloc = new Allocator<T>();
        int size = vec.end - vec.begin;
        _begin = alloc->allocate(size);
        _end = _begin + size;
        _now = _begin;

        T *p = vec.begin;
        for (; p != vec._now; p++, _now++)
        {
            alloc->construct(_now, *p);
        }

        return *this;
    }

    Vector(Vector<T> &&vec)
    {
        cout << "Vector(Vector<T> && vec)" << endl;
        alloc = vec.alloc;
        _begin = vec._begin;
        _now = vec._now;
        _end = vec._end;
        vec._begin = vec._end = vec._now = nullptr;
        vec.alloc = nullptr;
    }

    Vector &operator=(Vector<T> &&vec)
    {
        alloc = vec.alloc;
        _begin = vec._begin;
        _now = vec._now;
        _end = vec._end;
        vec._begin = vec._end = vec._now = nullptr;
        vec.alloc = nullptr;

        return *this;
    }

    void push_back(const T &val)
    {
        if (_now == _end)
        {
            resize();
        }
        alloc->construct(_now, val);
        _now++;
    }

    void pop_back()
    {
        if (_now != _begin)
        {
            alloc->destory(_now--);
        }
    }

    T &operator[](int index)
    {
        return _begin[index];
    }
    bool empty()
    {
        return _now == _begin;
    }
    int size()
    {
        return _now - _begin;
    }
    void print()
    {
        T *p = _begin;
        while (p != _now)
        {
            cout << *p << " ";
            p++;
        }
        cout << endl;
    }

private:
    T *_begin;
    T *_now;
    T *_end;
    Alloc *alloc;

    void resize()
    {
        int size = _end - _begin;
        T *p = alloc->allocate(size * 2);
        for (int i = 0; i < size; i++)
        {
            p[i] = _begin[i];
        }
        alloc->deallocate(_begin);
        _begin = p;
        _now = p + size;
        _end = p + size * 2;
    }
};
Vector<int> get()
{
    Vector<int> vec(50);
    for (int i = 0; i <= 5; i++)
        vec.push_back(i);
    return vec;
}
int main()
{
    Vector<string> vec;
    vec.push_back("111");
    vec.push_back("strring");
    vec.push_back("9527");
    vec.print();
    Vector<int> v(50);
    for (int i = 0; i <= 15; i++)
    {
        v.push_back(i);
    }
    v.print();
    // test right-value
    Vector<int> a = move(v);
    cout << a.size() << endl;

    a = get();
    a.print();
    return 0;
}
