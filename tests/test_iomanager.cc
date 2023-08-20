#include "../sylar_dchg/sylar.h"
#include "../sylar_dchg/iomanager.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <sys/epoll.h>

sylar_dchg::Logger::ptr g_logger = SYLAR_DCHG_LOG_ROOT();

int sock = 0;

void test_fiber() {
    SYLAR_DCHG_LOG_INFO(g_logger) << "test_fiber sock=" << sock;

    //sleep(3);

    //close(sock);
    //sylar_dchg::IOManager::GetThis()->cancelAll(sock);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(sock, F_SETFL, O_NONBLOCK);

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    inet_pton(AF_INET, "115.239.210.27", &addr.sin_addr.s_addr);

    if(!connect(sock, (const sockaddr*)&addr, sizeof(addr))) {
    } else if(errno == EINPROGRESS) {
        SYLAR_DCHG_LOG_INFO(g_logger) << "add event errno=" << errno << " " << strerror(errno);
        sylar_dchg::IOManager::GetThis()->addEvent(sock, sylar_dchg::IOManager::READ, [](){
            SYLAR_DCHG_LOG_INFO(g_logger) << "read callback";
        });
        sylar_dchg::IOManager::GetThis()->addEvent(sock, sylar_dchg::IOManager::WRITE, [](){
            SYLAR_DCHG_LOG_INFO(g_logger) << "write callback";
            //close(sock);
            sylar_dchg::IOManager::GetThis()->cancelEvent(sock, sylar_dchg::IOManager::READ);
            close(sock);
        });
    } else {
        SYLAR_DCHG_LOG_INFO(g_logger) << "else " << errno << " " << strerror(errno);
    }

}

void test1() {
    std::cout << "EPOLLIN=" << EPOLLIN
              << " EPOLLOUT=" << EPOLLOUT << std::endl;
    sylar_dchg::IOManager iom(2, false);
    iom.schedule(&test_fiber);
}

sylar_dchg::Timer::ptr s_timer;
void test_timer() {
    sylar_dchg::IOManager iom(2);
    s_timer = iom.addTimer(1000, [](){
        static int i = 0;
        SYLAR_DCHG_LOG_INFO(g_logger) << "hello timer i=" << i;
        if(++i == 3) {
            s_timer->reset(2000, true);
            //s_timer->cancel();
        }
    }, true);
}

int main(int argc, char** argv) {
    //test1();
    test_timer();
    return 0;
}
