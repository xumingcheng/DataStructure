//
// Created by 请输入我的名字 on 2024/10/25.
//

#ifndef UNTITLED21_WHERE_H
#define UNTITLED21_WHERE_H
#include "base_debug.h"
typedef struct {
    pT_char file;
    pT_char func;
    t_u32   line;
    pT_char what;
    pt_any  callback;
}T_WHERE;
t_where generate_whereId(PT_char file,t_u32 line,PT_char func ,PT_char what, pt_any callback);
t_where get_thread_where();
#endif //UNTITLED21_WHERE_H
