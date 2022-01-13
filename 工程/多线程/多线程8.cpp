#include<iostream>
#include<future>
#include<thread>
#include<memory>
#include<atomic>

using namespace std;

int mythread8(int val) {
	cout << "mythread(int val) start ���߳�ID = " << std::this_thread::get_id() << endl;

	std::this_thread::sleep_for(std::chrono::seconds(5));

	cout << "mythread(int val) end ,�߳�ID = " << std::this_thread::get_id() << endl;

	return 5;
}
//void mythread9(std::future<int>& temf) {
void mythread9(std::shared_future<int>& temf) {
	cout << "mythread() start" << " �߳�ID: " << this_thread::get_id() << endl;
	auto result = temf.get();   // get�ڲ�ʵ����һ���ƶ����壻 ֻ��getһ�Σ���ô�������̶߳���Ҫget������ô���أ�
	
	cout << "result�� " << result << endl;

	cout << "mythread() end" << " �߳�ID: " << this_thread::get_id() << endl;
	return;
}

//int g_mycount = 0;
std::atomic<int> g_mycount = 0; // ���ǿ��������һ�� int ����һ����������� atomic int����
//std::mutex g_mymut;


void myreadcount() {
	for (int i = 0; i < 1000000; i++) {
		//g_mymut.lock();
		g_mycount++;  // ���ᱻ�����
		//g_mymut.unlock();
	}
	return;
}

atomic_bool g_ifend = false;

void mythread10() {

	std::chrono::milliseconds dura(1000);
	while (g_ifend == false)
	{
		cout << "thread id = " << std::this_thread::get_id() << " ������" << endl;
		std::this_thread::sleep_for(dura);
	}
	cout << "thread id = " << std::this_thread::get_id() << " ���н���" << endl;
}


int main109() {

	cout << "main()" << " �߳�ID = " << std::this_thread::get_id() << endl;

	//std::future<int> result = std::async(std::launch::deferred,mythread8, 10);

	//cout << "continue....." << endl;
	////cout << result.get() << endl;	// �������� �ȴ� mythread() ִ����ϣ��õ����
	//// wait() �൱��join����
	//std::future_status status = result.wait_for(std::chrono::seconds(6)); // �ȴ� һ��  
	//
	//if (status == std::future_status::timeout) {
	//	// ��ʱ��ʾ�̻߳�ûִ����
	//	cout << "��ʱ���̻߳�ûִ�����" << endl;
	//}
	//else if(status == std::future_status::ready) {
	//	// ready ��ʾ�̳߳ɹ�����
	//	cout << "�߳�ִ����ϣ�����"<<endl;
	//	cout << result.get() << endl;
	//}
	//else if (status == std::future_status::deferred) {
	//	// ���async�ĵ�һ����������Ϊdeferred ���������������
	//	cout << "�߳���ʱִ��" << endl;
	//	cout << result.get() << endl;
	//}

	//std::packaged_task<int(int)> mypack(mythread8);
	//std::thread t2(std::ref(mypack), 12);
	//t2.join();
	//std::future<int> result = mypack.get_future();
	////std::shared_future<int> result2(std::move(result));
	//bool ifcanget = result.valid();
	//std::shared_future<int> result_s(result.share());
	//// std::share_furture ��get�Ǹ���ֵ�������ƶ�����
	//ifcanget = result.valid();

	//int mythread_result_s = result_s.get();
	//mythread_result_s = result_s.get();

	////std::thread t3(mythread9, std::ref(result));
	////t3.join();
	//std::thread t3(mythread9, std::ref(result_s));
	//t3.join();
	

	// ����ԭ�Ӳ���	atomic

	// ������  ���̱߳�� �����������ݣ���������ʱ������ס���ٲ��� �ٽ���
	// �����߳� һ�������ݣ�һ��д����
	// ԭ�Ӳ��� atomic  ���������ɲ���Ҫ���û����� ����������һ�ֲ���
	// �ڶ��߳��в��ᱻ��ϵ� ��ִ��Ƭ�� ԭ�Ӳ������Ȼ���������һ���
	// ����������һ�������һ������Σ�ԭ�Ӳ���һ����Ե���һ�����������һ�����������ٽ磩
	// ԭ�Ӳ�����һ��ָ���ɷָ�Ĳ�����������ְ�ָ��״̬

	//std::thread t1(myreadcount);
	//std::thread t2(myreadcount);
	//t1.join();
	//t2.join();

	//cout << "�����߳�ִ����ϣ�g_mycount��ֵΪ��" << g_mycount << endl;

	
	std::thread t1(mythread10);
	std::thread t2(mythread10);
	
	std::this_thread::sleep_for(std::chrono::seconds(5));
	g_ifend = true;

	t1.join();
	t2.join();



	cout << "I Love Chine" << endl;
	system("pause");
	return 0;
}