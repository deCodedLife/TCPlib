#ifndef TCPUSER_H
#define TCPUSER_H

#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>


struct NetAddr {
    std::string tcp_host;
    uint tcp_port;
};


class TCPUser
{
public:
    TCPUser();
    TCPUser(int sock, NetAddr addr);
    void SetSocket(int sock);

    int Connection();
    NetAddr NetAddress();

    sockaddr_in TCPAddr();
    sockaddr_in* TCPAddrP();

    static TCPUser fromPointer();

private:
    int tcp_sock;
    NetAddr tcp_addr;
    sockaddr_in tcp_sock_addr;
};

#endif // TCPUSER_H
