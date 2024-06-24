#include "tcpclient.h"

TCPClient::TCPClient()
{
    tcp_user = TCPUser(0, NetAddr{});
    InitSocket(&tcp_user);
}

void TCPClient::ConnectTo(TCPUser user)
{
    NetAddr address = user.NetAddress();

    int sock_status = connect(
        tcp_user.Connection(),
        (sockaddr *) user.TCPAddrP(),
        sizeof(user.TCPAddr()));

    if (sock_status == -1) {
        std::cerr << "[!] Can't connect to server {"
                  << address.tcp_host << ":" << address.tcp_port
                  << "} " << std::endl;
        return;
    }
}

void TCPClient::NewNessage(std::string message)
{
    SendMessage(tcp_user, message);
}
