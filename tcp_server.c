#include "tcp_server.h"

struct mainStruct *main_s;

/**
 * @brief Create a tcp socket
 *
 * @return short
 */
short SocketCreate(void)
{
    short hSocket;
    printf("Create the socket\n");
    hSocket = socket(AF_INET, SOCK_STREAM, 0);
    return hSocket;
}

/**
 * @brief Bind an existing socket to a port and accepting any incoming addr
 *
 * @param hSocket ref to the socket
 * @return int
 */
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

int main()
{
    if ((main_s = malloc(sizeof(mainStruct))) == NULL)
    {
        printf("erreur allocation mémoire\n");
        return -1;
    }
    if ((main_s->img_s = malloc(sizeof(img))) == NULL)
    {
        printf("erreur allocation mémoire\n");
        return -1;
    }
    if ((main_s->cmd_struct = malloc(sizeof(cmd))) == NULL)
    {
        printf("erreur allocation mémoire\n");
        return -1;
    }
    if ((main_s->chg_mode_struct = malloc(sizeof(chg_mode))) == NULL)
    {
        printf("erreur allocation mémoire\n");
        return -1;
    }
    if ((main_s->weight_struct = malloc(sizeof(weight_upd))) == NULL)
    {
        printf("erreur allocation mémoire\n");
        return -1;
    }
    if ((main_s->buf_f_struct = malloc(sizeof(circular_buf_t) + sizeof(bool))) == NULL)
    {
        printf("erreur allocation mémoire\n");
        return -1;
    }
    char *bufferMsg = malloc(100 * sizeof(char));
    int socket_desc, sock, clientLen, read_size;
    struct sockaddr_in server, client;
    char client_message[200] = {0};
    char message[100] = {0};
    main_s->buf_f_struct->cbuf = circular_buf_init(bufferMsg, 100);
    // Create socket
    socket_desc = SocketCreate();
    if (socket_desc == -1)
    {
        printf("Could not create socket\n");
        return -1;
    }
    printf("Socket created\n");
    // Bind
    if (BindCreatedSocket(socket_desc) < 0)
    {
        // print the error message
        perror("bind failed");
        return -1;
    }
    printf("bind done\n");
    // Listen
    listen(socket_desc, 3);
    printf("Waiting for incoming connections...\n");
    clientLen = sizeof(struct sockaddr_in);
    // accept connection from an incoming client
    sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&clientLen);
    if (sock < 0)
    {
        perror("accept failed");
        return -1;
    }
    printf("Connection accepted\n");
    memset(message, '\0', sizeof message);
    while (1)
    {
        memset(client_message, 0, sizeof(client_message));
        // Receive a reply from the client
        if (recv(sock, client_message, 200, 0) < 0)
        {
            printf("recv failed\n");
        }
        else
        {
            printf("Client reply : %s\n", client_message);

            // if we receieve stop message, we free all buffer and close the connection
            if (strstr(client_message,"STOP") != 0)
            {
                // freeing memory space
                circular_buf_free(main_s->buf_f_struct->cbuf);
                free(bufferMsg);
                free(main_s->cmd_struct);
                free(main_s->buf_f_struct);
                free(main_s->weight_struct);
                free(main_s->chg_mode_struct);
                free(main_s);
                // send end of connection and close socket
                send(sock, client_message, strlen(client_message), 0);
                close(socket_desc);
                break;
            }

            // if we receive another type of msg, we try to decode
            else
            {
                //if no code op, no need to call interpreteur
                if (decodeTC(main_s, client_message) == 0)
                    printf("Not a TC\n");
                else
                    interpreteur(main_s);
                // if new data : send new data
                if (main_s->buf_f_struct->new_data_f == true)
                {
                    int j = circular_buf_get(main_s->buf_f_struct->cbuf, bufferMsg);
                    if (j == -1)
                    {
                        printf("Retrieved failed\n");
                        return -1;
                    }

                    // Send some data
                    if (send(sock, bufferMsg, strlen(bufferMsg), 0) < 0)
                    {
                        printf("Send failed\n");
                        return -1;
                    }
                }
                // if new IMG to send : send the TM
                else if (main_s->img_s->img_f == true)
                {
                    char *imgTM = imgEncodedTM(main_s->img_s->addr, main_s->img_s->length);
                    // Send some data
                    if (send(sock, imgTM, main_s->img_s->length + 5, 0) < 0)
                    {
                        printf("Send failed\n");
                        return -1;
                    }
                    main_s->img_s->img_f = false;
                    free(imgTM);
                }
            }
        }
    }
    printf("end of while\n");
    return 0;
}
