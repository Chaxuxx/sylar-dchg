#include "../sylar_dchg/http/http.h"
#include "../sylar_dchg/log.h"

void test_request() {
    sylar_dchg::http::HttpRequest::ptr req(new sylar_dchg::http::HttpRequest);
    req->setHeader("host" , "www.sylar.top");
    req->setBody("hello sylar");
    req->dump(std::cout) << std::endl;
}

void test_response() {
    sylar_dchg::http::HttpResponse::ptr rsp(new sylar_dchg::http::HttpResponse);
    rsp->setHeader("X-X", "sylar");
    rsp->setBody("hello sylar");
    rsp->setStatus((sylar_dchg::http::HttpStatus)400);
    rsp->setClose(false);

    rsp->dump(std::cout) << std::endl;
}

int main(int argc, char** argv) {
    test_request();
    test_response();
    return 0;
}
