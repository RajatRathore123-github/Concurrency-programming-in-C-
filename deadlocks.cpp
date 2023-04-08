#include<iostream>
#include<thread>
#include<string>
#include<fstream>
#include<mutex>

using namespace std;


// deadlocks happen because each thread is waiting for other to complete but can be avoided if passed mutex serialize wise.
class LogFile{
    std::mutex m;
    std::mutex m2;
    ofstream f;
    public: 
      LogFile(){
          f.open("log.txt");
      }
      void shared_print(string id,int value){
          //using c++ std library we can also avoid deadlocks by using lock and std::adopt_lock parameter in locker.
          std::lock_guard<mutex> locker(m);
          std::lock_guard<mutex> locker(m2);
          cout << "From " << id << " : " << value << endl; 
      }

      void shared_print2(string id,int value){
          std::lock_guard<mutex> locker(m2);
          std::lock_guard<mutex> locker(m);
          cout << "From " << id << " : " << value << endl; 
      }

};

void myFunc(LogFile& log){
    for(int i = 0;i > -10;i--){
        log.shared_print("t1",i);
    }
}


int main(){
    LogFile log;
    std::thread t1(myFunc,std::ref(log));
    for(int i = 0;i < 10;i++){
        log.shared_print2(string("Call from main: "),i);
    }
    t1.join();
    return 0;
}