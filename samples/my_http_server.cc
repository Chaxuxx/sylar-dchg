#include "../sylar_dchg/http/http_server.h"
#include "../sylar_dchg/log.h"

sylar_dchg::Logger::ptr g_logger = SYLAR_DCHG_LOG_ROOT();
// sylar_dchg::IOManager::ptr worker;
void run() {
    g_logger->setLevel(sylar_dchg::LogLevel::INFO);
    sylar_dchg::Address::ptr addr = sylar_dchg::Address::LookupAnyIPAddress("0.0.0.0:8020");
    if(!addr) {
        SYLAR_DCHG_LOG_ERROR(g_logger) << "get address error";
        return;
    }

    // sylar_dchg::http::HttpServer::ptr http_server(new sylar_dchg::http::HttpServer(true, worker.get()));
    sylar_dchg::http::HttpServer::ptr http_server(new sylar_dchg::http::HttpServer(true));
    bool ssl = false;
    while(!http_server->bind(addr, ssl)) {
        SYLAR_DCHG_LOG_ERROR(g_logger) << "bind " << *addr << " fail";
        sleep(1);
    }

    if(ssl) {
        //http_server->loadCertificates("/home/apps/soft/sylar/keys/server.crt", "/home/apps/soft/sylar/keys/server.key");
    }

    http_server->start();
}

int main(int argc, char** argv) {
    sylar_dchg::IOManager iom(2);
    // worker.reset(new sylar_dchg::IOManager(4, true));
    iom.schedule(run);
    return 0;
}
