#include <iostream>
#include <memory>
class B; // 前向声明
class A {
public:
    std::shared_ptr<B> b_ptr;
    ~A() {
        std::cout << "A destructor called" << std::endl;
    }
};

class B {
public:
    std::shared_ptr<A> a_ptr;
    ~B() {
        std::cout << "B destructor called" << std::endl;
    }
};

class D; // 前向声明

class C {
public:
    std::shared_ptr<D> d_ptr;
    ~C() {
        std::cout << "C destructor called" << std::endl;
    }
};

class D {
public:
    std::weak_ptr<C> c_ptr; // 使用 weak_ptr 替代 shared_ptr
    ~D() {
        std::cout << "D destructor called" << std::endl;
    }
};
// 指针的引用计数是对象的引用计数
int main() {
    {
        std::shared_ptr<A> a = std::make_shared<A>();
        std::shared_ptr<B> b = std::make_shared<B>();
        std::cout << a.use_count() << " " << b.use_count() << std::endl;
        std::cout << a->b_ptr.use_count() << " " << b->a_ptr.use_count() << std::endl;
        a->b_ptr = b; // A 指向 B
        std::cout << a.use_count() << " " << b.use_count() << std::endl;
        std::cout << a->b_ptr.use_count() << " " << b->a_ptr.use_count() << std::endl;
        b->a_ptr = a; // B 指向 A
        std::cout << a.use_count() << " " << b.use_count() << std::endl;
        std::cout << a->b_ptr.use_count() << " " << b->a_ptr.use_count() << std::endl;
    } // a 和 b 离开作用域，但由于循环引用，它们的析构函数不会被调用

    {
        std::shared_ptr<C> c = std::make_shared<C>();
        std::shared_ptr<D> d = std::make_shared<D>();
        c->d_ptr = d; // C 指向 D
        d->c_ptr = c; // D 对 C 使用 weak_ptr
    } // c 和 d 离开作用域，它们的析构函数会被正确调用
    std::cout << "End of main" << std::endl;
    return 0;
}

