//Example code: A simple server side code, which echos back the received message.
//Handle multiple socket connections with select and fd_set on Linux
#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h> //close
#include <arpa/inet.h> //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros

#define TRUE 1
#define FALSE 0
#define PORT 8888

void update_game_barrel(char* buffer, char* barreltype) {
    barreltype = buffer[2];
}

void update_game_positions(char *buffer, float *posx, float *posy) {
    int i = 2;
    int xcount = 0;
    int ycount = 0;
    char x[10];
    char y[10];
    while(buffer[i] != '/') {
        x[xcount] = buffer[i];
        i++;
        xcount++;
    }
    i++;
    printf("%c", buffer[i]);
    while(buffer[i] != '\0') {
        y[ycount] = buffer[i];
        i++;
        ycount++;
    }
    
    *posx = (float)atof(x);
    *posy = (float)atof(y);
}

int main(int argc , char *argv[])
{
    int opt = TRUE;
    int master_socket , addrlen , new_socket , client_socket[3] ,
            max_clients = 3 , activity, i , valread , sd;
    int max_sd;
    struct sockaddr_in address;

    char buffer[1025]; //data buffer of 1K

    //set of socket descriptors
    fd_set readfds;

    //positions
    char positions[500];

    //server variables
    char barreltype = '0';
    float posx = 0;
    float posy = 0;

    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++)
    {
        client_socket[i] = 0;
    }

    //create a master socket
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
    {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    //set master socket to allow multiple connections ,
    //this is just a good habit, it will work without this
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                   sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    //bind the socket to localhost port 8888
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("Error en el puerto");
        exit(EXIT_FAILURE);
    }
    printf("Conexion en el puerto: %d \n", PORT);

    //try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accept the incoming connection
    addrlen = sizeof(address);
    puts("Esperando conexiones ...");

    while(TRUE)
    {
        //clear the socket set
        FD_ZERO(&readfds);

        //add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        //add child sockets to set
        for ( i = 0 ; i < max_clients ; i++)
        {
            //socket descriptor
            sd = client_socket[i];

            //if valid socket descriptor then add to read list
            if(sd > 0)
                FD_SET( sd , &readfds);

            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;
        }

        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

        if ((activity < 0) && (errno!=EINTR))
        {
            printf("Error de seleccion");
        }

        //If something happened on the master socket ,
        //then its an incoming connection
        if (FD_ISSET(master_socket, &readfds))
        {
            if ((new_socket = accept(master_socket,
                                     (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            //inform user of socket number - used in send and receive commands
            printf("Nueva conexion, fd del socket es %d , ip: %s , puerto: %d\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs
                    (address.sin_port));
            /*
            //send new connection greeting message
            if( send(new_socket, hello_message, strlen(hello_message), 0) != strlen(hello_message) )
            {
                perror("send");
            }
            
            puts("Mensaje inicial enviado");
            */

            //add new socket to array of sockets
            for (i = 0; i < max_clients; i++)
            {
                //if position is empty
                if(client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    printf("Agregando a la lista de sockets como: %d\n" , i);

                    break;
                }
            }
        }

        //else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++)
        {
            sd = client_socket[i];

            if (FD_ISSET( sd , &readfds))
            {
                //Check if it was for closing , and also read the
                //incoming message
                if ((valread = read( sd , buffer, 1024)) == 0)
                {
                    //Somebody disconnected , get his details and print
                    getpeername(sd , (struct sockaddr*)&address , \
						(socklen_t*)&addrlen);
                    printf("Host desconectado, ip %s, puerto %d \n" ,
                           inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

                    //Close the socket and mark as 0 in list for reuse
                    close(sd);
                    client_socket[i] = 0;
                }

                    //Echo back the message that came in
                else
                {
                    printf("He recibido: %s\n", buffer);
                    //set the string terminating NULL byte on the end
                    //of the data read
                    buffer[valread] = '\0';
                    
                    //Se recibe info del juego
                    if(buffer[0] == '0'){
                        update_game_barrel(buffer, &barreltype);
                        char* update_message = "Barril recibido";
                        send(sd, update_message, strlen(update_message), 0);
                    } else if(buffer[0] == '1'){
                        update_game_positions(buffer, &posx, &posy);
                        printf("Se han actualizado las posiciones en X (%f) y en Y (%f)\n", posx, posy);
                        int i = 0;
                        while(buffer[i] != '\0') {
                            positions[i] = buffer[i];
                            i++;
                        }
                        positions[i] = '/';
                        positions[i + 1] = barreltype;
                        positions[i + 2] = '\0';
                        send(sd, positions, strlen(positions), 0);
                    } else {
                        char *ukn_command = "No reconozco ese comando\n";
                        send(sd, ukn_command, strlen(ukn_command), 0);
                    }
                }
            }
        }
    }

    return 0;
}

//Notas para documentacion:
//Tomo mucho tiempo buscar una solucion en WinSock, pero tenia muchos problemas
//La solucion mas rapida considerando el tiempo era adaptar el juego a Linux
//Varios problemas encontrados:
//- Instalar libreria SDL2 en Ubuntu
//- Conocer los parametros adicionales de compilacion (-lSDL2 y -lSDL2_image)
//- Especialmente fue dificil encontrar -lSDL2_image porque no habia info

//References:
//https://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading/
//https://lazyfoo.net/tutorials/SDL/01_hello_SDL/linux/index.php
