//
// Created by 请输入我的名字 on 2024/10/8.
//

#ifndef UNTITLED21_3GPP_38413_H
#define UNTITLED21_3GPP_38413_H
/*todo :PDU Session Resource Notify*/
#include "where.h"
#define STAT_INVALID_WHERE 0xffff
#define CPP_LIKELY(x) __builtin_expect(!!(x), 1) /*像 __builtin_expect 这样的工具可以帮助编译器进行优化。
 * 当你告诉编译器某个条件很可能为真时，编译器可能会重排代码或生成更高效的指令，以期在大多数情况下提高执行速度。*/
#define PASS
#define CPP_VNAME(x) (#x)
class OnceStr {
    std::string s;
public:
    pT_char data() {
        return s.data();
    };

    OnceStr(bool v) {
        if (v) {
            s = "true";
        } else {
            s = "false";
        }
    }

    OnceStr(t_u8 v) {
        // 255
        char temp[4];
        snprintf(temp, 4, "%u", v);
        s = temp;
    }

    OnceStr(t_u16 v) {
        // 6'5535
        char temp[6];
        snprintf(temp, 6, "%u", v);
        s = temp;
    }

    OnceStr(t_u32 v) {
        // 42'9496'7295
        char temp[11];
        snprintf(temp, 11, "%u", v);
        s = temp;
    }

    OnceStr(t_u64 v) {
        // 1844'6744'0737'0955'1615
        char temp[21];

        if (v <= 4294967295) {
            snprintf(temp, 21, "%llu", v);
        } else {

            snprintf(temp, 21, "0x%llx", v);
        }
        s = temp;
    }

    OnceStr(t_s8 v) {
        // -128 ~ 127
        char temp[5];
        snprintf(temp, 5, "%d", v);
        s = temp;
    }

    OnceStr(t_s16 v) {
        char temp[8];
        snprintf(temp, 8, "%d", v);
        s = temp;
    }

    OnceStr(t_s32 v) {
        char temp[16];
        snprintf(temp, 16, "%d", v);
        s = temp;
    }

    OnceStr(t_s64 v) {
        char temp[24];
        snprintf(temp, 24, "%lld", v);
        s = temp;
    }

    OnceStr(t_size v) {
        char temp[24];
        snprintf(temp, 24, "%zu", v);
        s = temp;
    }

    OnceStr(double v) {
        char temp[128];
        snprintf(temp, 128, "%lf", v);
        s = temp;
    }

    OnceStr(pT_any v) {
        char temp[24];
        snprintf(temp, 24, "%p", v);
        s = temp;
    }

    OnceStr(pT_char v) {
        if (v) {
            s = v;
        } else {
            s = "(null)";
        }
    }

    OnceStr(std::string& v) {
        s = v;
    }

    OnceStr(std::nullptr_t& v) {
        s = "(nullptr)";
    }

    template <typename T>
    OnceStr(T& v) {
        char temp[24];
        switch (sizeof(T)) {
            // sizeof(enum class) == 4
            case 4: {
                t_u32 v32 = *(t_u32*)&v;
                snprintf(temp, 24, "%u(v)", v32);
                break;
            }
            case 8: {
                t_u64 v64 = *(t_u64*)&v;
                if (v64 <= 4294967295) {
                    snprintf(temp, 24, "%llu(v)", v64);
                } else {
                    snprintf(temp, 24, "0x%llx(v)", v64);
                }
                break;
            }
            default:
                snprintf(temp, 24, "%p(%%p)", &v);
                break;
        }
        s = temp;
    }
};
#define WHERE_(what) \
    ({\
        static t_where where = STAT_INVALID_WHERE;\
        if (where == STAT_INVALID_WHERE) {\
            where = generate_whereId(__FILE__, __LINE__, __FUNCTION__, what, nullptr);\
        }\
        where;\
    })
#define CHECK_VALUE(v1, op, v2)\
do{                            \
    decltype (v1) V1_VALUE = v1;\
    decltype (v2) V2_VALUE = v2;\
    if(CPP_LIKELY(v1 op v2) )\
    {\
         PASS\
    }else                      \
   {                           \
          throw newProblem(WHERE_(""), "check for %s(%s) %s %s(%s) failed",\
                             CPP_VNAME(v1), OnceStr(V1_VALUE).data(),\
                             CPP_VNAME(op),\
                             CPP_VNAME(v2), OnceStr(V2_VALUE).data()) ;  \
   }\
}while(0);

#endif //UNTITLED21_3GPP_38413_H
