#include<iostream>
#include<string>
#include<memory>
using namespace std;


class Singleton{
public:
    static Singleton& get_instance(){
        static Singleton s;
        return s;
    }
    void show(){
        cout<<"This is a singleton "<<endl;
    }
    Singleton(){}
    Singleton(const Singleton&)=delete;
    Singleton(const Singleton&&)=delete;
    Singleton& operator=(const Singleton&)=delete;

};

int main(){
    Singleton& s=Singleton::get_instance();
    s.show();
    return 0;
}




