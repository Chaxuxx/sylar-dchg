#include <iostream>
#include "../sylar_dchg/log.h"
// #include "../sylar_dchg/util.h"

int main(int argc, char** argv) {
    sylar_dchg::Logger::ptr logger(new sylar_dchg::Logger);
    logger->addAppender(sylar_dchg::LogAppender::ptr(new sylar_dchg::StdoutLogAppender));

    // sylar_dchg::FileLogAppender::ptr file_appender(new sylar_dchg::FileLogAppender("./log.txt"));
    // sylar_dchg::LogFormatter::ptr fmt(new sylar_dchg::LogFormatter("%d%T%p%T%m%n"));
    // file_appender->setFormatter(fmt);
    // file_appender->setLevel(sylar_dchg::LogLevel::ERROR);

    // logger->addAppender(file_appender);

    // sylar_dchg::LogEvent::ptr event(new sylar_dchg::LogEvent(__FILE__, __LINE__, 0, sylar_dchg::GetThreadId(), sylar_dchg::GetFiberId(), time(0)));
    sylar_dchg::LogEvent::ptr event(new sylar_dchg::LogEvent(logger,logger->getLevel(),__FILE__, __LINE__, 0, 1, 2, time(0),"hello"));
    // //event->getSS() << "hello sylar_dchg log";
    logger->log(sylar_dchg::LogLevel::DEBUG, event);
    std::cout << "hello sylar_dchg log" << std::endl;

    // SYLAR_dchg_LOG_INFO(logger) << "test macro";
    // SYLAR_dchg_LOG_ERROR(logger) << "test macro error";

    // SYLAR_dchg_LOG_FMT_ERROR(logger, "test macro fmt error %s", "aa");

    // auto l = sylar_dchg::LoggerMgr::GetInstance()->getLogger("xx");
    // SYLAR_dchg_LOG_INFO(l) << "xxx";
    return 0;
}
