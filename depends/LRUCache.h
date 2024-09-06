//
// Created by 请输入我的名字 on 2024/9/5.
//

#ifndef UNTITLED21_LRUCACHE_H
#define UNTITLED21_LRUCACHE_H
#include <map>
#include <string>
#include <exception>
class myexception :public std::exception
{
public:
    virtual  const char * what() const noexcept override
    {
        return "cant find you data";
    }
};
template <typename T,typename M>
class LruCache
{
public :
    typedef struct node{
        T  _key;
        M _value;
        struct node *pre;
        struct node *next;
        //node(const T& key, const M& value) : _key(key), _value(value), pre(nullptr), next(nullptr) {}
    } Node;
    LruCache() : _firstNode(nullptr) {}

    void putValue(T _T,M _M)
    {
       // auto num = getNodeLength();
       if(_firstNode == nullptr)
       {
           _firstNode = insertNode(_T, _M);;
       }else
       {
           auto _pNode = insertNode(_T, _M);
           _pNode->next = _firstNode;
           _firstNode->pre = _pNode;
           _firstNode = _pNode;
       }
    }

    int getNodeLength()
    {
        int num = 0;
        Node* tempNode = nullptr;
        for(tempNode = _firstNode;tempNode->next != nullptr;tempNode = tempNode->next)
        {
            num++;
        }
        return num;
    }
    Node *operator[](T _T)
    {
        Node* tempNode = nullptr;
        for(tempNode = this->_firstNode;tempNode != nullptr;tempNode = tempNode->next)
        {
            if(tempNode->_key == _T)
            {
                return tempNode;
            }
        }
        throw  myexception();
    }
    void getValue(T _T)
    {
        Node* tempNode = nullptr;
        std::cout<<"temp node:"<<tempNode<<std::endl;
        tempNode =( *this)[_T];
        std::cout<<"temp node:"<<tempNode<<std::endl;
        if(tempNode == nullptr)
        {
            throw myexception();
        }
        if(tempNode->pre == nullptr) return;
        if(tempNode->next != nullptr)
        {
            tempNode->pre = tempNode->next->pre;
        }
        tempNode->pre->next = tempNode->next;
        tempNode->pre = nullptr;
        tempNode->next = _firstNode;
        _firstNode->pre = tempNode;
        _firstNode = tempNode;
    }

    void display()
    {
        Node* tempNode = _firstNode;  // 从第一个节点开始
        while (tempNode != nullptr) {  // 遍历链表直到最后一个节点
            std::cout << "The key is " << tempNode->_key << std::endl;
            std::cout << "The value is " << tempNode->_value << std::endl;
            tempNode = tempNode->next;  // 移动到下一个节点
        }
    }
    ~LruCache()
    {
        for(auto Node = _firstNode;Node != NULL;Node = Node->next)
        {
            std::cout << "delete node"<< std::endl;
            delete Node;
        }
    }
private:
    Node *_firstNode;
    Node * insertNode(T _T,M _M)
    {
        auto node = new Node;
        node->_key = _T;
        node->_value = _M;
        node->pre = nullptr;
        node->next = nullptr;
        return node;
    }
};
#endif //UNTITLED21_LRUCACHE_H
