#pragma once

#include <map>
#include <chrono>
#include <thread>
#include "tcpclient.h"
#include "tcpconnection.h"


class TCPServer : TCPConnection
{
public:
    TCPServer(TCPUser user);
    ~TCPServer();
    void ListenAll();
    virtual void HandleMessages(TCPUser client);

private:
    TCPUser tcp_user;
    int tcp_binding;
    std::map<TCPUser*, std::thread*> handlers;
};
