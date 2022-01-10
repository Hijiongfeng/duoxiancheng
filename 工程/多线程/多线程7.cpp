#include<iostream>	
#include<vector>
#include<chrono>
#include<memory>
#include<future>
#include<thread>

using namespace std;

class AA7 {

public:
	AA7() {
		this->val = 7;
	}
	int mythread(int num) {
		cout << "mythread() start" << " �߳�ID: " << this_thread::get_id() << endl;
		//std::this_thread::sleep_for(std::chrono::seconds(5));

		cout << "mythread() start" << " �߳�ID: " << this_thread::get_id() << endl;

		return num;
	}
public:
	int val;
};



int mythread(int val) {
	cout << "mythread() start" << " �߳�ID: " << this_thread::get_id() << endl;

	cout << val << endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));

	cout << "mythread() end" << " �߳�ID: " << this_thread::get_id() << endl;
	
	return 5;
}

void mythread2(std::promise<int>& res, int cal) {
	cout << "mythread() start" << " �߳�ID: " << this_thread::get_id() << endl;

	cout << cal << endl;

	cal++;
	cal *= 10;

	std::this_thread::sleep_for(std::chrono::seconds(5));

	int result = cal;
	res.set_value(result);
	cout << "mythread() end" << " �߳�ID: " << this_thread::get_id() << endl;
	return;
}

void mythread3(std::future<int>& temf) {
	cout << "mythread() start" << " �߳�ID: " << this_thread::get_id() << endl;
	auto result = temf.get();
	cout << "result�� " << result << endl;

	cout << "mythread() end" << " �߳�ID: " << this_thread::get_id() << endl;
	return;
}


int main() {

	cout << "main() " << " �߳�ID: " << this_thread::get_id() << endl;

	//std::future<int> result = std::async(std::launch::async,mythread);	//����һ���̣߳��󶨹�ϵ

	//std::this_thread::sleep_for(std::chrono::seconds(5));
	//cout << "continue....." << endl;

	//int def;
	//def = 0;
	//cout << result.get() << endl;	// �������� �ȴ� mythread() ִ����ϣ��õ����
	////result.wait();
	//cout << "I Love Chine" << endl;


	// ���Ա�������߳���ں���
	//AA7 myobja;
	//int temmper = 12;
	//std::future<int>result2 = std::async(std::launch::async,&AA7::mythread, &myobja, temmper);

	//cout << "continue....." << endl;

	//cout << result2.get() << endl;	// �������� �ȴ� mythread() ִ����ϣ��õ����
	////result.wait();
	//cout << "I Love Chine,2" << endl;


	// std::packaged_task

	//std::packaged_task<int(int)> mypt(mythread);
	//std::thread t1(std::ref(mypt), 1);
	//t1.join();

	//std::future<int> result = mypt.get_future();

	//cout << result.get() << endl;
	//cout << "I Love Chine" << endl;
	//

	std::packaged_task<int(int)> mypt([](int val) {			//	��װ lambda ���ʽ
		cout << "mythread() start" << " �߳�ID: " << this_thread::get_id() << endl;
		cout << val << endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		cout << "mythread() end" << " �߳�ID: " << this_thread::get_id() << endl;
		return 5;
	});

	//std::thread t2(std::ref(mypt), 12);
	//t2.join();
	//std::future<int> result = mypt.get_future();
	//cout << result.get() << endl;

	//mypt(100);
	//std::future<int> result = mypt.get_future();
	//cout << result.get() << endl;


	//std::promise  ��ģ��


	std::promise<int> mypro;
	std::thread t1(mythread2, std::ref(mypro), 12);
	t1.join();

	// ��ȡ���ֵ
	std::future<int> result = mypro.get_future();

	std::thread t2(mythread3, std::ref(result));

	t2.join();
	//cout << result.get() << endl;
	cout << "I Love Chine" << endl;

	system("pause");
	return 0;
}