cmake_minimum_required(VERSION 3.0)
project(sylar_dchg) 

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
# include (cmake/utils.cmake)
# utils.cmake里定义了sylar_add_execuable

# source dir
aux_source_directory(${PROJECT_SOURCE_DIR}/sylar_dchg SRC)
# include path
include_directories(${PROJECT_SOURCE_DIR}/sylar_dchg)
include_directories(.)

# set(LIB_SRC
#     sylar_dchg/config.cc
#     sylar_dchg/env.cc
#     sylar_dchg/fiber.cc
#     sylar_dchg/log.cc
#     sylar_dchg/mutex.cc
#     sylar_dchg/thread.cc
#     sylar_dchg/util.cc
    
    
#     )
set(LIB_SRC
    sylar_dchg/thread.cc    
    sylar_dchg/log.cc
    sylar_dchg/util.cc
    
    
    )
add_library(sylar_dchg SHARED ${LIB_SRC}) #这是生成共享库

add_executable(test_log tests/test.cc sylar_dchg)
target_link_libraries(test_log sylar_dchg)