/**
 * @file singleton.h
 * @brief 单例模式封装 基本头文件
 * @author sylar.yin
 * @email 564628276@qq.com
 * @date 2019-05-18
 * @copyright Copyright (c) 2019年 sylar.yin All rights reserved (www.sylar.top)
 */
#ifndef __SYLAR_DCHG_SINGLETON_H__
#define __SYLAR_DCHG_SINGLETON_H__

#include <memory>

namespace sylar_dchg {

namespace {

template<class T, class X, int N>
T& GetInstanceX() {
    static T v;
    return v;
}

template<class T, class X, int N>
std::shared_ptr<T> GetInstancePtr() {
    static std::shared_ptr<T> v(new T);
    return v;
}


}

/**
 * @brief 单例模式封装类
 * @details T 类型
 *          X 为了创造多个实例对应的Tag
 *          N 同一个Tag创造多个实例索引
 */
template<class T, class X = void, int N = 0>
class Singleton {
public:
    /**
     * @brief 返回单例裸指针
     */
    static T* GetInstance() {//通过类直接调用静态成员函数 而不是对象
        static T v; //静态变量只会被初始化一次。 仅仅是使用static的话，单写一个singleton类的意义何在呢？  几个管理类都是单例
        return &v;//静态变量局部与否仅仅影响可见性，生命周期都是整个程序运行期间。这样声明定义局部静态变量，在调用函数时也只会初始化一次，后面不会再进行初始化。
        //由于是main运行前就进行几个管理器的单例初始化，所以不需要考虑线程安全。
        //return &GetInstanceX<T, X, N>();上面两个函数好像毫无意义 可删？
    }
};

/**
 * @brief 单例模式智能指针封装类
 * @details T 类型
 *          X 为了创造多个实例对应的Tag
 *          N 同一个Tag创造多个实例索引
 */
template<class T, class X = void, int N = 0>
class SingletonPtr {
public:
    /**
     * @brief 返回单例智能指针
     */
    static std::shared_ptr<T> GetInstance() {
        static std::shared_ptr<T> v(new T);
        return v;
        //return GetInstancePtr<T, X, N>();
    }
};

}

#endif
