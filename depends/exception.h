//
// Created by 请输入我的名字 on 2024/9/25.
//

#ifndef UNTITLED21_EXCEPTION_H
#define UNTITLED21_EXCEPTION_H
#include <vector>
#include <string>
#include <base_debug.h>
template<typename T>
class oncestr
{
private:
    char *Data = nullptr;

};
class problem
{
private:
    t_who who;
    t_when when;
    t_why why;
    t_where where;

public :
    void debug();
    void init();
};
template<typename T>
class cycle{
private:
    int __total;
    int __next;
    std::vector<T> __element;
public:
    cycle(int num)
    {
        __element.resize(num);
    }
    T & next_step()
    {

        if(__next > get_size()-1  )
        {
            __next = 0;
            return __element[__next];
        }
        else
        {
            T & t= __element[__next];
            __next++;
            return t;
        }
    }
    T & operator[](size_t index)
    {
        return __element.at(index);
    }
    size_t get_size()
    {
        return __element.size();
    }
};
void problem::debug() {

}

#endif //UNTITLED21_EXCEPTION_H
