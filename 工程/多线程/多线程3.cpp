#include<iostream>
#include<thread>
#include<vector>
#include<list>
#include<mutex>


using namespace std;

vector<int> gv{ 1 };

void myPrint(int num) { // �߳���ں���

	//cout << "���߳̿�ʼִ��,�̱߳��: " << num << endl;

	//cout << "���߳̽���ִ��,�̱߳��: " << num << endl;

	cout << "�߳�ID: " << this_thread::get_id() <<"  gv��ֵ��"<<gv[0] << endl;
	return;
}

class AA {

public:
	void inMsgReciveQue() {
		for (int i = 0; i < 1000; i++) {
			
			//my_mutex.lock();
			cout << "inMsgReciveQue: " << i << endl;
			{
				//lock_guard<mutex> sbguard(my_mutex);
				//my_mutex1.lock();
				//my_mutex2.lock();
				lock(my_mutex1, my_mutex2);
				lock_guard<mutex> suguard1(my_mutex1, adopt_lock);
				lock_guard<mutex> suguard2(my_mutex2, adopt_lock);
				msgReciveque.push_back(i);
				//my_mutex2.unlock();
				//my_mutex1.unlock();

			}

			//my_mutex.unlock();
		}
	}

	bool outMagLULPro(int& command) {
		//lock_guard<mutex> sbguard(my_mutex);		//  lock_guard ���캯������ ����lock���������� ִ��unlock
		//my_mutex1.lock();
		//my_mutex2.lock();
		lock(my_mutex1, my_mutex2);
		lock_guard<mutex> suguard1(my_mutex1, adopt_lock);
		lock_guard<mutex> suguard2(my_mutex2, adopt_lock);
		if (!msgReciveque.empty()) {
			int com = msgReciveque.front();  // ȡԪ��
			msgReciveque.pop_front();		// ����
			//my_mutex1.unlock();
			//my_mutex2.unlock();
			return true;
		}
		//my_mutex.unlock();
		//my_mutex1.unlock();
		//my_mutex2.unlock();
		return false;
	}

	void outMsgReciveQue(){
		for (int i = 0; i < 1000; i++) {
			bool result = outMagLULPro(i);
			if (result == true) {
				cout << "outMagLULPro(),�Ӷ�����ȡ��һ��Ԫ��" << endl;
			}
			else {
				cout << "outMagLULPro(),ִ�У�������Ϊ��" << endl;
			}
		}
	}

private:
	list<int> msgReciveque;
	mutex my_mutex1;
	mutex my_mutex2;
};


int main() {

	//vector<thread> mythread;

	//for (int i = 0; i < 10; i++) {
	//	mythread.push_back(thread(myPrint, i));
	//}

	//for (auto iter = mythread.begin(); iter != mythread.end(); iter++) {
	//	iter->join();
	//}
	//cout << "���߳̽���" << endl;

	//2.1ֻ��������

	//2.2��д������

	AA myobj;
	thread mythread_out(&AA::outMsgReciveQue, &myobj);
	thread mythread_in(&AA::inMsgReciveQue, &myobj);

	mythread_out.join();
	mythread_in.join();


	[]() {cout << "I love china" << endl; }();

	return 0;
}