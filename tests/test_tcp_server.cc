#include "../sylar_dchg/tcp_server.h"
#include "../sylar_dchg/iomanager.h"
#include "../sylar_dchg/log.h"

sylar_dchg::Logger::ptr g_logger = SYLAR_DCHG_LOG_ROOT();

void run() {
    auto addr = sylar_dchg::Address::LookupAny("0.0.0.0:8033");
    //auto addr2 = sylar_dchg::UnixAddress::ptr(new sylar_dchg::UnixAddress("/tmp/unix_addr"));
    std::vector<sylar_dchg::Address::ptr> addrs;
    addrs.push_back(addr);
    //addrs.push_back(addr2);

    sylar_dchg::TcpServer::ptr tcp_server(new sylar_dchg::TcpServer);
    std::vector<sylar_dchg::Address::ptr> fails;
    while(!tcp_server->bind(addrs, fails)) {
        sleep(2);
    }
    tcp_server->start();
    
}
int main(int argc, char** argv) {
    sylar_dchg::IOManager iom(2);
    iom.schedule(run);
    return 0;
}
