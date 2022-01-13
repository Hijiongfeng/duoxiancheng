#include<iostream>
#include<future>
#include<thread>
#include<memory>
#include<atomic>

using namespace std;

int mythread8(int val) {
	cout << "mythread(int val) start ，线程ID = " << std::this_thread::get_id() << endl;

	std::this_thread::sleep_for(std::chrono::seconds(5));

	cout << "mythread(int val) end ,线程ID = " << std::this_thread::get_id() << endl;

	return 5;
}
//void mythread9(std::future<int>& temf) {
void mythread9(std::shared_future<int>& temf) {
	cout << "mythread() start" << " 线程ID: " << this_thread::get_id() << endl;
	auto result = temf.get();   // get内部实现是一个移动语义； 只能get一次，那么如果多个线程都需要get，那怎么办呢？
	
	cout << "result： " << result << endl;

	cout << "mythread() end" << " 线程ID: " << this_thread::get_id() << endl;
	return;
}

//int g_mycount = 0;
std::atomic<int> g_mycount = 0; // 我们可以像操作一个 int 类型一样，操作这个 atomic int类型
//std::mutex g_mymut;


void myreadcount() {
	for (int i = 0; i < 1000000; i++) {
		//g_mymut.lock();
		g_mycount++;  // 不会被打断了
		//g_mymut.unlock();
	}
	return;
}

atomic_bool g_ifend = false;

void mythread10() {

	std::chrono::milliseconds dura(1000);
	while (g_ifend == false)
	{
		cout << "thread id = " << std::this_thread::get_id() << " 运行中" << endl;
		std::this_thread::sleep_for(dura);
	}
	cout << "thread id = " << std::this_thread::get_id() << " 运行结束" << endl;
}


int main109() {

	cout << "main()" << " 线程ID = " << std::this_thread::get_id() << endl;

	//std::future<int> result = std::async(std::launch::deferred,mythread8, 10);

	//cout << "continue....." << endl;
	////cout << result.get() << endl;	// 卡在这里 等待 mythread() 执行完毕，拿到结果
	//// wait() 相当于join（）
	//std::future_status status = result.wait_for(std::chrono::seconds(6)); // 等待 一秒  
	//
	//if (status == std::future_status::timeout) {
	//	// 超时表示线程还没执行完
	//	cout << "超时，线程还没执行完毕" << endl;
	//}
	//else if(status == std::future_status::ready) {
	//	// ready 表示线程成功返回
	//	cout << "线程执行完毕，返回"<<endl;
	//	cout << result.get() << endl;
	//}
	//else if (status == std::future_status::deferred) {
	//	// 如果async的第一个参数设置为deferred 则这个条件成立；
	//	cout << "线程延时执行" << endl;
	//	cout << result.get() << endl;
	//}

	//std::packaged_task<int(int)> mypack(mythread8);
	//std::thread t2(std::ref(mypack), 12);
	//t2.join();
	//std::future<int> result = mypack.get_future();
	////std::shared_future<int> result2(std::move(result));
	//bool ifcanget = result.valid();
	//std::shared_future<int> result_s(result.share());
	//// std::share_furture 的get是复制值，不是移动数据
	//ifcanget = result.valid();

	//int mythread_result_s = result_s.get();
	//mythread_result_s = result_s.get();

	////std::thread t3(mythread9, std::ref(result));
	////t3.join();
	//std::thread t3(mythread9, std::ref(result_s));
	//t3.join();
	

	// 三、原子操作	atomic

	// 互斥量  多线程编程 保护共享数据，操作数据时候，先锁住，再操作 再解锁
	// 两个线程 一个读数据，一个写数据
	// 原子操作 atomic  ，可以理解成不需要利用互斥量 加锁解锁的一种操作
	// 在多线程中不会被打断的 的执行片段 原子操作，比互斥量更成一筹；；
	// 互斥量加锁一般是针对一个代码段，原子操作一般针对的是一个变量（针对一个变量进行临界）
	// 原子操作，一般指不可分割的操作，不会出现半分割的状态

	//std::thread t1(myreadcount);
	//std::thread t2(myreadcount);
	//t1.join();
	//t2.join();

	//cout << "两个线程执行完毕，g_mycount的值为：" << g_mycount << endl;

	
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