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
				//myguard.lock();		// 不用自己unlock
				
				//myguard.unlock();

				// 处理非共享代码；  先把锁释放出来 让别的线程能够拿到这个锁
				//mutex *pts = myguard.release();

				//pts->lock();
				
				cout << "inMsgReciveQue: " << i << endl;
				msgReciveque.push_back(i);
				//pts->unlock();
				
				//this_thread::sleep_for(std::chrono::seconds(20));		//	休息 20s

			}
		}
	}

	bool outMagLULPro(int& command) {
		
		unique_lock<mutex> myguard(my_mutex1);
		//my_mutex1.lock();
		//this_thread::sleep_for(std::chrono::milliseconds(200));		//	休息 20s

		if (!msgReciveque.empty()) {
			command = msgReciveque.front();  // 取元素
			msgReciveque.pop_front();		// 消除

			return true;
		}
		return false;
	}

	void outMsgReciveQue() {
		int command = 0;
		for (int i = 0; i < 10000; i++) {
			bool result = outMagLULPro(command);
			if (result == true) {
				cout << "outMagLULPro(),从队列中取出一个元素: " <<command<< endl;
			}
			else {
				cout << "outMagLULPro(),执行，但队列为空" << endl;
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