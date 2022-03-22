#include<iostream>
#include<memory>
using namespace std;

void foo_construct(){
    int *p = new int(3);

    shared_ptr<int> sptr(p);
    shared_ptr<int> sptr2(new int(4));
    shared_ptr<int> sptr3 = sptr2;
    shared_ptr<int> sptr4 = make_shared<int>(5);
    cout<<sptr2.use_count()<<endl; //引用次数
}

void foo_construct1(){
    shared_ptr<int> sptr2(new int(4));
    {
        shared_ptr<int> sptr3 = sptr2;
        cout<<sptr2.use_count()<<endl;
    }
    cout<<sptr2.use_count()<<endl;
}

int main(){

    foo_construct1();

    return 0;
}