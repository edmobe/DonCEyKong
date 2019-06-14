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
void update_positions(char *buffer, GameState *game) {
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
  while(buffer[i] != '/') {
      y[ycount] = buffer[i];
      i++;
      ycount++;
  }
  i++;

  game->man.x = (float)atof(x);
  game->man.y = (float)atof(y);
}

void update_direction(char* buffer, GameState *game){
    const int pos = 2;
    int i = 2;
    int n;
    for(n = 0; n < pos; n++){
      while(buffer[i] != '/') {
        i++;
      }
      i++;

    }
    game->man.direction = buffer[i];
}

// Da la informacion del juego al servidor
void send_info(int sockfd, GameState *game, int *newBarril, int *newBarrilBaja, int *newBarrilMix)
{
    printf("Mensaje a enviar: ");
    char buffer[MAX] = {'2', '\0'};

    printf("%s\n", buffer);

    write(sockfd, buffer, sizeof(buffer));
    bzero(buffer, sizeof(buffer));
    read(sockfd, buffer, sizeof(buffer));
    printf("Mensaje del servidor: %s\n", buffer);

    update_positions(buffer, game);
    update_direction(buffer, game);

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
