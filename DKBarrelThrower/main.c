#include <stdio.h>

//Socket
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>
#define PORT 8888
#define MAX 500
#define SA struct sockaddr

// Da la informacion del juego al servidor
void send_barrel(int sockfd, char barreltype)
{
    char buffer[MAX];
    buffer[0] = '0';
    buffer[1] = '/';
    buffer[2] = barreltype;
    buffer[3] = '\0';

    write(sockfd, buffer, sizeof(buffer));
    bzero(buffer, sizeof(buffer));
    read(sockfd, buffer, sizeof(buffer));
    printf("Mensaje del servidor: %s\n", buffer);
    if ((strncmp(buffer, "exit", 4)) == 0) {
        printf("El cliente ha salido...\n");
    }
}


int main() {
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

    char tipo[2];

    printf("---------Hola desde el servidor--------------\n");
    while(1) {
        printf("\n-------Favor indique el tipo de barril-------\n");
        printf("1: Barril normal\n");
	printf("2: Barril caida libre\n");
	printf("3: Barriles mix\n");
        printf(">>> ");
        scanf("%s", tipo);
        if(strncmp(tipo, "1") == 0) {
            // Da al informacion del barril al servidor
            send_barrel(sockfd, tipo[0]);
        } else {
            printf("Comando desconocido\n");
        }
    }

}
