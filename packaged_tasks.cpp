#include<iostream>
#include<thread>
#include<string>
#include<fstream>
#include<mutex>
#include<queue>
#include<condition_variable>
#include<future>
#include<functional>
using namespace std;

int factorial(int N){
    int k = 1;
    for(int i = N;i > 1;i--){
        k = k*i;
    }
    cout << "Result is = " << k << endl;
    return k;
}

int main(){
    std::packaged_task<int(int)> t(factorial);
    t(6);
}