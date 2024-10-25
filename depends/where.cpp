//
// Created by 请输入我的名字 on 2024/10/25.
//
#include "where.h"
#include <mutex>
#include <array>
#define WHERE_NUM 128
static std::array<T_WHERE,WHERE_NUM> s_atWhere {nullptr, nullptr,0};
static __thread  t_where s_gWhere;
static  t_where s_where;
static std::mutex s_where_lock;
t_where generate_whereId(PT_char file,t_u32 line,PT_char func ,PT_char what, pt_any callback)
{

    {
        std::lock_guard<std::mutex> lock(s_where_lock);
        if(s_where == WHERE_NUM-1)
        {
            s_where = 0;
        }
        else
            s_where ++;
    }
    s_atWhere[s_where].file = file;
    s_atWhere[s_where].line = line;
    s_atWhere[s_where].func = func;
    s_atWhere[s_where].what = what;
    s_atWhere[s_where].callback = callback;
    s_gWhere = s_where;
    return s_gWhere;
}

t_where get_thread_where()
{
    return s_gWhere;
}