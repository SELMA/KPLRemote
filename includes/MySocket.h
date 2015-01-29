#ifndef MYSOCKET_H_
#define MYSOCKET_H_

#include <string>
#include <iostream>
#include <winsock2.h>

#define SIZE 512

class MySocket
{
private:
    WSADATA			_WSAData;
    SOCKET			_sock;
    fd_set 			_readfds;
    struct timeval              _tv;
    char			_buffer[SIZE + 1];
    std::string                 _reply;
    bool                        _currentCo;
	 
public:
    MySocket();
    ~MySocket();
    bool 			connex(std::string, int);
    bool 			sendData(std::string);
    std::string                 recvData();
    bool                        getCurrentCoStatu();
    void                        setCurrentCoStatu();
    void                        rezSock();
};

#endif /* MYSOCKET_H_ */