#include<iostream>
#include<future>
#include<thread>
#include<memory>
#include<atomic>

using namespace std;

//int g_mycount = 0;
std::atomic<int> g_mycount9 = 0; // 我们可以像操作一个 int 类型一样，操作这个 atomic int类型
//std::mutex g_mymut;

void myreadcount9() {
	for (int i = 0; i < 1000000; i++) {
		//g_mymut.lock();
		g_mycount9 = g_mycount9+1;  // 不会被打断了  +1 结果不对
		//g_mymut.unlock();
	}
	return;
}


int mythread11(int val) {
	//cout << "mythread11() 线程开始 " << " 线程ID = " << std::this_thread::get_id() << endl;
	return 1;
}

int main() {

	cout << "main()" << " 线程ID = " << std::this_thread::get_id() << endl;

	//std::thread t1(myreadcount9);
	//std::thread t2(myreadcount9);

	//t1.join();
	//t2.join();

	//cout << "两个线程执行结束，总和：" << g_mycount9 << endl;

	vector<std::future<int>> my_thread;

	for (int i = 0; i < 10; i++) {
		my_thread.push_back(std::async(mythread11, i));
		//std::async(std::launch::async | std::launch::deferred, mythread11, i);
	}
	
	for (auto& x : my_thread) {
		std::future_status status = x.wait_for(0s);
		//std::future_status status = x.wait_for(std::chrono::seconds(0));
		if (status == std::future_status::timeout) {
			// 超时表示线程还没执行完
			cout << "超时，线程还没执行完毕" << endl;
		}
		else if (status == std::future_status::ready) {
			// ready 表示线程成功返回
			cout << "线程执行完毕，返回" << endl;
			cout << x.get() << endl;
		}
		else if (status == std::future_status::deferred) {
			// 如果async的第一个参数设置为deferred 则这个条件成立；
			cout << "线程延时执行" << endl;
			cout << x.get() << endl;
		}
	}

	//cout << result.get() << endl;

	cout << "I Love Chine" << endl;
	system("pause");
	return 0;
}