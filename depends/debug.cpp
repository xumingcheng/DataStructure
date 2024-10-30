//
// Created by 请输入我的名字 on 2024/10/25.
//

#include "exception.h"
#include "mutex"
#include "stdarg.h"
#define EASY_DEBUG(problem)\
do{\
    \
}while(0)

static cycle<problem> st_problems(128);
static __thread problem *st_problem = nullptr;
static std::mutex st_mutex;
problem *get_latest_problem()
{
    return st_problem;
}
void debug_and_reset_problem()
{
    problem *_problem = get_latest_problem();
    if(_problem)
    {
        EASY_DEBUG(_problem);
        _problem = nullptr;
    }

}
#define STAT_PARSE(format)\
do{\
    va_list va_arg;       \
    va_start(va_arg,format); \
    snprintf(STAT_BUF,100,format,va_arg); \
    va_end(va_arg);\
}while(0)
#define STAT_PARSE2(format,...)\
do{\
    snprintf(STAT_BUF,100,format,##__VA_ARGS__); \
}while(0)
problem & newProblem(t_where where ,pT_char format ,...)
{
    char STAT_BUF[100] = {0};

    debug_and_reset_problem();
    STAT_PARSE(format);
    STAT_PARSE2(format);
    std::lock_guard<std::mutex> lockGuard(st_mutex);
    problem & _problem = st_problems.next_step();
    _problem.init();
    st_problem = &_problem;
    return _problem;
}
