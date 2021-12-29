#include<iostream>
#include<thread>
#include<mutex>

// 单例类

std::mutex resource_mutex;
std::once_flag o_flag;

class MyCAS {

	static void CreatInstance() {

		std::cout << "CreatInstance()执行" << std::endl;
		instatic = new MyCAS();
		static CGarhuisou cl;
	}

private:
	MyCAS(){}		// 私有化构造函数   // 类外不能创建

private:
	static MyCAS* instatic;		// 静态成员函数

public:

	static MyCAS* getInstance() {

		//if (instatic == nullptr) {   //双层锁定，以提高效率
		//	
		//	std::unique_lock<std::mutex> mymutex(resource_mutex);  //  主动解锁

		//	if (instatic == nullptr) {
		//		instatic = new MyCAS();
		//		static CGarhuisou cl;
		//	}
		//}

		std::call_once(o_flag, CreatInstance);

		return instatic;
	}

	class CGarhuisou {		//	类中套类，用于释放对象

	public:
		~CGarhuisou()
		{
			if (MyCAS::instatic) {
				delete MyCAS::instatic;
				MyCAS::instatic = nullptr;
			}
		}

	};

	void func() {

		std::cout << "测试：" << std::endl;
	}
};

MyCAS* MyCAS::instatic = nullptr;		// 静态成员函数类外初始化

void mythread() {		//	线程入口函数
	std::cout << "我的线程开始执行了" << std::endl;
	MyCAS* p_a = MyCAS::getInstance();
	std::cout << "线程ID: " << std::this_thread::get_id() << " p_a指针的值: " << p_a << std::endl;
	std::cout << "我的线程结束了" << std::endl;
	return;
}

int main5() {

	//MyCAS* p_a = MyCAS::getInstance();  // 静态成员函数可以通过 类名直接访问
	//MyCAS* p_b = MyCAS::getInstance();

	//p_a->func();

	//MyCAS::getInstance()->func();

	std::thread thread1(mythread);
	std::thread thread2(mythread);

	thread1.join();
	thread2.join();


	MyCAS* p_a = MyCAS::getInstance();
	std::cout << "主线程线程ID: " << std::this_thread::get_id() << " p_a指针的值: " << p_a << std::endl;
	p_a->func();

	return 0;
}