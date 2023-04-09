#include<iostream>
#include<thread>
#include<string>
#include<fstream>
#include<mutex>

using namespace std;

class LogFile{
    std::mutex m;
    //std::mutex m2;
    std::once_flag flag;
    ofstream f;
    public:
      LogFile(){
       // f.open("log.txt");
      }
      void shared_print(string id,int value){
        //lazy initialization or initialization upon first use edm

       // if(!f.is_open()){
            // not a thread safe method opens file twice define it above if condition
           // std::unique_lock<mutex> locker2(m2);
           // f.open("log.txt");
       // }
       std::call_once(flag,[&](){ f.open("log.txt");});
        std::unique_lock<mutex> locker(m,std::defer_lock);

       // locker.lock();

       // std::unique_lock<mutex> locker2 = std::move(locker);
      }
};



int main(){

}