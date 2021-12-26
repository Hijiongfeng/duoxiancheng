#include <iostream>
#include<thread>
#include<string>

using namespace std;

void myprint() {
    cout << "子线程----" << endl;
    for (size_t i = 0; i < 10; i++)
    {
        cout << i << endl;
    }
    cout << "我的线程结束了" << endl;
}

class MM {
public:
    MM(int &i):m_i(i){
        cout << "MM构造函数被执行" << endl;
    }  
    MM(const MM &mm) :m_i(mm.m_i) {
        cout << "MM拷贝构造函数函数被执行" << endl;
    }
    ~MM()
    {
        cout << "~MM析构函数函数被执行" << endl;
    }
    void operator()() {
        cout << "我的线程operator（）开始执行了" << endl;

        cout << "mi 1的值为：" << m_i << endl;
        cout << "mi 2的值为：" << m_i << endl;
        cout << "mi 3的值为：" << m_i << endl;
        cout << "mi 4的值为：" << m_i << endl;
        cout << "mi 5的值为：" << m_i << endl;
        // ***
        cout << "我的线程operator（）执行完毕了" << endl;
    }
public:
    int& m_i;
};

int main()
{
    std::cout << "Hello World!\n";
    
    thread test1(myprint);
    if (test1.joinable()) {
        cout << "can join or detach" << endl;
    }
    else
    {
        cout << "can not join or detach" << endl;
    }
    test1.join();
    //test1.detach();
    int num = 5;
    MM mm1(num);
    thread test2(mm1);
    test2.join();

    cout << "主线程结束了" << endl;
    cout << "主线程结束了1" << endl;
    cout << "主线程结束了2" << endl;
    return 0;
}

