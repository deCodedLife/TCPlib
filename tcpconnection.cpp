#include "tcpconnection.h"

TCPConnection::TCPConnection(){}


void TCPConnection::InitSocket(TCPUser *user)
{
    int tcp_option = 1;
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);

    setsockopt(
        tcp_socket,
        SOL_SOCKET,
        SO_REUSEADDR | SO_REUSEPORT,
        &tcp_option,
        sizeof(tcp_option));

    if (tcp_socket == -1) {
        std::cerr << "Can't create socket" << std::endl;
        return;
    }

    user->SetSocket(tcp_socket);
}


void TCPConnection::BindAddress(TCPUser user, int *binding)
{
    NetAddr user_addr = user.NetAddress();

    *binding = bind(
        user.Connection(),
        (sockaddr *) user.TCPAddrP(),
        sizeof(user.TCPAddr()));

    if (*binding == -1) {
        std::cerr <<
            "Can't bind to " <<
            "{" << user_addr.tcp_host << ":" << user_addr.tcp_port << "}" <<
            std::endl;
        return;
    }
}


void TCPConnection::SendMessage(TCPUser user, std::string data)
{
    send(
        user.Connection(),
        data.c_str(),
        (sizeof(char) * data.length() + 1),
        0);
}


void TCPConnection::RecieveMessage(TCPUser *from, std::string *buffer, bool *quit)
{
    char buff[MESSAGE_BUFFER_SIZE];
    int in_message_size {0};
    std::fill(buff, buff + MESSAGE_BUFFER_SIZE, 0);

    NetAddr sock_addr = from->NetAddress();
    in_message_size = recv(
        from->Connection(),
        buff,
        MESSAGE_BUFFER_SIZE,
        0);

    if (in_message_size == -1) {
        std::cerr << "[ ] Can't read incoming message from " <<
            "{" << sock_addr.tcp_host << ":" << sock_addr.tcp_port << "}" <<
            std::endl;

        close(from->Connection());
        return;
    }

    if (in_message_size == 0) {
        std::clog << "[ ] Client " <<
            "{" << sock_addr.tcp_host << ":" << sock_addr.tcp_port << "} " <<
            "disconnected from server" <<
            std::endl;

        close(from->Connection());
        *quit = true;

        return;
    }

    *buffer = buff;
}


void TCPConnection::ConnectionUser(TCPUser **newUser, int server_sock)
{
    struct sockaddr_in address;
    socklen_t address_size = sizeof address;

    int socket = accept(
        server_sock,
        (sockaddr *) &address,
        &address_size);

    char host[NI_MAXHOST];
    char port[NI_MAXSERV];

    std::fill(host, host + NI_MAXHOST, 0);
    std::fill(port, port + NI_MAXHOST, 0);

    int infoStatus = getnameinfo(
        (sockaddr *) &address,
        (socklen_t) address_size,
        host, NI_MAXHOST,
        port, NI_MAXSERV,
        0);

    if (infoStatus != 0) {
        inet_ntop(AF_INET, &address.sin_addr, host, NI_MAXHOST);
        strncpy(
            port,
            std::to_string(ntohs(address.sin_port)).c_str(),
            NI_MAXSERV);
    }

    *newUser = new TCPUser {
        socket,
        NetAddr {
        .tcp_host = host,
        .tcp_port = (uint) atoi(port)
    }};
}
