#include<iostream>
#include<thread>
#include<string>

using namespace std;

class A {
public:
	mutable int m_i;
	A(int i) :m_i(i) { cout << "���캯��ִ��" << this<<" thread_id:" <<this_thread::get_id()<< endl; }
	A(const A& a) :m_i(a.m_i) { cout << "�������캯��ִ��" << this<< " thread_id:" << this_thread::get_id()<<endl; }
	~A()
	{
		cout << "��������ִ��" << this<< " thread_id:" << this_thread::get_id()<<endl;
	}
	void thread_work(int a) {
		cout << "a = " << a << endl;
		cout << "���߳�thread_workִ��:" << this<<"  �߳�ID:"<<this_thread::get_id() << endl;
	}
};

void printD(const int &i,const string& mystring) {
	cout << i << endl;			// �����ɵ� i ������mvar������ ����һ��ֵ���ݣ�
								// ��ʹʹ����detach�����ֵҲ�ǰ�ȫ�ģ������߳̽����� ��û�б����١�
	cout << mystring << endl;
	return;
}

void myPrint2(const A& pmybuf) {

	cout << "���̵߳�ַ" << &pmybuf<<" ";

	cout << "���߳�ID��" << this_thread::get_id() << endl;
}

void myPrint3(unique_ptr<int> psd) {

	cout << "���߳�ID��" << this_thread::get_id() << endl;
}

int main2() {

	//int mvar = 1;
	//int& mvary = mvar;
	//char mybuf[] = "this is a string";
	//string str = "this is a string";
	//thread mythread1(printD, mvar, string(mybuf));  // ��ʱ����ȫ
	//mythread1.detach();


	//cout << "���߳�ID" << this_thread::get_id()<<endl;
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