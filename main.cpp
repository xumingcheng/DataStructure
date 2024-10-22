//
// Created by 请输入我的名字 on 2024/9/20.
//
#include "problem.h"
#include "debug.h"

typedef struct classroom
{
    int total;
}ClassRoom;

int & test1(ClassRoom & tRoom)
{
    int b = 10;
    int & a= b;
    //todo int & test1(ClassRoom & tRoom) 函数返回了一个对 b 的引用，这会导致错误，
    //todo 因为 b 是一个局部变量，当函数结束时，b 的生命周期结束，其引用将变得无效。
   // return b;//todo 错误导致失败局部变量的引用
   //todo 这是正确的，因为 tRoom.total 是一个类成员变量，其生命周期与 tRoom 对象相同。因此，当你返回 tRoom.total 的引用时，引用是有效的，直到 tRoom 对象被销毁。
   return tRoom.total;
}
int * test2(ClassRoom *ptRoom)
{
    int b = 80;
    int *a  = &b;
    //return a //todo b 是一个局部变量，它的作用域仅限于 test2 函数。当函数结束时，b 被销毁，指向它的指针 a 将指向一个无效的地址。不会报错，但是存在问题
    return &ptRoom->total;
}
void TestDebug (int num)
{
    if (num == 0)
    {
        throw newProblem();
    }
}
int main()
{
    auto Node = new NodeP;
    Node->studyUniquePtr();
    Node->useofString();
    ClassRoom tRoom = {0};
    tRoom.total = 20;
    int & use = test1(tRoom);
    int * puse = test2(&tRoom);
    std::cout<<"usetotal is "<<use<<std::endl;
    std::cout<<"pusetotal is "<<*puse<<std::endl;
    try {
        TestDebug(0);
    }
    catch (problem &_problem)
    {
        std::cout<<"fail ......"<<std::endl;

    }


}
