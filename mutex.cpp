#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<fstream>
//#include<stack>
using namespace std;

std::mutex mu;

//void shared_print(string message, int id){
   // mu.lock();
  //  cout << message << id << endl;
   // mu.unlock();
//}

class LogFile{
    std::mutex m;
    ofstream f;
    public:
      LogFile(){
        f.open("log.txt");
      }
      void shared_print(string id, int value){
        std::lock_guard<mutex> locker(m);
        f << "From " << id << " : " << value << endl;
      }
      // never return f to the outside scope
      //never pass f as argument to the provided function
};

class stack{
    int* _data;
    std::mutex _mu;
    public:  
      int& pop();
      int& top();
};





/*void myFunc(LogFile& log){
    for(int i = 0;i > -10;i--){
        log.shared_print(string("Call from t1: "), i);
    }
    
}*/

void myFunc(stack& s){
    int v = s.pop();
    process(v);
}

int main(){
    LogFile log;
    std::thread t1(myFunc, std::ref(log));
    for(int i = 0;i < 10;i++){
        log.shared_print(string("Call from MAIN: "), i);
    }

    t1.join();

    return 0;
}