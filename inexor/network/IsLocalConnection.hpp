/// Is the connection from the same machine?
///

#pragma once

#ifdef WIN32
#include <Winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#endif

inline bool IsLocalConnection(int socketfd) {
    sockaddr_in RemAddr, LocAddr;
    socklen_t Len = sizeof(RemAddr);
    getpeername(socketfd, (sockaddr *)&RemAddr, &Len);
    getsockname(socketfd, (sockaddr *)&LocAddr, &Len);
    return (RemAddr.sin_addr.s_addr == LocAddr.sin_addr.s_addr);
}