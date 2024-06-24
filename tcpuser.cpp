#include "tcpuser.h"

TCPUser::TCPUser()
{

}

TCPUser::TCPUser(int sock, NetAddr addr) :
    tcp_sock(sock),
    tcp_addr(addr)
{
    tcp_sock_addr = sockaddr_in {
        .sin_family = AF_INET,
        .sin_port   = htons(tcp_addr.tcp_port),
        .sin_addr   = inet_addr(tcp_addr.tcp_host.c_str()),
    };
}

void TCPUser::SetSocket(int sock)
{
    tcp_sock = sock;
}

int TCPUser::Connection()
{
    return tcp_sock;
}

NetAddr TCPUser::NetAddress()
{
    return tcp_addr;
}

sockaddr_in TCPUser::TCPAddr()
{
    return tcp_sock_addr;
}

sockaddr_in *TCPUser::TCPAddrP()
{
    return &tcp_sock_addr;
}

