#ifndef __SYLAR_DCHG_HTTP_SERVLETS_STATUS_SERVLET_H__
#define __SYLAR_DCHG_HTTP_SERVLETS_STATUS_SERVLET_H__

#include "../servlet.h"

namespace sylar_dchg {
namespace http {

class StatusServlet : public Servlet {
public:
    StatusServlet();
    virtual int32_t handle(sylar_dchg::http::HttpRequest::ptr request
                   , sylar_dchg::http::HttpResponse::ptr response
                   , sylar_dchg::http::HttpSession::ptr session) override;
};

}
}

#endif
