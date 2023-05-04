#include <iostream>
#include "../sylar_dchg/log.h"
#include "../sylar_dchg/util.h"

int main(int argc, char** argv) {
    sylar_dchg::Logger::ptr logger(new sylar_dchg::Logger);
    logger->addAppender(sylar_dchg::LogAppender::ptr(new sylar_dchg::StdoutLogAppender));//这种定义方式使得很难对stdoutappender进行自定义格式化 所以放到fileappender之后测试 在p7 p8左右

    // sylar_dchg::FileLogAppender::ptr file_appender(new sylar_dchg::FileLogAppender("./log.txt"));#TODO fileappender尚未测试
    sylar_dchg::LogFormatter::ptr fmt(new sylar_dchg::LogFormatter("%d%T%p%T%m%n"));

    // file_appender->setFormatter(fmt);
    // file_appender->setLevel(sylar_dchg::LogLevel::ERROR);

    // logger->addAppender(file_appender);

    // sylar_dchg::LogEvent::ptr event(new sylar_dchg::LogEvent(__FILE__, __LINE__, 0, sylar_dchg::GetThreadId(), sylar_dchg::GetFiberId(), time(0)));
    // sylar_dchg::LogEvent::ptr event(new sylar_dchg::LogEvent(logger,logger->getLevel(),__FILE__, __LINE__, 0, sylar_dchg::GetThreadId(), sylar_dchg::GetFiberId(), time(0),"hello"));
    //哪里__line__ 就输出那里的行

    // event->getSS() << "hello sylar_dchg log";//message item
    // logger->log(sylar_dchg::LogLevel::DEBUG, event);//logger调用log函数输出event的值 这里log是主动调用的 宏里是析构时自动执行的
    // std::cout << "hello sylar_dchg log" << std::endl;

    SYLAR_DCHG_LOG_INFO(logger) << "test macro";//流式使用
    SYLAR_DCHG_LOG_ERROR(logger) << "test macro error";

    SYLAR_DCHG_LOG_FMT_ERROR(logger, "test macro fmt error %s", "aa");//格式化方式 但是同样是输出到流里面 最后析构输出

    auto l = sylar_dchg::LoggerMgr::GetInstance()->getLogger("xx");//使用manager创建一个logger 命名为xx
    SYLAR_DCHG_LOG_INFO(l) << "xxx";
    return 0;
}
