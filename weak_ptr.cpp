#include<iostream>
#include<memory>
using namespace std;

class Cperson;
class CSon;

//循环引用
class Cperson{

public:
    Cperson(){}

    void Set(shared_ptr<CSon> pSon){
        m_pSon = pSon;
    }

    ~Cperson(){}

private:
    weak_ptr<CSon> m_pSon;
};

class CSon{

public:
    CSon(){}

    void Set(shared_ptr<Cperson> pParent){
        m_pParent = pParent;
    }

    ~CSon(){}

private:
    weak_ptr<Cperson> m_pParent;
};

void testhread(){
    Cperson* pPer = new Cperson();
    CSon* pSon = new CSon();

    {
        shared_ptr<Cperson> shared_Parent(pPer);
        shared_ptr<CSon> shared_Son(pSon);

        shared_Parent->Set(shared_Son);
        shared_Son->Set(shared_Parent);

        cout<<shared_Son.use_count()<<endl;
        cout<<shared_Parent.use_count()<<endl;
    }
    //循环引用，出作用域堆内存没有被释放
    
    

}

void testhread1(){
    Cperson* pPer = new Cperson();
    CSon* pSon = new CSon();

    {
        shared_ptr<Cperson> shared_Parent(pPer);
        shared_ptr<CSon> shared_Son(pSon);

        shared_Parent->Set(shared_Son);
        shared_Son->Set(shared_Parent);

        cout<<shared_Son.use_count()<<endl;
        cout<<shared_Parent.use_count()<<endl;
    }
    //循环引用，出作用域堆内存没有被释放
    
    

}

int main(){

    testhread1();

    return 0;
}