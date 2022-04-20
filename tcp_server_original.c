#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

short SocketCreate(void)
{
    short hSocket;
    printf("Create the socket\n");
    hSocket = socket(AF_INET, SOCK_STREAM, 0);
    return hSocket;
}
int BindCreatedSocket(int hSocket)
{
    int iRetval = -1;
    int ClientPort = 64000;
    struct sockaddr_in remote = {0};
    /* Internet address family */
    remote.sin_family = AF_INET;
    /* Any incoming interface */
    remote.sin_addr.s_addr = htonl(INADDR_ANY);
    remote.sin_port = htons(ClientPort); /* Local port */
    iRetval = bind(hSocket, (struct sockaddr *)&remote, sizeof(remote));
    return iRetval;
}
int main(int argc, char *argv[])
{
    int socket_desc, sock, clientLen, read_size;
    struct sockaddr_in server, client;
    char client_message[200] = {0};
    char message[100] = {0};
    const char *pMessage = "0x11";
    // Create socket
    socket_desc = SocketCreate();
    if (socket_desc == -1)
    {
        printf("Could not create socket");
        return 1;
    }
    printf("Socket created\n");
    // Bind
    if (BindCreatedSocket(socket_desc) < 0)
    {
        // print the error message
        perror("bind failed.");
        return 1;
    }
    printf("bind done\n");
    // Listen
    listen(socket_desc, 3);
    // Accept and incoming connection
    printf("Waiting for incoming connections...\n");
    clientLen = sizeof(struct sockaddr_in);
    // accept connection from an incoming client
    sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&clientLen);
    if (sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    printf("Connection accepted\n");
    while (1)
    {
        memset(client_message, '\0', sizeof client_message);
        memset(message, '\0', sizeof message);
        // Receive a reply from the client
        if (recv(sock, client_message, 200, 0) < 0)
        {
            printf("recv failed\n");
        }
        else
        {
            printf("Client reply : %s\n", client_message);
            if (strstr(client_message, "testimg"))
            {
                char buffer[1000] = {0};
                char buffer_img[2000000] = {0};
                FILE *file = fopen("pict.bmp", "r");
                *buffer_img = (char) 5;
                *(buffer_img + 1) = (char) 1228938;
                *(buffer_img + 2) = (char) (1228938/256);
                *(buffer_img + 3) = (char) (1228938/256/256);
                *(buffer_img + 4) = (char) (1228938/256/256/256);
                int len = 5;
                while (fgets(buffer, 1000, file))
                {
                    len += sprintf(buffer_img+len, "%s", buffer);
                }
                if (send(sock, buffer_img, len, 0) < 0)
                {
                    printf("Send failed");
                }
            }
            strcpy(message, "received");
            // Send some data
            if (send(sock, message, strlen(message), 0) < 0)
            {
                printf("Send failed");
            }
        }
    }

    return 0;
}