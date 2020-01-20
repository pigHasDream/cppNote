/* Synchrosizing Operations */
#include <chrono>
#include <deque>
#include <functional>
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <mutex>

using namespace std;
std::deque<int> q;
std::mutex mu;
std::condition_variable cond;

void function_1() {
	int count = 10;
	while (count > 0) {
		std::unique_lock<std::mutex> locker(mu);
		q.push_front(count);
		locker.unlock();
    cond.notify_one(); // notify one waiting thread if any.
    cond.notify_all(); // notify all waiting thread if any
		std::this_thread::sleep_for(std::chrono::seconds(1));
		count--;
	}
}

void function_2() {
	int data = 0;
	while ( data != 1) {
		std::unique_lock<std::mutex> locker(mu);

    // Need also to use the lambda function in case of "spurious wake"
    // The lambda function will sure the extra check of functionality of 
    // correct behavior
    cond.wait(locker, [](){ return not q.empty();});
    data = q.back();
    q.pop_back();
    locker.unlock();
    cout << "t2 got a value from t1: " << data << endl;
  }
	
}
// It is hard to set the sleep time.
int main() {
	std::thread t1(function_1);
	std::thread t2(function_2);
	t1.join();
	t2.join();
	return 0;
}

