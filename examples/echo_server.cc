#include "../sylar_dchg/tcp_server.h"
#include "../sylar_dchg/log.h"
#include "../sylar_dchg/iomanager.h"
#include "../sylar_dchg/bytearray.h"
#include "../sylar_dchg/address.h"

static sylar_dchg::Logger::ptr g_logger = SYLAR_DCHG_LOG_ROOT();

class EchoServer : public sylar_dchg::TcpServer {
public:
    EchoServer(int type);
    void handleClient(sylar_dchg::Socket::ptr client);

private:
    int m_type = 0;
};

EchoServer::EchoServer(int type)
    :m_type(type) {
}

void EchoServer::handleClient(sylar_dchg::Socket::ptr client) {
    SYLAR_DCHG_LOG_INFO(g_logger) << "handleClient " << *client;   
    sylar_dchg::ByteArray::ptr ba(new sylar_dchg::ByteArray);
    while(true) {
        ba->clear();
        std::vector<iovec> iovs;
        ba->getWriteBuffers(iovs, 1024);

        int rt = client->recv(&iovs[0], iovs.size());
        if(rt == 0) {
            SYLAR_DCHG_LOG_INFO(g_logger) << "client close: " << *client;
            break;
        } else if(rt < 0) {
            SYLAR_DCHG_LOG_INFO(g_logger) << "client error rt=" << rt
                << " errno=" << errno << " errstr=" << strerror(errno);
            break;
        }
        ba->setPosition(ba->getPosition() + rt);
        ba->setPosition(0);
        //SYLAR_DCHG_LOG_INFO(g_logger) << "recv rt=" << rt << " data=" << std::string((char*)iovs[0].iov_base, rt);
        if(m_type == 1) {//text 
            std::cout << ba->toString();// << std::endl;
        } else {
            std::cout << ba->toHexString();// << std::endl;
        }
        std::cout.flush();
    }
}

int type = 1;

void run() {
    SYLAR_DCHG_LOG_INFO(g_logger) << "server type=" << type;
    EchoServer::ptr es(new EchoServer(type));
    auto addr = sylar_dchg::Address::LookupAny("0.0.0.0:8020");
    while(!es->bind(addr)) {
        sleep(2);
    }
    es->start();
}

int main(int argc, char** argv) {
    if(argc < 2) {
        SYLAR_DCHG_LOG_INFO(g_logger) << "used as[" << argv[0] << " -t] or [" << argv[0] << " -b]";
        return 0;
    }

    if(!strcmp(argv[1], "-b")) {
        type = 2;
    }

    sylar_dchg::IOManager iom(2);
    iom.schedule(run);
    return 0;
}
