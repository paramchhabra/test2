
#include <iostream>

class A{
    public:
        void yay(){
            std::cout<<"yes"<<std::endl;
        }
};

class B: public A{
    public:
        void yay(){
            std::cout<<"no"<<std::endl;
        }
};

class C: public B{

};

int main(){
    C a;
    a.yay();
}