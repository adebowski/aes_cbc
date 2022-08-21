#pragma once
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <functional>
#include <vector>

class TCPClient {
     int m_socket;
    sockaddr_in m_server;
    std::thread m_clientListen;

   public:
    TCPClient(const char *server_address, const uint16_t server_port);
    
    TCPClient() = delete;
    TCPClient(const TCPClient&) = delete;
    TCPClient(TCPClient&&) = delete;
    TCPClient& operator=(const TCPClient&) = delete;
    TCPClient& operator=(TCPClient&&) = delete;

    int GetSocket() const {
        return m_socket;
    }

    bool OpenConnection();
    bool CloseConnection();
};
