#include<iostream>
#include<thread>
#include<string>
#include<fstream>
#include<mutex>
#include<condition_variable>
#include<future>

using namespace std;

//std::mutex m;
//std::condition_variable cond;

int factorial(int N){
    int k = 1;
    for(int i = N;i > 1;i--){
        k *= i;
    }
    cout << "The factorial is = " << k << endl;
    return k;
}



int main(){
     int x;
    //std::thread t1(factorial,4,std::ref(x));
    std::future<int> fu = std::async(factorial,4);
    x = fu.get();
    //t1.join();
    return 0;
}