//
// Created by 请输入我的名字 on 2024/10/22.
//

#ifndef UNTITLED21_DEBUG_H
#define UNTITLED21_DEBUG_H
#include "exception.h"
#include "mutex"
#define EASY_DEBUG(problem)
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
problem & newProblem()
{
    debug_and_reset_problem();
    std::lock_guard<std::mutex> lockGuard(st_mutex);
    problem & _problem = st_problems.next_step();
    st_problem = &_problem;
    return _problem;
}
#endif //UNTITLED21_DEBUG_H
