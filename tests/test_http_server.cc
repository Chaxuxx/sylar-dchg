#include "../sylar_dchg/http/http_server.h"
#include "../sylar_dchg/log.h"
#include "../sylar_dchg/env.h"
// #include <iostream>
static sylar_dchg::Logger::ptr g_logger = SYLAR_DCHG_LOG_ROOT();

#define XX(...) #__VA_ARGS__


sylar_dchg::IOManager::ptr worker;
void run() {
    g_logger->setLevel(sylar_dchg::LogLevel::INFO);
    //sylar_dchg::http::HttpServer::ptr server(new sylar_dchg::http::HttpServer(true, worker.get(), sylar_dchg::IOManager::GetThis()));
    
    sylar_dchg::http::HttpServer::ptr server(new sylar_dchg::http::HttpServer(true));
    sylar_dchg::Address::ptr addr = sylar_dchg::Address::LookupAnyIPAddress("0.0.0.0:8020");
    while(!server->bind(addr)) {
        sleep(2);
    }
    auto sd = server->getServletDispatch();
    sd->addServlet("/sylar/xx", [](sylar_dchg::http::HttpRequest::ptr req
                ,sylar_dchg::http::HttpResponse::ptr rsp
                ,sylar_dchg::http::HttpSession::ptr session) {
            rsp->setBody(req->toString());
            return 0;
    });

    sd->addGlobServlet("/sylar/*", [](sylar_dchg::http::HttpRequest::ptr req
                ,sylar_dchg::http::HttpResponse::ptr rsp
                ,sylar_dchg::http::HttpSession::ptr session) {
            rsp->setBody("Glob:\r\n" + req->toString());
            return 0;
    });

    sd->addGlobServlet("/sylarx/*", [](sylar_dchg::http::HttpRequest::ptr req
                ,sylar_dchg::http::HttpResponse::ptr rsp
                ,sylar_dchg::http::HttpSession::ptr session) {
            rsp->setBody(XX(<html>
<head><title>404 Not Found</title></head>
<body>
<center><h1>404 Not Found</h1></center>
<hr><center>nginx/1.16.0</center>
</body>
</html>
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
));
            return 0;
    });
    // std::cout<<"hello"<<std::endl;
    server->start();
}

int main(int argc, char** argv) {

    // sylar_dchg::EnvMgr::GetInstance()->init(argc, argv);
    // sylar_dchg::Config::LoadFromConfDir(sylar_dchg::EnvMgr::GetInstance()->getConfigPath());

    sylar_dchg::IOManager iom(3, true, "main");//这里貌似不能单线程
    // sylar_dchg::IOManager iom(1);
    worker.reset(new sylar_dchg::IOManager(3, false, "worker"));
    iom.schedule(run);
    return 0;
}
