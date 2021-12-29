#include<iostream>
#include<thread>
#include<mutex>

// ������

std::mutex resource_mutex;
std::once_flag o_flag;

class MyCAS {

	static void CreatInstance() {

		std::cout << "CreatInstance()ִ��" << std::endl;
		instatic = new MyCAS();
		static CGarhuisou cl;
	}

private:
	MyCAS(){}		// ˽�л����캯��   // ���ⲻ�ܴ���

private:
	static MyCAS* instatic;		// ��̬��Ա����

public:

	static MyCAS* getInstance() {

		//if (instatic == nullptr) {   //˫�������������Ч��
		//	
		//	std::unique_lock<std::mutex> mymutex(resource_mutex);  //  ��������

		//	if (instatic == nullptr) {
		//		instatic = new MyCAS();
		//		static CGarhuisou cl;
		//	}
		//}

		std::call_once(o_flag, CreatInstance);

		return instatic;
	}

	class CGarhuisou {		//	�������࣬�����ͷŶ���

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

		std::cout << "���ԣ�" << std::endl;
	}
};

MyCAS* MyCAS::instatic = nullptr;		// ��̬��Ա���������ʼ��

void mythread() {		//	�߳���ں���
	std::cout << "�ҵ��߳̿�ʼִ����" << std::endl;
	MyCAS* p_a = MyCAS::getInstance();
	std::cout << "�߳�ID: " << std::this_thread::get_id() << " p_aָ���ֵ: " << p_a << std::endl;
	std::cout << "�ҵ��߳̽�����" << std::endl;
	return;
}

int main5() {

	//MyCAS* p_a = MyCAS::getInstance();  // ��̬��Ա��������ͨ�� ����ֱ�ӷ���
	//MyCAS* p_b = MyCAS::getInstance();

	//p_a->func();

	//MyCAS::getInstance()->func();

	std::thread thread1(mythread);
	std::thread thread2(mythread);

	thread1.join();
	thread2.join();


	MyCAS* p_a = MyCAS::getInstance();
	std::cout << "���߳��߳�ID: " << std::this_thread::get_id() << " p_aָ���ֵ: " << p_a << std::endl;
	p_a->func();

	return 0;
}