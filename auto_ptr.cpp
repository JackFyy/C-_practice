#include<iostream>
using namespace std;

class CStudent
{
public:
    CStudent(){

    }

    void test(){
        cout<<"CStudent"<<endl;
        m_nSex = 1;
    }

private:
    char* m_pszBuf;
    int m_nSex;

};

//创建一个类，利用该类的构造和析构(进出作用域自动被编译器调用)的机制来解决资源自动释放的问题
class CSmartPtr{
public:

    CSmartPtr(CStudent* pObj){
        m_pObj = pObj;
    }

    ~CSmartPtr(){
        if(m_pObj != nullptr){
            delete m_pObj;
        }
    }

    CSmartPtr& operator=(CSmartPtr& sp){
        if(m_pObj!=nullptr){
            delete m_pObj;
        }
        m_pObj = sp.m_pObj;
        sp.m_pObj = nullptr;

        return *this;

    }
    // CSmartPtr(CSmartPtr&) = delete;



    //需要想办法让CSmartPtr像一个指针(运算符重载)
    CStudent* operator->(){
        return m_pObj;
    }
    CStudent& operator*(){
        return *m_pObj;
    }
    operator bool(){
        return m_pObj != nullptr;
    }


private:
    CStudent* m_pObj; //将资源放入智能指针类中，管理起来

};

int main(){

    //CStudent* pStu = new CStudent();
    CSmartPtr sp(new CStudent());

    CSmartPtr sp2(new CStudent());
    sp2 = sp;
    // sp->test();
    // (*sp).test();
    // if(sp){
    //     cout<<"sp不为空"<<endl;
    // }

    return 0;
}