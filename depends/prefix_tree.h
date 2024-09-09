//
// Created by 请输入我的名字 on 2024/9/9.
//

#ifndef UNTITLED21_PREFIX_TREE_H
#define UNTITLED21_PREFIX_TREE_H
#include <string>
#include <iostream>
#include <array>
#include <string>

class Node
{
public:

 Node(const char *a ,size_t b):_isEnd(false)
    {
        std::cout<<"Node"<<std::endl;
    }
private :
    bool _isEnd;
};
static Node operator""_tb(const char* t,size_t len)
{
    return{t,len};
}
class Tree
{
public:
    Tree()
    {
        std::cout<<"tree" << std::endl;
    }
private:
    Node *RootNode;
    std::array<Node*,5>NodeArray;
};
#endif //UNTITLED21_PREFIX_TREE_H
