//GUI
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <time.h>
#include "main.h"
#include "status.h"
#include "load.h"
#include "barril.h"
#include "render.h"
#include "events.h"
#include "collide.h"
#include "process.h"
#include <stdlib.h>
#include "socket.h"

//Socket
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>


//Socket
#define PORT 8888
#define MAX 500
#define SA struct sockaddr

int barrel_event(char *buffer) {
    const int pos = 3;
    int i = 2;
    int n;
    for(n = 0; n < pos; n++){
      while(buffer[i] != '/') {
        i++;
      }
      i++;

    }

  if(buffer[i] == '1') {
    return 1;
  }
  else if(buffer[i] == '2') {
    return 2;
  }
  else if(buffer[i] == '3') {
    return 3;
  }
  return 0;
}

///*************************************************************************************************************
// Da la informacion del juego al servidor
void send_info(int sockfd, GameState *game, int *newBarril, int *newBarrilBaja, int *newBarrilMix)
{
    printf("Mensaje a enviar: ");
    char buffer[MAX];
    char man_x[10];
    char man_y[10];
    int i = 0;
    snprintf(man_x, sizeof man_x, "%f", game->man.x);
    snprintf(man_y, sizeof man_y, "%f", game->man.y);
    buffer[0] = '1';
    buffer[1] = '/';

    while(man_x[i] != '\0') {
      buffer[i + 2] = man_x[i];
      i++;
    }
    buffer[i] = '/';
    
    int j = 0;

    while(man_y[j] != '\0') {
      buffer[i + 1] = man_y[j];
      i++;
      j++;
    }

    buffer[i] = '/';
    buffer[i+1] = game->man.direction;

    printf("%s\n", buffer);

    write(sockfd, buffer, sizeof(buffer));
    bzero(buffer, sizeof(buffer));
    read(sockfd, buffer, sizeof(buffer));
    printf("Mensaje del servidor: %s\n", buffer);

    if(barrel_event(buffer) == 1) {
      *newBarril = *newBarril + 1; 
    }
    else if(barrel_event(buffer) == 2) {
      *newBarrilBaja = *newBarrilBaja + 1; 
    }
    else if(barrel_event(buffer) == 3) {
      *newBarrilMix = *newBarrilMix + 1; 
    }

    if ((strncmp(buffer, "exit", 4)) == 0) {
        printf("El cliente ha salido...\n");
    }
}
///******************************************************************************************************