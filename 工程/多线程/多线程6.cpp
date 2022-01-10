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
			cout << "往队列中插入一个元素：" << i << endl;
			msgRecvList.push_back(i);

			my_cond.notify_all(); // 我们尝试把wait的线程唤醒；
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
		//		cout << "从队列中取出一个元素：" << command << endl;
		//	}
		//	else {
		//		cout << "队列为空，不进行操作" << i<<endl;
		//	}
		//}
		while (true) {
			unique_lock<mutex> mylock(mymutex);

			// wait()用来等一个东西
			// 如果第二个参数的lambda表达式返回值是false，那么wait()将解锁互斥量，并阻塞到本行
			// 阻塞到什么时候为止呢？阻塞到其他某个线程调用notify_one()成员函数为止；
			//当 wait() 被 notify_one() 激活时，会先执行它的 条件判断表达式 是否为 true，
			//如果为true才会继续往下执行

			my_cond.wait(mylock, [this] {
				if (!msgRecvList.empty())
					return true;
				return false;
				});

			// 流程只要能走到这边，一定是锁着的；
			command = msgRecvList.front();
			msgRecvList.pop_front();

			cout << "outMsgRecvList()执行，取出一个元素" << command << " 线程ID："<<this_thread::get_id() << endl;
			mylock.unlock();   // 提前解锁，让其他线程能够处理；
			

			// 执行一些其他动作，，假设需要 100ms
			// 上面那个锁已经放开，其他线程获取到锁，又尝试唤醒，这个时候程序在这边执行，，则唤醒失败（不是卡在 wait() 那边）
			// 这个时候notify_one 就没有效果

			//if (msgRecvList.empty()) break;

		}

	}

private:
	list<int> msgRecvList;
	mutex mymutex;
	condition_variable my_cond;  // 条件变量
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