#include "../sylar_dchg/socket.h"
#include "../sylar_dchg/sylar.h"
#include "../sylar_dchg/iomanager.h"

static sylar_dchg::Logger::ptr g_looger = SYLAR_DCHG_LOG_ROOT();

void test_socket() {
    //std::vector<sylar_dchg::Address::ptr> addrs;
    //sylar_dchg::Address::Lookup(addrs, "www.baidu.com", AF_INET);
    //sylar_dchg::IPAddress::ptr addr;
    //for(auto& i : addrs) {
    //    SYLAR_DCHG_LOG_INFO(g_looger) << i->toString();
    //    addr = std::dynamic_pointer_cast<sylar_dchg::IPAddress>(i);
    //    if(addr) {
    //        break;
    //    }
    //}
    sylar_dchg::IPAddress::ptr addr = sylar_dchg::Address::LookupAnyIPAddress("www.baidu.com");//测试TCP链接
    if(addr) {
        SYLAR_DCHG_LOG_INFO(g_looger) << "get address: " << addr->toString();
    } else {
        SYLAR_DCHG_LOG_ERROR(g_looger) << "get address fail";
        return;
    }

    sylar_dchg::Socket::ptr sock = sylar_dchg::Socket::CreateTCP(addr);
    addr->setPort(80);
    SYLAR_DCHG_LOG_INFO(g_looger) << "addr=" << addr->toString();
    if(!sock->connect(addr)) {
        SYLAR_DCHG_LOG_ERROR(g_looger) << "connect " << addr->toString() << " fail";
        return;
    } else {
        SYLAR_DCHG_LOG_INFO(g_looger) << "connect " << addr->toString() << " connected";
    }

    const char buff[] = "GET / HTTP/1.0\r\n\r\n";
    int rt = sock->send(buff, sizeof(buff));
    if(rt <= 0) {
        SYLAR_DCHG_LOG_INFO(g_looger) << "send fail rt=" << rt;
        return;
    }

    std::string buffs;
    buffs.resize(4096);
    rt = sock->recv(&buffs[0], buffs.size());

    if(rt <= 0) {
        SYLAR_DCHG_LOG_INFO(g_looger) << "recv fail rt=" << rt;
        return;
    }

    buffs.resize(rt);
    SYLAR_DCHG_LOG_INFO(g_looger) << buffs;//将获取到的内容输出
}

void test2() {
    sylar_dchg::IPAddress::ptr addr = sylar_dchg::Address::LookupAnyIPAddress("www.baidu.com:80");
    if(addr) {
        SYLAR_DCHG_LOG_INFO(g_looger) << "get address: " << addr->toString();
    } else {
        SYLAR_DCHG_LOG_ERROR(g_looger) << "get address fail";
        return;
    }

    sylar_dchg::Socket::ptr sock = sylar_dchg::Socket::CreateTCP(addr);
    if(!sock->connect(addr)) {
        SYLAR_DCHG_LOG_ERROR(g_looger) << "connect " << addr->toString() << " fail";
        return;
    } else {
        SYLAR_DCHG_LOG_INFO(g_looger) << "connect " << addr->toString() << " connected";
    }

    uint64_t ts = sylar_dchg::GetCurrentUS();
    for(size_t i = 0; i < 10000000000ul; ++i) {
        if(int err = sock->getError()) {
            SYLAR_DCHG_LOG_INFO(g_looger) << "err=" << err << " errstr=" << strerror(err);
            break;
        }

        //struct tcp_info tcp_info;
        //if(!sock->getOption(IPPROTO_TCP, TCP_INFO, tcp_info)) {
        //    SYLAR_DCHG_LOG_INFO(g_looger) << "err";
        //    break;
        //}
        //if(tcp_info.tcpi_state != TCP_ESTABLISHED) {
        //    SYLAR_DCHG_LOG_INFO(g_looger)
        //            << " state=" << (int)tcp_info.tcpi_state;
        //    break;
        //}
        static int batch = 10000000;
        if(i && (i % batch) == 0) {
            uint64_t ts2 = sylar_dchg::GetCurrentUS();
            SYLAR_DCHG_LOG_INFO(g_looger) << "i=" << i << " used: " << ((ts2 - ts) * 1.0 / batch) << " us";
            ts = ts2;
        }
    }
}

int main(int argc, char** argv) {
    sylar_dchg::IOManager iom;
    //iom.schedule(&test_socket);
    iom.schedule(&test2);
    return 0;
}
