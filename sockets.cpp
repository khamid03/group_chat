#include <iostream>
#include <string>
#include <sstream>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
 
#endif

using namespace std;
int main(){
    bool running = true;
    WSADATA wsInfo;
    WORD top = MAKEWORD(2,2);

    int ws_OK = WSAStartup(top,&wsInfo);
    if (ws_OK != 0)
    {
        cerr << "Problem with winsock!" << endl;
        return 1;
    }
    
    SOCKET server_listeting = socket(AF_INET, SOCK_STREAM, 0);
    if (server_listeting == INVALID_SOCKET)
    {
        cerr << "Problem with Socket!" << endl;
        return 0;
    }
    
    sockaddr_in hin;
    hin.sin_family = AF_INET;
    hin.sin_port = htons(11111);
    hin.sin_addr.S_un.S_addr = INADDR_ANY;

    bind(server_listeting,(sockaddr*)&hin,sizeof(hin));

    listen(server_listeting,SOMAXCONN);
    fd_set master_set;
    FD_ZERO(&master_set);

    FD_SET(server_listeting,&master_set);

    while (running)
    {
        fd_set copy_set = master_set;

        int socket_count = select(0,&copy_set,nullptr,nullptr,nullptr);
        for (int i = 0; i < socket_count; i++)
        {
            SOCKET socket = copy_set.fd_array[i];
            if (socket == server_listeting)
            {
                SOCKET client = accept(server_listeting,nullptr,nullptr);
                if (client < 0)
                {
                    cerr << "Fail to accept client\n";
                    exit(EXIT_FAILURE);
                }
                cout << "Client " << client <<" Connected"<<endl;
                for (int i = 0; i < (int)master_set.fd_count; i++)
                    {
                        SOCKET outsocket = master_set.fd_array[i];
                        if (outsocket != server_listeting && outsocket != socket)
                        {
                            ostringstream ss;
                            ss << "Socket No" << client << "--joined the chat\r\n";
                            string strout = ss.str();
                            send(outsocket,strout.c_str(),strout.size() + 1,0);
                        }
                    }
                FD_SET(client,&master_set);

                string welcoming = "Start talking with other people now!\r\nTo leave the chat type: quit or Quit or QUIT\r\n";
                send(client,welcoming.c_str(),welcoming.size()+1,0);
            }
            else
            {
                char buff_size[4096];
                ZeroMemory(buff_size,4096);

                int bytesin = recv(socket,buff_size,4096,0);
                if (bytesin <= 0)
                {   
                    for (int i = 0; i < (int)master_set.fd_count; i++)
                    {
                        SOCKET outsocket = master_set.fd_array[i];
                        if (outsocket != server_listeting && outsocket != socket)
                        {
                            ostringstream ss;
                            ss << "Socket No" << socket << "--left the chat\r\n";
                            string strout = ss.str();
                            send(outsocket,strout.c_str(),strout.size() + 1,0);
                        }
                    }
                    cout << "Client " << socket << " Disconnected"<<endl;
                    closesocket(socket);
                    FD_CLR(socket,&master_set);
                    
                }        
                else
                {
                    for (int i = 0; i < (int)master_set.fd_count; i++)
                    {
                        SOCKET outsocket = master_set.fd_array[i];
                        if (outsocket != server_listeting && outsocket != socket)
                        {
                            ostringstream ss;
                            ss << "Socket No" << socket << ": " << buff_size << "\r\n";
                            string strout = ss.str();
                            send(outsocket,strout.c_str(),strout.size() + 1,0);
                        }
                        
                    }
                    
                }
                
            }
            
        }
        
    }
}
