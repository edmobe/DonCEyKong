#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 8888
#define SA struct sockaddr
void give_info(int sockfd)
{
    char *buff[MAX];
    int n;
    bzero(buff, sizeof(buff));
    printf("Mensaje a enviar: ");
    char *man_x = "XMAN";
    char *man_y = "YMAN";
    buff[0] = '1';
    strcat(buff, "/");
    strcat(buff, man_x);
    strcat(buff, "/");
    strcat(buff, man_y);
    printf("%s\n", buff);
    printf("WRITE\n");
    write(sockfd, buff, sizeof(buff));
    bzero(buff, sizeof(buff));
    printf("READ\n");
    read(sockfd, buff, sizeof(buff));
    printf("Mensaje del servidor: %s\n", buff);
    printf("HA SALIDO?\n");
    if ((strncmp(buff, "exit", 4)) == 0) {
        printf("El cliente ha salido...\n");
    }
}

int main()
{
    //Socket
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Error al crear el socket...\n");
        exit(0);
    }
    else
        printf("Socket creado exitosamente..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("Error en la conexion al servidor...\n");
        exit(0);
    }
    else
        printf("Conectado al servidor...\n");


    // function for chat
    while(1){
        give_info(sockfd);
    }
    

    // close the socket
    close(sockfd);
}

//References:
//https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
//https://stackoverflow.com/questions/15850042/xcode-warning-implicit-declaration-of-function-is-invalid-in-c99
