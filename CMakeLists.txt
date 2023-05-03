cmake_minimum_required(VERSION 3.0)
project(sylar_dchg) 

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
# include (cmake/utils.cmake)
# utils.cmake里定义了sylar_add_execuable

set(CMAKE_VERBOSE_MAKEFILE ON)
# set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -fPIC -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -fPIC -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")

# # source dir
# aux_source_directory(${PROJECT_SOURCE_DIR}/sylar_dchg SRC)
# # include path
# include_directories(${PROJECT_SOURCE_DIR}/sylar_dchg)
# include_directories(.)

# set(LIB_SRC
#     sylar_dchg/config.cc
#     sylar_dchg/env.cc
#     sylar_dchg/fiber.cc
#     sylar_dchg/log.cc
#     sylar_dchg/mutex.cc
#     sylar_dchg/thread.cc
#     sylar_dchg/util.cc
#     )
find_library(YAMLCPP yaml-cpp)
set(LIB_SRC
    sylar_dchg/log.cc
    )
add_library(sylar_dchg SHARED ${LIB_SRC}) #这是生成共享库

add_executable(test tests/test.cc)
add_dependencies(test sylar_dchg)#test是要生成的 sylar_dchg是其依赖的库
target_link_libraries(test sylar_dchg yaml-cpp)#链接

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)