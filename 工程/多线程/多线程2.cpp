#include<iostream>
#include<thread>
#include<string>

using namespace std;

class A {
public:
	mutable int m_i;
	A(int i) :m_i(i) { cout << "构造函数执行" << this<<" thread_id:" <<this_thread::get_id()<< endl; }
	A(const A& a) :m_i(a.m_i) { cout << "拷贝构造函数执行" << this<< " thread_id:" << this_thread::get_id()<<endl; }
	~A()
	{
		cout << "析构函数执行" << this<< " thread_id:" << this_thread::get_id()<<endl;
	}
	void thread_work(int a) {
		cout << "a = " << a << endl;
		cout << "子线程thread_work执行:" << this<<"  线程ID:"<<this_thread::get_id() << endl;
	}
};

void printD(const int &i,const string& mystring) {
	cout << i << endl;			// 分析可得 i 并不是mvar的引用 这是一个值传递，
								// 即使使用了detach，这个值也是安全的，在主线程结束后 并没有被销毁。
	cout << mystring << endl;
	return;
}

void myPrint2(const A& pmybuf) {

	cout << "子线程地址" << &pmybuf<<" ";

	cout << "子线程ID：" << this_thread::get_id() << endl;
}

void myPrint3(unique_ptr<int> psd) {

	cout << "子线程ID：" << this_thread::get_id() << endl;
}

int main2() {

	//int mvar = 1;
	//int& mvary = mvar;
	//char mybuf[] = "this is a string";
	//string str = "this is a string";
	//thread mythread1(printD, mvar, string(mybuf));  // 临时对象安全
	//mythread1.detach();


	//cout << "主线程ID" << this_thread::get_id()<<endl;
	//int mavr = 1;
	//A a(mavr);
	//thread mythread2(myPrint2,std::ref(a));
	//mythread2.join();

	//unique_ptr<int> myp(new int(10));
	//thread mythread3(myPrint3, move(myp));
	//mythread3.join();
	
	A myobj(10);
	thread mythread4(&A::thread_work,std::ref(myobj), 100);
	mythread4.join();
	//system("pause");
	return 0;
}