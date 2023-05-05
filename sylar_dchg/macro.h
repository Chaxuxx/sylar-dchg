/**
 * @file macro.h
 * @brief 常用宏的封装
 * @author sylar_DCHG.yin
 * @email 564628276@qq.com
 * @date 2019-06-01
 * @copyright Copyright (c) 2019年 sylar_DCHG.yin All rights reserved (www.sylar_DCHG.top)
 */
#ifndef __SYLAR_DCHG_MACRO_H__
#define __SYLAR_DCHG_MACRO_H__

#include <string.h>
#include <assert.h>
#include "log.h"
#include "util.h"

#if defined __GNUC__ || defined __llvm__
/// LIKCLY 宏的封装, 告诉编译器优化,条件大概率成立
#   define SYLAR_DCHG_LIKELY(x)       __builtin_expect(!!(x), 1)
/// LIKCLY 宏的封装, 告诉编译器优化,条件大概率不成立
#   define SYLAR_DCHG_UNLIKELY(x)     __builtin_expect(!!(x), 0)
#else
#   define SYLAR_DCHG_LIKELY(x)      (x)
#   define SYLAR_DCHG_UNLIKELY(x)      (x)
#endif

/// 断言宏封装
#define SYLAR_DCHG_ASSERT(x) \
    if(SYLAR_DCHG_UNLIKELY(!(x))) { \
        SYLAR_DCHG_LOG_ERROR(SYLAR_DCHG_LOG_ROOT()) << "ASSERTION: " #x \
            << "\nbacktrace:\n" \
            << sylar_dchg::BacktraceToString(100, 2, "    "); \
        assert(x); \
    }

/// 断言宏封装
#define SYLAR_DCHG_ASSERT2(x, w) \
    if(SYLAR_DCHG_UNLIKELY(!(x))) { \
        SYLAR_DCHG_LOG_ERROR(SYLAR_DCHG_LOG_ROOT()) << "ASSERTION: " #x \
            << "\n" << w \
            << "\nbacktrace:\n" \
            << sylar_dchg::BacktraceToString(100, 2, "    "); \
        assert(x); \
    }

#endif
