//
// Created by 请输入我的名字 on 2024/9/9.
//

#include "prefix_tree.h"
int main()
{
    auto Treetest = new Tree;
    Treetest->insertNode("china");
    Treetest->insertNode("japan");
    Treetest->insertNode("Usa");
    Treetest->findNode("china");
    Treetest->findNode("japan");
    Treetest->findNode("beautiful");
    Treetest->findNode("beautiful");
    Treetest->findNode("U");
}