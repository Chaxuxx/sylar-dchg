cmake_minimum_required(VERSION 3.0)
project(sylar_dchg) 

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include (cmake/utils.cmake)#这个文件是哪儿来的 未知
# utils.cmake里定义了sylar_add_execuable

set(CMAKE_VERBOSE_MAKEFILE ON)
# set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -fPIC -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -fPIC -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")
# 有一个宏重定义的忽略

# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif()

find_package(ZLIB REQUIRED)
if(ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIR})
endif()

# set(LIB_SRC
#     sylar_dchg/config.cc
#     sylar_dchg/env.cc
#     sylar_dchg/fiber.cc
#     sylar_dchg/log.cc
#     sylar_dchg/mutex.cc
#     sylar_dchg/thread.cc
#     sylar_dchg/util.cc
#     )
# find_library(yamlcpp libyamlcpp.a)
# find_library(YAMLCPP yaml-cpp)
set(LIB_SRC
    sylar_dchg/log.cc
    sylar_dchg/util.cc
    sylar_dchg/config.cc
    sylar_dchg/thread.cc
    sylar_dchg/mutex.cc
    sylar_dchg/address.cc
    sylar_dchg/bytearray.cc
    sylar_dchg/fd_manager.cc
    sylar_dchg/address.cc
    sylar_dchg/bytearray.cc
    sylar_dchg/fd_manager.cc
    sylar_dchg/fiber.cc
    sylar_dchg/hook.cc
    sylar_dchg/iomanager.cc
    sylar_dchg/log.cc
    sylar_dchg/mutex.cc
    sylar_dchg/scheduler.cc
    sylar_dchg/socket.cc
    sylar_dchg/stream.cc
    sylar_dchg/tcp_server.cc
    sylar_dchg/timer.cc
    sylar_dchg/thread.cc
    sylar_dchg/util.cc
    sylar_dchg/env.cc

    sylar_dchg/http/http.cc
    sylar_dchg/http/http_connection.cc
    sylar_dchg/http/http_parser.cc
    sylar_dchg/http/http_session.cc
    sylar_dchg/http/http_server.cc
    sylar_dchg/http/servlet.cc
    sylar_dchg/http/servlets/config_servlet.cc
    sylar_dchg/http/servlets/status_servlet.cc

    sylar_dchg/streams/socket_stream.cc
    sylar_dchg/streams/zlib_stream.cc
    )

#ragel生成高效解析http报文的源码
ragelmaker(sylar_dchg/http/http11_parser.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/sylar_dchg/http)
ragelmaker(sylar_dchg/http/httpclient_parser.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/sylar_dchg/http)
ragelmaker(sylar_dchg/uri.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/sylar_dchg)

add_library(sylar_dchg SHARED ${LIB_SRC}) #这是生成共享库 库名为sylar_dchg
force_redefine_file_macro_for_sources(sylar_dchg) #这样更改__FILE__的位置为相对路径而不是绝对路径 加上上面的utils.cmake文件

#设置别名 包括一系列需要链接的库 
set(LIBS
        sylar_dchg
        pthread
        yaml-cpp
        ${ZLIB_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        
        )
    
# add_executable(test tests/test.cc)
# add_dependencies(test sylar_dchg)#test是要生成的 sylar_dchg是其依赖的库
# force_redefine_file_macro_for_sources(test)
# target_link_libraries(test sylar_dchg -lyaml-cpp -lpthread)#链接  可以直接用参数啦

add_executable(test tests/test.cc)
add_dependencies(test sylar_dchg)
force_redefine_file_macro_for_sources(test)
target_link_libraries(test ${LIBS})#链接使用别名

# add_executable(test_config tests/test_config.cc)
# add_dependencies(test_config sylar_dchg)#test_config是要生成的 sylar_dchg是其依赖的库
# force_redefine_file_macro_for_sources(test_config)
# target_link_libraries(test_config sylar_dchg -lyaml-cpp)#链接

add_executable(test_tcpserver tests/test_tcp_server.cc)
add_dependencies(test_tcpserver sylar_dchg)
force_redefine_file_macro_for_sources(test_tcpserver)
target_link_libraries(test_tcpserver ${LIBS})

add_executable(echoserver examples/echo_server.cc)
add_dependencies(echoserver sylar_dchg)
force_redefine_file_macro_for_sources(echoserver)
target_link_libraries(echoserver ${LIBS})

add_executable(test_httpserver tests/test_http_server.cc)
add_dependencies(test_httpserver sylar_dchg)
force_redefine_file_macro_for_sources(test_httpserver)
target_link_libraries(test_httpserver ${LIBS})

add_executable(httpserver samples/my_http_server.cc)
add_dependencies(httpserver sylar_dchg)
force_redefine_file_macro_for_sources(httpserver)
target_link_libraries(httpserver ${LIBS})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)#二进制文件存放位置设置
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)#lib存放位置设置