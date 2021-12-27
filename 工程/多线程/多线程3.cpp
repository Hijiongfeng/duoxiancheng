#include<iostream>
#include<thread>
#include<vector>
#include<list>
#include<mutex>


using namespace std;

vector<int> gv{ 1 };

void myPrint(int num) { // 线程入口函数

	//cout << "子线程开始执行,线程编号: " << num << endl;

	//cout << "子线程结束执行,线程编号: " << num << endl;

	cout << "线程ID: " << this_thread::get_id() <<"  gv的值："<<gv[0] << endl;
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
		//lock_guard<mutex> sbguard(my_mutex);		//  lock_guard 构造函数里面 进行lock，析构函数 执行unlock
		//my_mutex1.lock();
		//my_mutex2.lock();
		lock(my_mutex1, my_mutex2);
		lock_guard<mutex> suguard1(my_mutex1, adopt_lock);
		lock_guard<mutex> suguard2(my_mutex2, adopt_lock);

		//this_thread::sleep_for(std::chrono::seconds(20));

		if (!msgReciveque.empty()) {
			command = msgReciveque.front();  // 取元素
			msgReciveque.pop_front();		// 消除
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

private:
	list<int> msgReciveque;
	mutex my_mutex1;
	mutex my_mutex2;
};


int main3() {

	//vector<thread> mythread;

	//for (int i = 0; i < 10; i++) {
	//	mythread.push_back(thread(myPrint, i));
	//}

	//for (auto iter = mythread.begin(); iter != mythread.end(); iter++) {
	//	iter->join();
	//}
	//cout << "主线程结束" << endl;

	//2.1只读的数据

	//2.2读写的数据

	AA myobj;
	thread mythread_out(&AA::outMsgReciveQue, &myobj);
	thread mythread_in(&AA::inMsgReciveQue, &myobj);

	mythread_out.join();
	mythread_in.join();


	[]() {cout << "I love china" << endl; }();

	return 0;
}