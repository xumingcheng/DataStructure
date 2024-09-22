//
// Created by 请输入我的名字 on 2024/9/9.
//

#ifndef UNTITLED21_PROBLEM_H
#define UNTITLED21_PROBLEM_H
#include <string>
#include <string_view>
#include <iostream>
#include <memory>
typedef struct Student{
    int age;
    ~Student()
    {
        std::cout<<"desconruct Student"<<std::endl;
    }
    Student()
    {
        if(this != nullptr)
        {
            std::cout<<"conruct Student"<<std::endl;
        }

    }
}Student;

class NodeP
{
public:

     NodeP(int a):_isEnd(false)
    {
        std::cout<<"Node"<<std::endl;
    }
    NodeP(const char *pc,size_t len)
    {
       std::cout<<"str"<<std::endl;
       Msg = pc;
       len = len;
    }
    NodeP()
    {
         std::cout<<"NodeP construct"<<std::endl;
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


    //todo :: unique智能指针+++++++++++++++++++++++++++++++++++++++++++++++++++++++
    void studyUniquePtr()
    {
         _upStu = std::make_unique<Student>();//todo 会去调用相应的构造函数 ，make_unique是一个函数
         //todo ::不能被复制，只能通过move来转移所有权,_upStu会被置为空，
         auto p2 = std::move(_upStu);//todo p2是一个局部变量,超出作用域会被销毁，自动调用析构函数

        //todo 自定义智能指针资源释放函数,资源释放函数的入参需要能够处理智能指针管理的对象和类型，本例中需要将Student * 传入。
         auto testlambda = [](Student* stu)->void {
             delete stu ;
             return ;
         };
         std::unique_ptr<Student, decltype(testlambda)>ptr(new Student,testlambda);
    }
 /*todo ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

 //todo :: shared智能指针+++++++++++++++++++++++++++++++++++++++++++++++++++++++
    void studySharedPtr()
    {
        _usharedpStu = std::make_shared<Student>();//todo 会去调用相应的构造函数 ，shared_ptr是一个函数
        //todo ::能被复制，使用 std::move 不会转移所有权，而是将原来的 shared_ptr 赋值给新的 shared_ptr，并增加引用计数
        auto p2 = std::move(_usharedpStu);//todo _usharedpStu的move之后， p2继续持有该对象，他的引用计数仍然是1,，_usharedpStu会被置为空
        //todo p2是一个局部变量,超出作用域会被销毁，自动调用析构函数,当引用计数为0
        Student *_p =p2.get();//todo 获取原始指针
        p2.use_count(); //todo 获取引用计数的值,引用计数下降的方式：1=== 离开作用域
        //todo 2=== 被赋予新值时：std::shared_ptr<Student> p1 = std::make_shared<Student>(); // 引用计数为 1
        // todo std::shared_ptr<Student> p2 = p1; // 引用计数增加到 2
        //todo p1 = std::make_shared<Student>(); // 引用计数下降到 1（p2 仍然指向原来的对象）
        // 新的 Student 对象的引用计数为 1
        //  3=== 调用 reset() 函数时：std::shared_ptr<Student> p1 = std::make_shared<Student>(); // 引用计数为 1
        // std::shared_ptr<Student> p2 = p1; // 引用计数增加到 2
        // p1.reset(); // p1 不再持有对象，引用计数下降到 1 只有当p1是最后一个指向该资源的指针，调用reset才会调用相应的析构函数

        //todo ###################################### move的用法###############################
        // move 是一个语义移动函数，将左值显示转化为右值引用 左值：表示能够取地址的变量，右值：生命周期很短，无法取地址，如匿名对象，右值引用一般应用于语义移动，即避免了拷贝，提高性能
        // 右值引用（T&&）表示可以接管和修改临时对象或不再需要的对象的资源，而不会像左值引用那样需要保持原始对象的完整性.移动语义允许我们窃取源对象的资源，而不是复制它们。
        // 移动语义的核心思想是资源转移而不是资源拷贝
        // A obj1(100);               // 正常构造
        // A obj2 = std::move(obj1);   // 移动构造，而不是拷贝构造 当然你需要实现相应的移动构造函数
    }
    /*todo ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

    /*todo ============================STRING的使用====================================*/
    /*todo STRING类是支持迭代器的*/



    /*todo ============================STRING的使用End================================*/

    /*todo ============================vector的使用===================================*/




    /*todo ============================vector的使用End================================*/
    /*todo ============================map的使用======================================*/




    /*todo ============================map的使用End===================================*/
    /*todo ============================array的使用====================================*/




    /*todo ============================array的使用End================================*/
private :
     bool _isEnd;
     const char * Msg;
     size_t len;
     std::unique_ptr<Student> _upStu; // todo 智能指针的构造函数不会去创建对象，而是初始化一个空指针 会不会调用构造函数在于会不会创建相应的资源（包含结构体，以及对象）
     std::shared_ptr<Student> _usharedpStu;
};
//todo 字面量的理解+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static NodeP operator""_tb(const char *pc,size_t len)
{
    return{pc,len};
}
//todo 字面量的理解+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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
    NodeP *RootNode;
    std::array<NodeP*,5>NodeArray; //todo:不会调用构造函数，但是他在给Node初始化的时候也会调用构造函数
    std::array<NodeP,5>NodeArray2; //todo:会调用默认构造函数
};
//todo 字面量运算符

#endif //UNTITLED21_PROBLEM_H
