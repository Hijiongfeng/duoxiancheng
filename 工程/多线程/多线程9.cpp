#include<iostream>
#include<future>
#include<thread>
#include<memory>
#include<atomic>

using namespace std;

//int g_mycount = 0;
std::atomic<int> g_mycount9 = 0; // ���ǿ��������һ�� int ����һ����������� atomic int����
//std::mutex g_mymut;

void myreadcount9() {
	for (int i = 0; i < 1000000; i++) {
		//g_mymut.lock();
		g_mycount9 = g_mycount9+1;  // ���ᱻ�����  +1 �������
		//g_mymut.unlock();
	}
	return;
}


int mythread11(int val) {
	//cout << "mythread11() �߳̿�ʼ " << " �߳�ID = " << std::this_thread::get_id() << endl;
	return 1;
}

int main() {

	cout << "main()" << " �߳�ID = " << std::this_thread::get_id() << endl;

	//std::thread t1(myreadcount9);
	//std::thread t2(myreadcount9);

	//t1.join();
	//t2.join();

	//cout << "�����߳�ִ�н������ܺͣ�" << g_mycount9 << endl;

	vector<std::future<int>> my_thread;

	for (int i = 0; i < 10; i++) {
		my_thread.push_back(std::async(mythread11, i));
		//std::async(std::launch::async | std::launch::deferred, mythread11, i);
	}
	
	for (auto& x : my_thread) {
		std::future_status status = x.wait_for(0s);
		//std::future_status status = x.wait_for(std::chrono::seconds(0));
		if (status == std::future_status::timeout) {
			// ��ʱ��ʾ�̻߳�ûִ����
			cout << "��ʱ���̻߳�ûִ�����" << endl;
		}
		else if (status == std::future_status::ready) {
			// ready ��ʾ�̳߳ɹ�����
			cout << "�߳�ִ����ϣ�����" << endl;
			cout << x.get() << endl;
		}
		else if (status == std::future_status::deferred) {
			// ���async�ĵ�һ����������Ϊdeferred ���������������
			cout << "�߳���ʱִ��" << endl;
			cout << x.get() << endl;
		}
	}

	//cout << result.get() << endl;

	cout << "I Love Chine" << endl;
	system("pause");
	return 0;
}