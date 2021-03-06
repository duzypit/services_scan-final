#ifndef __SCRIBE_HPP__
#define __SCRIBE_HPP__
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <deque>
#include <thread>
#include <condition_variable>
#include <sstream>
#include <iomanip> //std::put_time

#include "../include/datatypes.hpp"
#include "../include/smtpSender.hpp"

class Scribe
{
public:
    Scribe();
    ~Scribe();
    void start(std::deque<Report>& overseerMsgQueue, std::mutex& overseerMutex);
    void stop();
    void setUpMailer(GmailCredentials credentials);

private:

    std::ofstream _file;
    std::thread _thread;
    bool _stop_thread;
    std::condition_variable _cv;

    GmailCredentials _credentials;

    void save(const Report& e);

    std::string formatMsg(const Report& e);

    void observe(std::deque<Report>& overseerMsgQueue, std::mutex& overseerMutex);
};

#endif
