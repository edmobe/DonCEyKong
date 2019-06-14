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
#include "socket.h"
#include <stdlib.h>

//GUI
#define GRAVEDAD 0.70f



///Metodo que carga toda la base de nuestro juego
///Recibe un gameState
void loadGame(GameState *game)
{
  SDL_Surface *surface = NULL;

  ///Carga la imagen del barril 3y crea texturas con el render a partir de ella
  surface = IMG_Load("media/barril3.png");
  game->barril = SDL_CreateTextureFromSurface(game->renderer, surface);

  ///Carga la imagen del barril 7 y crea texturas con el render a partir de ella
  surface = IMG_Load("media/barril7.png");
  game->barrilMixFrames[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);
  //Carga la imagen del barril 8 y crea texturas con el render a partir de ella
  surface = IMG_Load("media/barril8.png");
  game->barrilMixFrames[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);
  ///Carga la imagen del barril 1 y crea texturas con el render a partir de ella
  surface = IMG_Load("media/barril3.png");
  game->barrilMixFrames[2] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);
  ///Carga la imagen del barril 4 y crea texturas con el render a partir de ella
  surface = IMG_Load("media/barril4.png");
  game->barrilMixFrames[3] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);
  ///Carga la imagen del barril 5 y crea texturas con el render a partir de ella
  surface = IMG_Load("media/barril5.png");
  game->barrilMixFrames[4] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);
  ///Carga la imagen del barril 6 y crea texturas con el render a partir de ella
  surface = IMG_Load("media/barril6.png");
  game->barrilMixFrames[5] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);


  ///Carga la imagen del barril 1 y crea texturas con el render a partir de ella
  surface = IMG_Load("media/barril1.png");
  game->estanonFrames[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);

  ///Carga la imagen de Pauline1 1 y crea texturas con el render a partir de ella
  surface = IMG_Load("media/Pauline/pauline3.png");
  game->paulineFrames[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);
  ///Carga la imagen de Pauline1 2 y crea texturas con el render a partir de ella
  surface = IMG_Load("media/Pauline/pauline4.png");
  game->paulineFrames[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);
  ///Carga la imagen de Pauline1 3 y crea texturas con el render a partir de ella
  surface = IMG_Load("media/Pauline/pauline2.png");
  game->paulineFrames[2] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);
  ///Carga la imagen de Pauline1 4 y crea texturas con el render a partir de ella
  surface = IMG_Load("media/Pauline/pauline1.png");
  game->paulineFrames[3] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);


  ///Carga la imagen de la llama 1 y crea texturas con el render a partir de ella
  surface = IMG_Load("media/llama1.png");
  game->llamaFrames[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);
   ///Carga la imagen de llama 2 y crea texturas con el render a partir de ella
  surface = IMG_Load("media/llama2.png");
  game->llamaFrames[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);
   ///Carga la imagen de llama 3 y crea texturas con el render a partir de ella
  surface = IMG_Load("media/llama3.png");
  game->llamaFrames[2] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);
   ///Carga la imagen de llama 4 y crea texturas con el render a partir de ella
  surface = IMG_Load("media/llama4.png");
  game->llamaFrames[3] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);


  ///Carga la imagen del barril 7 y crea texturas con el render a partir de ella
  surface = IMG_Load("media/barril7.png");
  game->barrilBajaFrames[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
  //game->barrilMixFrames[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);
   ///Carga la imagen del barril 8 y crea texturas con el render a partir de ella
  surface = IMG_Load("media/barril8.png");
  game->barrilBajaFrames[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
  //game->barrilMixFrames[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);


  ///Carga la imagen del barril 1 y crea texturas con el render a partir de ella
  surface = IMG_Load("media/barril2.png");
  game->estanonFrames[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);

  ///Carga la imagen de DK (0) y crea texturas con el render a partir de ella
  surface = IMG_Load("media/King9.png");
  game->DK[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);

  ///Carga la imagen de DK (1) y crea texturas con el render a partir de ella
  surface = IMG_Load("media/King8.png");
  game->DK[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);

  ///Carga la imagen de DK (2) y crea texturas con el render a partir de ella
  surface = IMG_Load("media/King11.png");
  game->DK[2] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);

  ///Carga la imagen de mario muerto y crea texturas con el render a partir de ella
  surface = IMG_Load("media/mario2.png");
  game->marioMuerto = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);

  ///Carga la imagen de Mario (0) y crea texturas con el render a partir de ella
  surface = IMG_Load("media/run4.png");
  game->marioFrames[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);

  ///Carga la imagen de Mario (1) y crea texturas con el render a partir de ella
  surface = IMG_Load("media/run5.png");
  game->marioFrames[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);

  ///Carga la imagen de Mario (2) y crea texturas con el render a partir de ella
  surface = IMG_Load("media/mario11.png");
  game->marioFrames[2] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);

  ///Carga la imagen de Mario (3) y crea texturas con el render a partir de ella
  surface = IMG_Load("media/mario13.png");
  game->marioFrames[3] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);

  ///Carga la imagen del Suelo y crea texturas con el render a partir de ella
  surface = IMG_Load("media/piso.png");
  game->suelo = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);

  ///Carga las letras del font
  game->font = TTF_OpenFont("fonts/Crazy-Pixel.ttf", 50);
  if(!game->font){
    printf("Cannot find font");
    SDL_Quit();
    exit(1);
  }

  ///Carga la escalera
  surface = IMG_Load("media/escalera.png");
  game->escalera1 = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);



  ///Posiciones de las imagenes
    ///init mario
  game->man.x = 35;
  game->man.y = 625;
  game->man.dx = 0;
  game->man.dy = 0;
  game->man.enSuelo = 0;
  game->man.animFrame = 0;
  game->man.izq = 1;
  game->man.slowingDown = 0;
  game->man.lives=3;
  game->man.muerto = 0;
  game->man.direction = 'R';

  ///init el estado del juego
  game->statusState=STATUS_STATE_LIVES;

  ///init estado de la vidas
  init_status_lives(game);
  game->deathCountdown = -1;

  
  ///init label para escribir en pantalla
  game->label=NULL;

  ///init el tiempo
  game->time = 0;

  ///init DK
  game->dk.x = 20;
  game->dk.y = 80;
  game->dk.DKFrame=0;

  ///init suelo
  ///primer piso
  for(int i=0; i<25; i++)
    {
    game->piso[i].w=25;
    game->piso[i].h=20;
    game->piso[i].x=50+(i*25);
    game->piso[i].y=660;
  }
  ///segundo piso
  for(int i=25; i<45; i++)
    {
    game->piso[i].w=25;
    game->piso[i].h=20;
    game->piso[i].x=(i-25)*25;
    game->piso[i].y=550+(i-25);
  }
  ///tercer piso
  for(int i=45; i<65; i++)
    {
    game->piso[i].w=25;
    game->piso[i].h=20;
    game->piso[i].x=600-((i-45)*25);
    game->piso[i].y=450+(i-45);
  }
  ///cuarto piso
  for(int i=65; i<85; i++)
    {
    game->piso[i].w=25;
    game->piso[i].h=20;
    game->piso[i].x=(i-65)*25;
    game->piso[i].y=340+(i-45);
  }
  ///quinto piso
  for(int i=85; i<105; i++)
    {
    game->piso[i].w=25;
    game->piso[i].h=20;
    game->piso[i].x=600-((i-85)*25);
    game->piso[i].y=250+(i-85);
  }
  ///sexto piso
  for(int i=105; i<127; i++)
    {
    game->piso[i].w=25;
    game->piso[i].h=20;
    game->piso[i].x=(i-105)*25;
    game->piso[i].y=150+(i-105);
  }
  ///piso final
  for(int i=127; i<135; i++)
    {
    game->piso[i].w=25;
    game->piso[i].h=20;
    game->piso[i].x= 115+(i-127)*25;
    game->piso[i].y=75;
  }
  ///init de las escaleras primera parte
  ///Temporal se encarga de dibujar diversos bloques de escaleras
  int temporal = 610;
  for (int i = 0; i < 4; i += 2)
  {
    game->escaleras[i].x=500;
    game->escaleras[i].y=temporal;
    game->escaleras[i+1].x=500;
    game->escaleras[i+1].y=temporal-50;
    temporal = 410;
  }
  ///ini escaleras segunda parte
  temporal = 510;
  for (int i = 4; i < 8; i += 2)
  {
    game->escaleras[i].x=95;
    game->escaleras[i].y=temporal;
    game->escaleras[i+1].x=95;
    game->escaleras[i+1].y=temporal-40;
    temporal = 310;
  }
  ///ini escaleras tercera parte
  for (int i = 8; i < 10; i += 2)
  {
    game->escaleras[i].x=550;
    game->escaleras[i].y=200;
    game->escaleras[i+1].x=550;
    game->escaleras[i+1].y=200-40;
    
  }
  ///Escaleras cuarta parte
  for (int i = 10; i < 12; i += 2)
  {
    game->escaleras[i].x=315;
    game->escaleras[i].y=115;
    game->escaleras[i+1].x=315;
    game->escaleras[i+1].y=115-40;
    
  }
  ///Estañon de fuego
  game->estanon.x = 50;
  game->estanon.y = 620;
  game->estanon.estanonFrame = 0;

  ///Pauline 
  game->pauline.x = 120;
  game->pauline.y = 43;
  game->pauline.dx = 1;
  game->pauline.paulineFrame = 0;


}