#include <iostream>
#include <string>
#include <thread>
#include <sstream>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment (lib, "ws2_32.lib")  
#endif


using namespace std;
void receiveMessages(int clientSocket) {
    char buffer[4096];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            cout << "\n" << string(buffer, 0, bytesReceived) << endl;
        } else if (bytesReceived == 0) {
            cout << "Connection closed by server." << endl;
            break;
        }
    }
}

int main()
{
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "Failed to initialize Winsock." << endl;
        return 1;
    }
#endif
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(11111);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) {
        cerr << "Invalid address/ Address not supported." << endl;
        return 1;
    }

    if (connect(clientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        cerr << "Connection failed." << endl;
        return 1;
    }

    thread receiveThread(receiveMessages, clientSocket);
  
    bool sending = true;
    while(sending){
        string strout;
        getline(cin,strout);
        if (strout == "quit" || strout == "Quit" || strout == "QUIT")
        {
            sending = false;
        }
        send(clientSocket,strout.c_str(),strout.size()+1,0);
    }
    receiveThread.detach();
 
    #ifdef _WIN32
    closesocket(clientSocket);
    WSACleanup();
#else
    close(clientSocket);
#endif

    return 0;
}
