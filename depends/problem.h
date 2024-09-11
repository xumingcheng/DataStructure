//
// Created by 请输入我的名字 on 2024/9/9.
//

#ifndef UNTITLED21_PROBLEM_H
#define UNTITLED21_PROBLEM_H
#include <string>
#include <string_view>
#include <iostream>
class NodeP
{
public:

     NodeP(int a):_isEnd(false)
    {
        std::cout<<"Node"<<std::endl;
    }
    NodeP(char *pc,size_t len)
    {
       std::cout<<"str"<<str<<std::endl;
       Msg = pc;
       len = len;
    }
    //todo operator用作类型转换运算符，将当前对象隐式或显式地转换为 std::string_view 类型 eg:
    // constexpr MyStringBuffer buffer("Hello, World!", 13);
    // 隐式转换为 std::string_view
    // std::string_view view = buffer;
    // 在 constexpr 标记下，该运算符函数必须在编译时生成有效的 std::string_view 实例。
    // const 表示这个成员函数不会修改当前对象的状态，保证对象在调用这个函数时不会发生变化
    constexpr operator std::string_view() const noexcept
    {
         return{Msg,len};
    }
private :
     bool _isEnd;
     char * Msg;
     size_t len;
};
//todo 字面量的理解
static NodeP operator""_tb(const char *pc,size_t len)
{
    return{pc,len};
}


class TreeP
{
public:
    TreeP()
    {
        std::cout<<"tree" << std::endl;
        //RootNode = new NodeP; //todo :错误没有合适的构造函数。
        RootNode = new NodeP(20); //todo :正确。
        auto nodes = "400"_tb; //todo nodes是一个对象，根据字面值类型的不同，操作符函数可以接受的参数也是不一样的。int operator"" _n(unsigned long long i)
                               //todo double operator"" _f(long double i) int operator"" _s(const char*s, size_t l) int operator"" _c(char c)
    }
private:
    Node *RootNode;
    std::array<Node*,5>NodeArray; //todo:不会调用构造函数，但是他在给Node初始化的时候也会调用构造函数
    std::array<Node,5>NodeArray2; //todo:会调用构造函数
};
//todo 字面量运算符

#endif //UNTITLED21_PROBLEM_H
