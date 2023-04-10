#include<iostream>
#include<thread>
#include<string>
#include<fstream>
#include<mutex>
#include<queue>
#include<condition_variable>

using namespace std;


std::deque<int> q;
std::mutex m;
std::condition_variable cond;

void func1(){
    int k = 1;
    while(k > 0){
        std::unique_lock<mutex> locker(m);
        q.push_front(k);
        locker.unlock();
        cond.notify_one(); // notify one waiting thread, if it exists.
        std::this_thread::sleep_for(chrono::seconds(1));
        k--;
    }
}

void func2(){
    int data = 0;
    while(data != 1){
        std::unique_lock<mutex> locker(m);
        cond.wait(locker,[](){return !q.empty();}); // thread 2 in sleeping mode
        if(!q.empty()){
            data = q.back();
            q.pop_back();
            locker.unlock();
            cout << "t2 got a value from t1: " << data << endl;
        }
       /* else{
            locker.unlock();
            std::this_thread::sleep_for(chrono::microseconds(10));
        }*/
    }
}

int main(){
    std::thread t1(func1);
    std::thread t2(func2);
    t1.join();
    t2.join();

}