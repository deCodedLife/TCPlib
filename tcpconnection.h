#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <unistd.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <iostream>

#include "tcpuser.h"
#define MESSAGE_BUFFER_SIZE 4096


class TCPConnection
{
public:
    TCPConnection();
    void InitSocket(TCPUser *user);
    void BindAddress(TCPUser user, int *binding);
    void SendMessage(TCPUser user, std::string data);
    void RecieveMessage(TCPUser *from, std::string *buffer, bool *quit);
    void ConnectionUser(TCPUser **newUser, int server_sock);
};

#endif // TCPCONNECTION_H
