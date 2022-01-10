#include<iostream>
#include<vector>
#include<thread>
#include<list>
#include<mutex>


using namespace std;

class AA6 {

public:
	void inMsgRecvList() {
		for (int i = 0; i < 10000; i++) {
			

			unique_lock<mutex> mylock(mymutex);
			cout << "�������в���һ��Ԫ�أ�" << i << endl;
			msgRecvList.push_back(i);

			my_cond.notify_all(); // ���ǳ��԰�wait���̻߳��ѣ�
		}
		return;
	}
	
	//bool msgRecvListTest(int& command) {
	//	unique_lock<mutex> mylock(mymutex);
	//	if (!msgRecvList.empty()) {
	//		command = msgRecvList.front();
	//		msgRecvList.pop_front();
	//		return true;
	//	}
	//	return false;
	//}

	void outMsgRecvList() {
		int command = 0;
		//for (int i = 0; i < 10000; i++) {
		//	if (msgRecvListTest(command) == true) {
		//		cout << "�Ӷ�����ȡ��һ��Ԫ�أ�" << command << endl;
		//	}
		//	else {
		//		cout << "����Ϊ�գ������в���" << i<<endl;
		//	}
		//}
		while (true) {
			unique_lock<mutex> mylock(mymutex);

			// wait()������һ������
			// ����ڶ���������lambda���ʽ����ֵ��false����ôwait()��������������������������
			// ������ʲôʱ��Ϊֹ�أ�����������ĳ���̵߳���notify_one()��Ա����Ϊֹ��
			//�� wait() �� notify_one() ����ʱ������ִ������ �����жϱ��ʽ �Ƿ�Ϊ true��
			//���Ϊtrue�Ż��������ִ��

			my_cond.wait(mylock, [this] {
				if (!msgRecvList.empty())
					return true;
				return false;
				});

			// ����ֻҪ���ߵ���ߣ�һ�������ŵģ�
			command = msgRecvList.front();
			msgRecvList.pop_front();

			cout << "outMsgRecvList()ִ�У�ȡ��һ��Ԫ��" << command << " �߳�ID��"<<this_thread::get_id() << endl;
			mylock.unlock();   // ��ǰ�������������߳��ܹ�����
			

			// ִ��һЩ������������������Ҫ 100ms
			// �����Ǹ����Ѿ��ſ��������̻߳�ȡ�������ֳ��Ի��ѣ����ʱ����������ִ�У�������ʧ�ܣ����ǿ��� wait() �Ǳߣ�
			// ���ʱ��notify_one ��û��Ч��

			//if (msgRecvList.empty()) break;

		}

	}

private:
	list<int> msgRecvList;
	mutex mymutex;
	condition_variable my_cond;  // ��������
};


int main7() {
	AA6 myobj;
	thread my_thread1(&AA6::outMsgRecvList, &myobj);
	thread my_thread1_1(&AA6::outMsgRecvList, &myobj);
	thread my_thread2(&AA6::inMsgRecvList, &myobj);

	my_thread1.join();
	my_thread1_1.join();
	my_thread2.join();

	cout << "I love china  " << this_thread::get_id() << endl;

	return 0;
}