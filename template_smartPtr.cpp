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

template<typename T>
class CSmartPtr;

//引用计数
template<typename T>
class CRefCount{

    friend class CSmartPtr<T>;

public:

    CRefCount(T* pStu){
        m_Obj = pStu;
        m_nCount = 1;
    }

    ~CRefCount(){
        delete m_Obj;
        m_Obj = nullptr;
    }

    void AddRef(){
        m_nCount++;
    }

    void Release(){
        if(--m_nCount == 0){
            delete this;
        }
    }

private:
    T* m_Obj;
    int m_nCount;

};

//创建一个类，利用该类的构造和析构(进出作用域自动被编译器调用)的机制来解决资源自动释放的问题
//使用模板
template<typename T>
class CSmartPtr{
public:

    CSmartPtr(){
        m_pRef = nullptr;
    }

    CSmartPtr(T* pStu){
        m_pRef = new CRefCount<T>(pStu);
        cout<<"普通构造函数"<<endl;
    }

    ~CSmartPtr(){
        m_pRef->Release();
    }

    CSmartPtr(CSmartPtr& obj){
        cout<<"拷贝构造"<<endl;
        m_pRef = obj.m_pRef;
        m_pRef->AddRef();
    }

    CSmartPtr& operator=(CSmartPtr& obj){
        cout<<"运算符重载"<<endl;
        if(m_pRef == obj.m_pRef){
            return *this;
        }

        

        if(m_pRef!=nullptr){
            m_pRef->Release();
        }

        m_pRef = obj.m_pRef;
        m_pRef->AddRef();

        return *this;
        

    }
  
    //需要想办法让CSmartPtr像一个指针(运算符重载)
    T* operator->(){
        return m_pRef->m_Obj;
    }
    T** operator&(){
        return &m_pRef->m_Obj;
    }

    T& operator*(){
        return *m_pRef->m_Obj;
    }
    operator CStudent*(){
        return m_pRef->m_Obj;
    }


private:
    CRefCount<T>* m_pRef; //将资源放入智能指针类中，管理起来

};

class CTest{
public:
    CTest(){}
};

int main(){

    //结合引用计数和写时拷贝
    CStudent* pStu = new CStudent();

    CSmartPtr<CStudent> sp1(pStu);
    CSmartPtr<CStudent> sp2(sp1); //调拷贝构造

    sp2=sp1; //调运算符重载

    CSmartPtr<CTest> sp3(new CTest);
    

    return 0;
}