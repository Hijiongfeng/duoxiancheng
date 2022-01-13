#include<iostream>
#include<thread>
#include<vector>
#include<list>
#include<mutex>
#include<Windows.h>

//#define _WINDOWJQ_

using namespace std;

#ifdef _WINDOWJQ_
CRITICAL_SECTION my_winsec;
#endif // _WINDOWJQ_

class CWinLock {  // �Զ��ͷ� windows�µ��ٽ���
public:
	CWinLock(CRITICAL_SECTION* m_Critemp) {
		m_Criptr = m_Critemp;
		EnterCriticalSection(m_Criptr);
	}
	~CWinLock()
	{
		LeaveCriticalSection(m_Criptr);
	}

private:
	CRITICAL_SECTION* m_Criptr;
};



class AA {

public:
	void inMsgReciveQue() {
		for (int i = 0; i < 1000; i++) {
			
			//my_mutex.lock();
			cout << "inMsgReciveQue: " << i << endl;
			{
#ifdef _WINDOWJQ_ 
				//EnterCriticalSection(&my_winsec);	// �����ٽ���
				CWinLock clock(&my_winsec);
				msgReciveque.push_back(i);
				
				//LeaveCriticalSection(&my_winsec);	// �뿪�ٽ���
#else // _WINDOWJQ
				
				//lock_guard<recursive_mutex> subguard(re_mutex);
				//testfunc1();
				//my_mutex1.lock();
				std::chrono::milliseconds dura(100);
				//if (ti_mutex.try_lock_for(dura)) {		// �������� ��100ms�ڣ��õ��� ����Ϊtrue
				if (ti_mutex.try_lock_until(std::chrono::steady_clock::now()+dura)) {
					msgReciveque.push_back(i);
					ti_mutex.unlock();
					
				}
				else {
					// ���û�õ���  ִ����Щ���
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
				}				
#endif
			}
		}
	}

	bool outMagLULPro(int& command) {
#ifdef _WINDOWJQ_
		EnterCriticalSection(&my_winsec);
		
		if (!msgReciveque.empty()) {
			command = msgReciveque.front();  // ȡԪ��
			msgReciveque.pop_front();		// ����
			LeaveCriticalSection(&my_winsec);
			return true;
		}
		LeaveCriticalSection(&my_winsec);
#else
		my_mutex1.lock();
		if (!msgReciveque.empty()) {
			command = msgReciveque.front();  // ȡԪ��
			msgReciveque.pop_front();		// ����
			my_mutex1.unlock();
			//my_mutex2.unlock();
			return true;
		}
		my_mutex1.unlock();	
#endif
		return false;
	}

	void outMsgReciveQue(){
		int command = 0;
		for (int i = 0; i < 1000; i++) {
			bool result = outMagLULPro(command);
			if (result == true) {
				cout << "outMagLULPro(),�Ӷ�����ȡ��һ��Ԫ��" << endl;
			}
			else {
				cout << "outMagLULPro(),ִ�У�������Ϊ��" << endl;
			}
		}
	}
	AA()
	{
#ifdef _WINDOWJQ_
		InitializeCriticalSection(&my_winsec);	//	���ٽ���֮ǰҪ��ʼ��
#endif // _WINDOWJQ_
	}

	void testfunc1() {
		lock_guard<std::recursive_mutex> subguard(re_mutex);

	}

	void testfunc2() {
		lock_guard<std::recursive_mutex> subguard(re_mutex);
	}
private:
	list<int> msgReciveque;
	mutex my_mutex1;
	mutex my_mutex2;
	std::recursive_mutex re_mutex;  // �ݹ�ʽ�Ļ�����   ���Զ�μ������������ͨ�Ļ�������
	std::timed_mutex ti_mutex;			// ���г�ʱ�Ļ�����
	std::recursive_timed_mutex re_time_mutex;   // ���г�ʱ�ĵݹ黥����
};



int main() {
	AA myobj;
	thread mythread_out(&AA::outMsgReciveQue, &myobj);
	thread mythread_in(&AA::inMsgReciveQue, &myobj);

	mythread_out.join();
	mythread_in.join();


	[]() {cout << "I love china" << endl; }();  // ����ֱ�ӵ��á�

	return 0;
}