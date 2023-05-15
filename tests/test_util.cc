#include "sylar_dchg/sylar.h"
#include <assert.h>

sylar_dchg::Logger::ptr g_logger = SYLAR_DCHG_LOG_ROOT();

void test_assert() {
    SYLAR_DCHG_LOG_INFO(g_logger) << sylar_dchg::BacktraceToString(10);
    //SYLAR_DCHG_ASSERT2(0 == 1, "abcdef xx");
}

int main(int argc, char** argv) {
    test_assert();

    int arr[] = {1,3,5,7,9,11};

    SYLAR_DCHG_LOG_INFO(g_logger) << sylar_dchg::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 0);
    SYLAR_DCHG_LOG_INFO(g_logger) << sylar_dchg::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 1);
    SYLAR_DCHG_LOG_INFO(g_logger) << sylar_dchg::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 4);
    SYLAR_DCHG_LOG_INFO(g_logger) << sylar_dchg::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 13);
    SYLAR_DCHG_ASSERT(sylar_dchg::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 0) == -1);
    SYLAR_DCHG_ASSERT(sylar_dchg::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 1) == 0);
    SYLAR_DCHG_ASSERT(sylar_dchg::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 2) == -2);
    SYLAR_DCHG_ASSERT(sylar_dchg::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 3) == 1);
    SYLAR_DCHG_ASSERT(sylar_dchg::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 4) == -3);
    SYLAR_DCHG_ASSERT(sylar_dchg::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 5) == 2);
    SYLAR_DCHG_ASSERT(sylar_dchg::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 6) == -4);
    SYLAR_DCHG_ASSERT(sylar_dchg::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 7) == 3);
    SYLAR_DCHG_ASSERT(sylar_dchg::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 8) == -5);
    SYLAR_DCHG_ASSERT(sylar_dchg::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 9) == 4);
    SYLAR_DCHG_ASSERT(sylar_dchg::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 10) == -6);
    SYLAR_DCHG_ASSERT(sylar_dchg::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 11) == 5);
    SYLAR_DCHG_ASSERT(sylar_dchg::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 12) == -7);
    return 0;
}
