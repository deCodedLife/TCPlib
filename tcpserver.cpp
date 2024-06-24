#include "tcpserver.h"

TCPServer::TCPServer(TCPUser user) :
    tcp_user(user)
{
    InitSocket(&tcp_user);
    BindAddress(tcp_user, &tcp_binding);
}

TCPServer::~TCPServer()
{
    close(tcp_user.Connection());
}


void TCPServer::ListenAll()
{
    int tcp_server = listen(tcp_user.Connection(), SOMAXCONN);
    if (tcp_server == -1) {
        std::cerr << "Can't start tcp server" << std::endl;
        return;
    }

    while(true)
    {
        TCPUser *client = new TCPUser();
        ConnectionUser(&client, tcp_user.Connection());
        handlers[client] = new std::thread([&](TCPUser client){
            this->HandleMessages(client);
        }, *client);
    }
}


void TCPServer::HandleMessages(TCPUser client)
{
    const std::chrono::duration thread_delay = std::chrono::milliseconds(100);
    std::cout << "[ ] New client connected" << std::endl;

    while (true)
    {
        std::this_thread::sleep_for(thread_delay);

        std::string client_message;
        bool is_quit = false;
        RecieveMessage(&client, &client_message, &is_quit);

        if (is_quit)
            break;

        NetAddr address = client.NetAddress();
        std::cout << "[ ] User {"
                  << address.tcp_host << ":" << address.tcp_port
                  << "} Sent "
                  << client_message
                  << std::endl;
    }
}
