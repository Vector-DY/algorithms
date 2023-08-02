#include <iostream>
#include <memory>
#include <atomic>
using namespace std;
namespace fc {
    // 定义一个callable 对象类作为默认删除器
    template<typename T>
    class default_deleter{
    public:
        void operator()(T* ptr) {
            delete ptr;
        }
    };

    template<typename T, typename deleter = default_deleter<T>>
    class shared_ptr{
    private:
        // 原生堆指针
        T *ptr = nullptr;
        // 指向use_count的指针，事实上use_count是结构体中的一个成员，用指针可扩展
        std::atomic<int> *use_count = nullptr;
    public:
        // 默认构造
        shared_ptr() = default;
        // 原生指针构造
        shared_ptr(T *_ptr);
        // 拷贝构造
        shared_ptr(const shared_ptr &lsh);
        // 移动构造
        shared_ptr(shared_ptr && lsh);
        // 拷贝赋值运算符
        shared_ptr& operator=(const shared_ptr &lsh);
        // 移动复制运算符
        shared_ptr& operator=(shared_ptr && lsh);
        // 析构
        ~shared_ptr();
        // 函数运算符
        T* operator->();
        // 解引用运算符
        T& operator*();
        // 重载到bool的隐式转换
        operator bool() const;
        // 交换
        void swap(shared_ptr & lsh);
        // 解除对当前指针的管理，如有新的ptr则托管新的指针
        void reset(T *_ptr = nullptr);
        // 引用计数
        int count();
        // 获取原生指针
        T* get();
    };

    template<typename T, typename deleter>
    shared_ptr<T, deleter>::shared_ptr(T *_ptr) : ptr(_ptr), use_count(new std::atomic<int>(1)){}
    
    // 拷贝构造
    template<typename T, typename deleter>
    shared_ptr<T, deleter>::shared_ptr(const shared_ptr &lsh) {
        ptr = lsh.ptr;
        use_count = lsh.use_count;
        ++*use_count;
    }
    // 移动构造
    template<typename T, typename deleter>
    shared_ptr<T, deleter>::shared_ptr(shared_ptr && lsh) {
        std::swap(ptr, lsh.ptr);
        std::swap(use_count, lsh.use_count);
    }

    template<typename T, typename deleter>
    shared_ptr<T, deleter> &shared_ptr<T,deleter>::operator=(const shared_ptr &lsh) {
        shared_ptr<T, deleter>lsh_copy(lsh);
        swap(lsh_copy);
        return *this;
    }

    template<typename T, typename deleter>
    shared_ptr<T, deleter> &shared_ptr<T, deleter>::operator=(shared_ptr && lsh) {
        if (this != & lsh) {
            // 如果原来有托管对象
            if (ptr) {
                --*use_count;
                if (*use_count <= 0) {
                    deleter()(ptr);
                    delete use_count;
                }
                ptr = nullptr;
                use_count = nullptr;
            }
            swap(lsh);
        }
        return *this;
    }

    // 析构
    template<typename T, typename deleter>
    shared_ptr<T, deleter>::~shared_ptr() {
        if (ptr) {
            --*use_count;
            if (*use_count <= 0) {
                deleter()(ptr);
                delete use_count;
            } 
        }
    }
    template<typename T, typename deleter>
    T *shared_ptr<T, deleter>::operator->() {
        return ptr;
    }
    template<typename T, typename deleter>
    T &shared_ptr<T, deleter>::operator*() {
        return *ptr;
    }
    template<typename T, typename deleter>
    shared_ptr<T, deleter>::operator bool() const {
        return ptr != nullptr;
    }
    template<typename T, typename deleter>
    void shared_ptr<T, deleter>::swap(shared_ptr & lsh) {
        std::swap(ptr, lsh.ptr);
        std::swap(use_count, lsh.use_count);
    }

    template<typename T, typename deleter>
    void shared_ptr<T, deleter>::reset(T *_ptr) {
        if (ptr) { // 先释放原托管
            --*use_count;
            if (*use_count <= 0) {
                deleter()(ptr);
                delete use_count;
            }
            ptr = nullptr;
            use_count = nullptr;
        }
        if (_ptr) {
            ptr = _ptr;
            use_count = new std::atomic<int>(1);
        }
    }


    template<typename T, typename deleter>
    int shared_ptr<T, deleter>::count() {
        return *use_count;
    }

    template<typename T, typename deleter>
    T *shared_ptr<T, deleter>::get() {
        return ptr;
    }
}


class Student {
public:
    int id;
    int age;
    Student(int id_, int age_):id(id_), age(age_){}
};


void print(fc::shared_ptr<Student> &s){
    if (s.get() == nullptr) {
        cout << "nullptr" << endl;
        return;
    }
    cout << "id:" << s->id << "  " << "age:" << s->age << endl;
    cout << "use count:" << s.count() << endl;
}

int main(int argc, char *argv[]){
    {
        cout<<"拷贝构造测试，解引用，箭头函数测试"<<endl;
        fc::shared_ptr<Student> s1(new Student(0,18));
        fc::shared_ptr<Student> s2(s1);
        (*s1).age = 19;
        print(s2);
        cout<<"自赋值测试"<<endl;
        s1 = s1;
        print(s1);
        if (s1) {
            cout << "隐式转换为bool" << endl;
        }
    }

    {
        cout<<"测试reset"<<endl;
        fc::shared_ptr<Student> s1(new Student(0,18));
        s1.reset();
        print(s1);
        s1.reset(new Student(1,19));
        print(s1);

    }
    {
        cout<<"移动构造测试"<<endl;
        fc::shared_ptr<Student> s1(fc::shared_ptr<Student>(new Student(0,18)));
        print(s1);

        cout<<"拷贝赋值运算符测试"<<endl;
        fc::shared_ptr<Student> s2;
        s2 = s1;
        print(s1);
        print(s2);

        cout<<"移动赋值运算符测试"<<endl;
        fc::shared_ptr<Student> s3 (new Student(2,20));
        s1 = std::move(s3);
        print(s1);
        print(s2);
        print(s3);
    }
    return 0;
}