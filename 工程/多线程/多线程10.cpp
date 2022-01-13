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

class CWinLock {  // 自动释放 windows下的临界区
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
				//EnterCriticalSection(&my_winsec);	// 进入临界区
				CWinLock clock(&my_winsec);
				msgReciveque.push_back(i);
				
				//LeaveCriticalSection(&my_winsec);	// 离开临界区
#else // _WINDOWJQ
				
				//lock_guard<recursive_mutex> subguard(re_mutex);
				//testfunc1();
				//my_mutex1.lock();
				std::chrono::milliseconds dura(100);
				//if (ti_mutex.try_lock_for(dura)) {		// 尝试拿锁 在100ms内，拿到锁 返回为true
				if (ti_mutex.try_lock_until(std::chrono::steady_clock::now()+dura)) {
					msgReciveque.push_back(i);
					ti_mutex.unlock();
					
				}
				else {
					// 这次没拿到锁  执行这些语句
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
			command = msgReciveque.front();  // 取元素
			msgReciveque.pop_front();		// 消除
			LeaveCriticalSection(&my_winsec);
			return true;
		}
		LeaveCriticalSection(&my_winsec);
#else
		my_mutex1.lock();
		if (!msgReciveque.empty()) {
			command = msgReciveque.front();  // 取元素
			msgReciveque.pop_front();		// 消除
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
				cout << "outMagLULPro(),从队列中取出一个元素" << endl;
			}
			else {
				cout << "outMagLULPro(),执行，但队列为空" << endl;
			}
		}
	}
	AA()
	{
#ifdef _WINDOWJQ_
		InitializeCriticalSection(&my_winsec);	//	用临界区之前要初始化
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
	std::recursive_mutex re_mutex;  // 递归式的互斥量   可以多次加锁（相比于普通的互斥量）
	std::timed_mutex ti_mutex;			// 带有超时的互斥量
	std::recursive_timed_mutex re_time_mutex;   // 带有超时的递归互斥量
};



int main() {
	AA myobj;
	thread mythread_out(&AA::outMsgReciveQue, &myobj);
	thread mythread_in(&AA::inMsgReciveQue, &myobj);

	mythread_out.join();
	mythread_in.join();


	[]() {cout << "I love china" << endl; }();  // （）直接调用、

	return 0;
}