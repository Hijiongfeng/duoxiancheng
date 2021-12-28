#include<iostream>
#include<thread>
#include<vector>
#include<list>
#include<mutex>


using namespace std;


class AA4 {

public:

	std::unique_lock<mutex> aFunction() {
		unique_lock<mutex> myunique(my_mutex1);
		return myunique;
	}

	void inMsgReciveQue() {
		for (int i = 0; i < 10000; i++) {
	
			{
				//my_mutex1.lock();
				unique_lock<mutex> myguard(my_mutex1);
				unique_lock<mutex> myguard2(std::move(myguard));
				//myguard.lock();		// �����Լ�unlock
				
				//myguard.unlock();

				// ����ǹ�����룻  �Ȱ����ͷų��� �ñ���߳��ܹ��õ������
				//mutex *pts = myguard.release();

				//pts->lock();
				
				cout << "inMsgReciveQue: " << i << endl;
				msgReciveque.push_back(i);
				//pts->unlock();
				
				//this_thread::sleep_for(std::chrono::seconds(20));		//	��Ϣ 20s

			}
		}
	}

	bool outMagLULPro(int& command) {
		
		unique_lock<mutex> myguard(my_mutex1);
		//my_mutex1.lock();
		//this_thread::sleep_for(std::chrono::milliseconds(200));		//	��Ϣ 20s

		if (!msgReciveque.empty()) {
			command = msgReciveque.front();  // ȡԪ��
			msgReciveque.pop_front();		// ����

			return true;
		}
		return false;
	}

	void outMsgReciveQue() {
		int command = 0;
		for (int i = 0; i < 10000; i++) {
			bool result = outMagLULPro(command);
			if (result == true) {
				cout << "outMagLULPro(),�Ӷ�����ȡ��һ��Ԫ��: " <<command<< endl;
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


int main4() {

	
	AA4 myobj;
	
	thread mythread_out(&AA4::outMsgReciveQue, &myobj);
	thread mythread_in(&AA4::inMsgReciveQue, &myobj);


	mythread_out.join();
	mythread_in.join();


	[]() {cout << "I love china" << endl; }();

	return 0;
}