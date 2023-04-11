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

class A{
    public:
      void f(int x, char c){

      }
      long g(double x){
        return 0;
      }
      int operator()(int N){return 0;}
};

void foo(int x){

}

int main(){
    A a;
    std::thread t1(a,6); // a copy of a and then invoke it as a functor in a different thread
    std::thread t2(std::ref(a),6); //launch a as a functor in a different thread
    std::thread t3(A(),6); //creates a temporary A, which is moved into the thread object and then creates thread
    std::thread t4([](int x){return x*x;},6);// through a lambda function
    std::thread t5(foo,6); //through functions
    std::thread t6(&A::f , a, 6, 'w'); // making a copy of a and then invoke a's function a.f(6,'w') in a different thread.
    std::thread t7(&A::f,&a,6,'w');
    std::thread t8(std::move(a),6);
    //std::async(std::launch::async,a,6);
   // std::bind(a,6);
    //std::call_once(once_flag,a,6);
}