#include "TCPClient.h"
#include <iostream>

TCPClient::TCPClient(const char *server_address, const uint16_t server_port) : m_socket{-1}
{
    m_server.sin_family = AF_INET;
    m_server.sin_addr.s_addr = inet_addr(server_address);
    m_server.sin_port = htons(server_port);
}

bool TCPClient::OpenConnection() {
    // socket create and verification
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket == -1) {
        printf("socket creation failed...\n");
        return false;
    } else
        printf("Socket successfully created..\n");

    if (connect(m_socket, (sockaddr*)&m_server, sizeof(m_server)) != 0) {
        printf("connection with the server failed...\n");
        return false;
    }
    else
        printf("connected to the server..\n");

    return true;
}
bool TCPClient::CloseConnection() {
    close(m_socket);
}