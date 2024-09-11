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

class Node
{
public:
    std::unordered_map<char ,Node*>_children;
    Node():_isEnd(false)
    {
        std::cout<<"Node"<<std::endl;
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
            if(node->_children.find(ch) != node->_children.end())
            {
                std::cout<<"not find"<<std::endl;
                node->_children[ch] = new Node;
            }
            node = node->_children[ch];
        }
    }
    Tree()
    {
        RootNode = new Node();
    }
    ~Tree()
    {

    }
private:
    Node *RootNode;
    std::array<Node*,5>NodeArray;
    std::array<Node,5>NodeArray_;
};
#endif //UNTITLED21_PREFIX_TREE_H
