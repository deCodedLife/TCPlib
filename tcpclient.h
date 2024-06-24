#pragma once

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>

#include "tcpconnection.h"
#include "tcpuser.h"



class TCPClient : public TCPConnection
{
public:
    TCPClient();
    void ConnectTo(TCPUser user);
    void NewNessage(std::string message);

private:
    TCPUser tcp_user;
};
