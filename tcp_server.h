#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<pthread.h>
#include<fcntl.h>
#include "decodageTC.h"
#include "encodageTM.h"
#include "struct_allocation.h"


#ifndef _TCPSERVER_H
#define _TCPSERVER_H

typedef struct socket_thr_s 
{
    int sock;
    int socket_desc;
} socket_thr_s;

/**
 * @brief Create a tcp socket 
 * 
 * @return short 
 */
short SocketCreate(void);

/**
 * @brief Bind an existing socket to a port and accepting any incoming addr
 * 
 * @param hSocket ref to the socket
 * @return int 
 */
int BindCreatedSocket(int hSocket);

#endif