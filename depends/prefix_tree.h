//
// Created by 请输入我的名字 on 2024/9/9.
//

#ifndef UNTITLED21_PREFIX_TREE_H
#define UNTITLED21_PREFIX_TREE_H
#include <string>
#include <iostream>
#include <array>
#include <string>
#include <unordered_map>
/*
 * insert string "cat", "cap"
 * _children中的第一个节点是c 然后创建下一个节点a,在创建t节点
 *            c
 *            |
 *            a  c的children map
 *           / \
 *          t   p a的children map
 * */
class Node
{
public:
    std::unordered_map<char ,Node*>_children;
    Node():_isEnd(false)
    {
        //std::cout<<"Node"<<std::endl;
    }
    void setEnd(Node * node)
    {
        node->_isEnd = true;
    }
    ~Node()
    {
        for(auto & _item:_children)
        {
            delete _item.second; // 释放子节点
        }
    }

private :
    bool _isEnd;

};

class Tree
{
public:
    void insertNode(std::string str)
    {
        Node * node = RootNode;
        for(auto ch:str)
        {
            if(node->_children.find(ch) == node->_children.end())
            {
                //std::cout<<"not find"<<std::endl;
                node->_children[ch] = new Node;
            }
            node = node->_children[ch];
        }
        node->setEnd(node);
        std::cout<<"insert string "<< str << " success " <<std::endl;
    }
    //如果找不到则插入
    void findNode(std::string str)
    {
        Node * node = RootNode;
        bool _findFlag = true;
        for(auto ch:str)
        {
            if(node->_children.find(ch) == node->_children.end()) //todo 查找过程
            {
                node->_children[ch] = new Node;
                _findFlag = false;
            }
            node = node->_children[ch];
        }
        if(!_findFlag)  node->setEnd(node);
        else std::cout<< " find " << str << " success " <<std::endl;
    }
    Tree()
    {
        RootNode = new Node();
    }
    //todo 当一个对象通过 delete 被销毁时，它的析构函数会自动执行。如果该对象包含指针成员（如 Node 中的 _children 容器存储了 Node* 指针），则析构函数负责清理这些动态分配的资源。
    ~Tree()
    {
        delete RootNode;
    }
private:
    Node *RootNode;
};
#endif //UNTITLED21_PREFIX_TREE_H
