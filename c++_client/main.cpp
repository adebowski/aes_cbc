#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "TCPClient.h"

#include <thread>
#include <vector>
#include "Parser.h"

#define PORT 8888
#define MAX_BUFFER_SIZE 512

static void GetData(const int socket) {
    std::vector<uint8_t> buffer(MAX_BUFFER_SIZE,0);
    for (;;) {
        buffer.clear();
        int receivedData = read(socket, &buffer[0], 100);
        if (receivedData == 0) {
            return;
        }
        const auto decryptedData = Parser::DecryptData(buffer.data(), receivedData);
        printf("Decrypted data: %s \n", decryptedData.c_str());
    }
}

int main(int, char**) {
    TCPClient tcpClient("127.0.0.1", 8888);
    if (tcpClient.OpenConnection()) {
        std::thread thread(GetData, tcpClient.GetSocket());
        thread.join();
    }
}