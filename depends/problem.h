//
// Created by 请输入我的名字 on 2024/9/9.
//

#ifndef UNTITLED21_PROBLEM_H
#define UNTITLED21_PROBLEM_H
#include <string>
#include <string_view>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <map>
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
    Student(char *a)
    {

    }

    Student(int a)
    {

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
    void useofString()
    {
        //todo 基本初始化以及用法
        std::string str; /*todo 初始化为一个空字符串*/
        std::cout<<str<<"空串"<<std::endl;

        std::string str1("china"); /*todo 初始化为一个chia的字符串*/
        std::cout<<str1<<"初始化为c风格的字符串"<<std::endl;

        std::string str2(str1); /*todo 拷贝构造*/
        std::cout<<str2<<"拷贝构造"<<std::endl;

        std::string str3(3,'w'); /*todo 重复字符串初始化*/
        std::cout<<str3<<"重复字符初始化"<<std::endl;

        std::string str4= (str1)+str2 +str3; /*todo 字符串拼接*/
        std::cout<<str4<<"字符串拼接"<<std::endl;

        //todo 基本操作
        std::cout<<str4.empty()<<":是否empty"<<std::endl;
        std::cout<<str4.size()<<":size长度"<<std::endl;
        std::cout<<str4.length()<<":length长度"<<std::endl;
        std::cout<<str4[1]<<":获取str4[1]"<<std::endl;
        str3.clear();//todo 清空字符
        str4.erase(5,2);//todo 可以通过迭代器删除也可以通过指定位置删除 从第五个字符开始删除2个字符串
        auto it = str4.begin()+2;
        str4.erase(it,it+3);//todo 删除从迭代器指向的开始位置到后面的三个元素
        str4.erase(it);//todo 删除从迭代器指向的开始位置到最后
        str4.insert(2,"s"); //todo 从位置2插入字符串”s“
        str4.append("use");//todo 追加字符串
        auto substr = str4.substr(3);//todo 从第三个位置获取子串
        if(str4.find("china") == std::string::npos) //todo find返回的一个china这个字符串的首次位置(如果找到的话)pos，没有找到的话，pos == npos.
        {
            std::cout<<"cant find "<<std::endl;
        }
        str4.find("china",5);//todo 从第五个位置开始查
        str4.find('2',5);//todo 查字符
        //todo 转为c风格的字符指针
        const char* cstr = str4.c_str();
        std::cout<<"c style string "<<cstr<<std::endl;

        //todo 使用比较运算符 ==, !=, <, >, <=, >=
        //todo 使用基础的loop遍历
        for(auto & ch : str4)
        {
            std::cout<<ch <<std::endl;
        }
        //todo 使用迭代器遍历遍历
        for(auto itor = str4.begin();itor != str4.end();itor++)
        {
            std::cout<<*itor<<std::endl;
        }
        // todo 替代字符串
        str4.replace(3,6,"hello");//todo 从位置3开始替换6个字符为hello

        //todo test
        std::string uri("https://172.20.140.103/imsi-46011123456789/uepolicy/1425");
        if(uri.find("https://") == std::string::npos)
        {
            std::cout<<"bad uri"<<std::endl;
            return;
        }
        auto authoritytemp = uri.substr(uri.find("https://")+8);
        auto authority  = authoritytemp.substr(0,authoritytemp.find('/'));
        std::cout<<"authority is "<<authority<<std::endl;
    }
    /*todo ============================STRING的使用End================================*/

    /*todo ============================vector的使用===================================*/
    void studyvector()
    {
        char a = 10;
        std::vector<Student> vec(10,&a); //todo 调用Student的入参是char* 创建10个对象
        std::vector<int> vec3(5, 10); //todo 指定5个值为10的元素
        std::vector<int> _vec2 = {1,3}; //todo 初始化
        vec3.push_back(2);//todo 向末尾增加元素
        vec3.pop_back();//todo 向末尾删除元素
        vec3.size();//todo 获取向量的大小
        vec3.capacity();//todo 获取向量的容量大小
        vec3.resize(10);//todo 重新调整容量大小，如果小于之前的容量则将多余的删除
        std::vector<Student> __vec;
        __vec.resize(3, Student(42)); //todo 创建 3 个 Student 对象，id 为 42
        if(vec3.empty()) //todo 判空
        {
            std::cout<<"vec is empty"<<std::endl;
        }
        vec3.clear();// todo 清空所有元素
        vec3.insert(vec3.begin(),3); //todo 在第一的位置插入3
        vec3.insert(vec3.begin()+2,3); //todo 在第2的位置插入3
        vec3.erase(vec3.begin()+2); //todo 删除第二个元素 如果类型是对象，则会调用相应的类的析构函数
        vec3.erase(vec3.begin()+2,vec3.begin()+3); //todo 删除第二个元素 如果类型是对象，则会调用相应的类的析构函数
        vec.emplace_back(10);//todo emplace_back 在容器内部直接构造对象，避免了构造临时对象并拷贝或移动到容器的过程。用于在容器的末尾直接构造对象。
        // todo 它与 push_back 的主要区别在于，emplace_back 可以避免不必要的临时对象创建和拷贝或移动操作，从而提高性能。pushback是已经存在的一个对象push进去
        std::sort(vec.begin(),vec.end(),[](Student &stu1 ,Student &stu2)->bool //todo vector自定义lamda表达式进行排序
        {
          return stu1.age>stu2.age;
        });
        auto front = vec.front();// todo 返回第一个元素
        auto back = vec.back();// todo 返回最后一个元素
        //todo 遍历 基础遍历
        for(auto & num : vec3)
        {
            std::cout<<"num "<< num<<std::endl;
        }
        for(auto num = vec3.begin();num !=vec3.end();num++ ) //todo auto & num = vec3.begin()是错误的，因为vec3.begin() 返回的是一个临时对象（即一个迭代器）。对临时对象使用引用是错误的，因为它会在定义后立即被销毁
        {
            std::cout<<"itor num "<< *num<<std::endl;
        }
        // todo swap的用法
        vec3.swap(vec3);//todo 能够将size 和 capacity调整到当前的大小，如果一个向量删除了很多元素的情况
        vec3.shrink_to_fit();// todo 和上面的swap交换自己功能类似
        //todo  find的用法 ,同样也支持查找函数，lambada表达式，以及仿函数作为查找的方式
        auto it = std::find(vec3.begin(), vec3.end(), 3);//todo find只能查找特定的大于某个值的元素
        // todo 用于查找第一个满足特定条件（谓词）的元素。
        // todo 谓词是一个返回 bool 类型的函数或者 lambda 表达式。
       // todo 返回值与 find 类似，找到匹配元素则返回指向该元素的迭代器，否则返回指向容器末尾的迭代器。
        auto i1t = std::find_if(vec3.begin(), vec3.end(), [](int &a)
        {
            return a > 4;
            // todo 用于查找第一个满足特定条件（谓词）的元素。
        });

        if(it != vec3.end())
        {
            std::cout<<"find success"<<std::endl;
        }
    }
    /*todo ============================vector的使用End================================*/


    /*todo ============================map的使用======================================*/
    void studymap()
    {
        std::map<int,std::string> _map ={{1,"china"},{2,"japan"}};
        //todo 插入元素
        _map[2] = "USE";
        _map.insert({4,"key"}); //
        _map.emplace(5,"hello"); //todo 使用 emplace(): 避免不必要的拷贝。和insert类似
        //todo 访问元素
        std::string str = _map[1];_map.at(1);//todo at如果key不存在，不会插入新的元素，会抛出异常，而【】不会抛出异常,会插入新的元素，在本例子中会增加该键，value是空串
        //todo find查找元素
        try{
            auto str = _map.at(30);
        }
        catch (const std::out_of_range &exception)
        {
            std::cout<<"exception is "<<exception.what()<<std::endl;
            return ;
        }
        //todo 查找键为3的元素
        auto result = _map.find(3);
        if(result == _map.end())
        {
            std::cout<<"cant find"<<std::endl;
        }
        //todo 检查键3是否存在 存在返回TRUE,不存在返回FALSE
        if(_map.count(3))
        {
            std::cout<<"_map.count have find"<<std::endl;
        }
        // todo 删除
        _map.erase(1);//todo 按照键值对进行删除
        //todo 查找
       auto it=  _map.find(1);
       if(it != _map.end())
       {
           std::cout<<"find"<<it->second<< std::endl;
       }
       //todo 遍历
       for(auto & pair : _map)
       {
           std::cout<<"loop "<<pair.first<<pair.second<<std::endl;
       }
       //todo 迭代器遍历
       for(auto pair = _map.begin();pair != _map.end();pair++)
       {
           std::cout<<"loop "<<pair->first<<pair->first<<std::endl;
       }
       //todo 清空
       _map.clear();
       //todo 自定义排序
        struct DescendingOrder {
            bool operator()(int a, int b) const {
                return a > b;
            }
            bool operator()(std::string a, std::string b) const {
                return a > b;
            }
        };

        //todo 只会使用key类型排序
        std::map<int, std::string, DescendingOrder> descendingMap;
        descendingMap[1] = "one";
        descendingMap[2] = "two";
    }
    /* todo ============================map的使用End===================================*/
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
        //RootNode = new NodeP; // todo :错误没有合适的构造函数。
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
