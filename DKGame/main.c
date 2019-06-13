//GUI
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <time.h>
#include "main.h"
#include "status.h"
#include <stdlib.h>

//Socket
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>

//GUI
#define GRAVEDAD 0.70f

//Socket
#define PORT 8888
#define MAX 500
#define SA struct sockaddr

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

  ///Carga la imagen de DK y crea texturas con el render a partir de ella
  surface = IMG_Load("media/King9.png");
  if(surface == NULL)
  {
    printf("Cannot find DK image!\n\n");
    SDL_Quit();
    exit(1);
  }
  game->DK[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);

  ///Carga la imagen de mario muerto y crea texturas con el render a partir de ella
  surface = IMG_Load("media/mario2.png");
  if(surface == NULL)
  {
    printf("Cannot find mario muerto image!\n\n");
    SDL_Quit();
    exit(1);
  }
  game->marioMuerto = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);

  ///Carga la imagen de Mario (0) y crea texturas con el render a partir de ella
  surface = IMG_Load("media/run4.png");
  if(surface == NULL)
  {
    printf("Cannot find mario image!\n\n");
    SDL_Quit();
    exit(1);
  }

  game->marioFrames[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);

  ///Carga la imagen de Mario (1) y crea texturas con el render a partir de ella
  surface = IMG_Load("media/run5.png");
  if(surface == NULL)
  {
    printf("Cannot find mario image!\n\n");
    SDL_Quit();
    exit(1);
  }

  game->marioFrames[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
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
  game->man.up = 0;
  game->man.down = 0;

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


///Metodo que nos permite realizar animaciones con las imagenes
///recibe un gameState
void process(int newBarril, int newLlama, int newBarrilBaja, int newBarrilMix, GameState *game)
{
  ///a�ade tiempo, para hacer las animaciones por frames
  game->time++;

   if(game->statusState == STATUS_STATE_LIVES)
   {
       ///Muestra la ventana de vidas antes de empezar el juego
        if(game->time>120)
        {
          shutdown_status_lives(game);
          game->statusState= STATUS_STATE_GAME;
        }
   }

   ///si el estado de juego es Game Over
   else if(game->statusState == STATUS_STATE_GAMEOVER)
  {
    if(game->time > 190)
    {
      SDL_Quit();
      exit(0);
    }
  }

   ///si se esta jugando se realisa esto
   else if(game->statusState == STATUS_STATE_GAME)
  {
      ///Animación del estañon de fuego
      if (game->time % 8 == 0){
        if(game->estanon.estanonFrame == 0)
          {
            game->estanon.estanonFrame= 1;
                   
          }
          else
          {
            game->estanon.estanonFrame = 0;
          }
      } 

      ///Animación de Pauline
      if (game->time % 8 == 0 && game->pauline.dx > 0){
        if(game->pauline.paulineFrame == 0 || game->pauline.paulineFrame == 3)
          {
            game->pauline.paulineFrame = 1;
                   
          }
          else
          {
            game->pauline.paulineFrame = 0;
          }
      }
      if (game->time % 8 == 0 && game->pauline.dx < 0){
        if(game->pauline.paulineFrame == 0 || game->pauline.paulineFrame == 3)
          {
            game->pauline.paulineFrame = 2;
                   
          }
          else
          {
            game->pauline.paulineFrame = 3;
          }
      }

      ///Animación de las llamas
      for(int i = 0; i < newLlama; i++){
      if (game->time % 8 == 0 && game->llamas[i].dx < 0){
        if(game->llamas[i].llamaFrame == 0 || game->llamas[i].llamaFrame == 3)
          {
            game->llamas[i].llamaFrame = 1;
                   
          }
          else
          {
            game->llamas[i].llamaFrame = 0;
          }
      }
      if (game->time % 8 == 0 && game->llamas[i].dx > 0){
        if(game->llamas[i].llamaFrame == 0 || game->llamas[i].llamaFrame == 3)
          {
            game->llamas[i].llamaFrame = 2;
                   
          }
          else
          {
            game->llamas[i].llamaFrame = 3;
          }
      }
      }

      //Animación de los barriles mix
      for(int i = 0; i < newBarrilMix; i++){
      if (game->time % 8 == 0 && game->barrilMix[i].mix == 0){
        if(game->barrilMix[i].barrilMixFrame == 0 || game->barrilMix[i].barrilMixFrame == 2 || game->barrilMix[i].barrilMixFrame == 3 || game->barrilMix[i].barrilMixFrame == 4 || game->barrilMix[i].barrilMixFrame == 5) 
          {
            game->barrilMix[i].barrilMixFrame = 1;
                   
          }
          else
          {
            game->barrilMix[i].barrilMixFrame = 0;
          }
      }
      if (game->time % 8 == 0 && game->barrilMix[i].mix == 1){
        if(game->barrilMix[i].barrilMixFrame == 0 || game->barrilMix[i].barrilMixFrame == 1 || game->barrilMix[i].barrilMixFrame == 5 )
          {
            game->barrilMix[i].barrilMixFrame = 2;
                   
          }
          if(game->barrilMix[i].barrilMixFrame == 2){
            game->barrilMix[i].barrilMixFrame = 3;
          }
          if(game->barrilMix[i].barrilMixFrame == 3){
            game->barrilMix[i].barrilMixFrame = 4;
          }
          else
          {
            game->barrilMix[i].barrilMixFrame = 5;
          }
      }
      }

      ///Animación de los Barriles que bajan
      for(int i = 0; i < newBarrilBaja; i++){
        if (game->time % 8 == 0){
          if(game->barrilBaja[i].barrilBajanFrame == 0)
           {
              game->barrilBaja[i].barrilBajanFrame = 1;
                   
           }
            else
            {
              game->barrilBaja[i].barrilBajanFrame = 0;
            }
        }
      }

      ///Animación de mario muerto
      if(!game->man.muerto)
      {
          ///movimiento de mario
          Man *man = &game->man;
          man->x += man->dx;
          man->y += man->dy;

        ///cambiar el sprite segun el movimiento
        if(man->dx != 0 && man->enSuelo && !man->slowingDown)
        {
            ///si han pasado 8 frames por segundo
            if(game->time % 8 == 0)
             {
                if(man->animFrame == 0)
                {
                   man->animFrame = 1;
                   
                }
                else
                {
                   man->animFrame = 0;
                   
                }
             }
        }
       
      for (int i = 0; i < newBarril; i++){
        game->barriles[i].dy += GRAVEDAD;
      }
      for (int i = 0; i < newLlama; i++){
        if(game->llamas[i].gravedad == 1){
          game->llamas[i].dy += GRAVEDAD;
        }
        
      }
      for (int i = 0; i < newBarrilMix; i++){
        game->barrilMix[i].dy += GRAVEDAD;
      }
    
       
       man->dy += GRAVEDAD;
          
        
       
       }
    ///Si mario muere y el contador de muertes es inferior a 0
    if(game->man.muerto && game->deathCountdown < 0)
    {
      game->deathCountdown = 120;
    }
    if(game->deathCountdown >= 0)
    {
      game->deathCountdown--;
      if(game->deathCountdown < 0)
      {
        game->man.lives--;

        if(game->man.lives >= 0)
        {
          init_status_lives(game);
          game->statusState = STATUS_STATE_LIVES;
          game->time = 0;

          ///reset
          game->man.muerto = 0;
          game->man.x = 100;
          game->man.y = 240-40;
          game->man.dx = 0;
          game->man.dy = 0;
          game->man.enSuelo = 0;
        }
        else
        {
          init_game_over(game);
          game->statusState = STATUS_STATE_GAMEOVER;
          game->time = 0;
        }
      }
    }

   }



}

///Util funcion que nos permite saber si dos rectangulos (imagenes) estan chocando
int collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2)
{
  return (!((x1 > (x2+wt2)) || (x2 > (x1+wt1)) || (y1 > (y2+ht2)) || (y2 > (y1+ht1))));
}




///Metodo para verificar las colisiones
///Recibe un gameState
void collisionDetect(GameState *game)
{
   ///Verifica choques con barriles
  int i;
  for(int i = 0; i < NUM_BARRILES; i++)
  {
    if(collide2d(game->man.x, game->man.y, game->barriles[i].x, game->barriles[i].y, 30, 30, 20, 20))
    {
      game->man.muerto = 1;
    }
  }
  for(i = 0; i < NUM_BARRIL_BAJA; i++)
  {
    if(collide2d(game->man.x, game->man.y, game->barrilBaja[i].x, game->barrilBaja[i].y, 30, 30, 20, 20))
    {
      game->man.muerto = 1;
    }
  }

  for (int i = 0; i < NUM_LLAMAS; i++){
    for (int j = 0; j < NUM_ESCALERAS; j++){
      if(collide2d(game->llamas[i].x, game->llamas[i].y, game->escaleras[j].x+10, game->escaleras[j].y, 20, 20, 1, 40))
    {
      game->llamas[i].gravedad = 0;
      game->llamas[i].dx = 0;
      if(game->time % 2 == 0){
        game->llamas[i].y += -1;
        if(!(collide2d(game->llamas[i].x, game->llamas[i].y, game->escaleras[j].x+10, game->escaleras[j].y, 20, 20, 1, 40)))
          {
            if(game->llamas[i].check > 0){
              game->llamas[i].dx = -1;
              game->llamas[i].check = -20;
              game->llamas[i].gravedad = 1;

            }
            else
            {
              game->llamas[i].dx = 1;
              game->llamas[i].check = 20;
              game->llamas[i].gravedad = 1;
            }
            
            
        }
      }
    }
    }
  }

  ///Verifica choque de mario con pauline
  if(collide2d(game->man.x, game->man.y, game->pauline.x, game->pauline.y, 30, 30, 30, 30))
  {
        init_game_win(game);
        game->statusState = STATUS_STATE_WIN;
  }

  ///Verifica que mario no salga por la derecha
  if(game->man.x >= 600)
  {
      game->man.x = 560;
  }

  ///Verifica que mario no salga por la izquierda
  if(game->man.x <= 0)
  {
      game->man.x = 40;
  }

  ///Verifica colision con el suelo
  for(int i = 0; i < 135; i++)
  {
    float mw = 25, mh = 25;
    float mx = game->man.x, my = game->man.y;
    float bx = game->piso[i].x, by = game->piso[i].y, bw = game->piso[i].w, bh = game->piso[i].h;

    if(mx+mw/2 > bx && mx+mw/2<bx+bw)
    {
      ///Nos estamos golpeando la cabeza?
      if(my < by+bh && my > by && game->man.dy < 0)
      {
        ///corrige y
        game->man.y = by+bh;
        my = by+bh;

        ///si nos golpeamos la cabeza detiene la velocidad de salto
        game->man.dy = 0;
        game->man.enSuelo = 1;
      }
    }
    if(mx+mw > bx && mx<bx+bw)
    {
      ///Estamos callendo en el suelo
      if(my+mh > by && my < by && game->man.dy > 0)
      {
        ///corrige y
        game->man.y = by-mh;
        my = by-mh;

        ///si cae en el suelo, detiene la velocidad de salto
        game->man.dy = 0;
        game->man.enSuelo = 1;
      }
    }

    if(my+mh > by && my<by+bh)
    {
      ///Choca con costados del suelo (izquierdo)
      if(mx < bx+bw && mx+mw > bx+bw && game->man.dx < 0)
      {
        ///corrige x
        game->man.x = bx+bw;
        mx = bx+bw;

        game->man.dx = 0;
      }
      ///Choca con costados del suelo (derecho)
      else if(mx+mw > bx && mx < bx && game->man.dx > 0)
      {
        ///corrige x
        game->man.x = bx-mw;
        mx = bx-mw;

        game->man.dx = 0;
      }
    }
  }
}









///Metodo que verifica los posibles eventos que pueden pasar en el juego
///Recibe una ventana y un gameState para verificar los eventos
int processEvents(SDL_Window *window, GameState *game, int *newBarril, int *newLlamas, int *newBarrilBaja, int *newBarrilMix)
{
  ///Se llama a una funcion de SDL que nos facilita la verificacion de eventos
  SDL_Event event;
  int done = 0;

  while(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
        ///caso en que se cierra la ventana
      case SDL_WINDOWEVENT_CLOSE:
      {
        if(window)
        {
          SDL_DestroyWindow(window);
          window = NULL;
          done = 1;
        }
      }
      break;
      ///caso en que se apreta la tecla de abajo
      case SDL_KEYDOWN:
      {
        switch(event.key.keysym.sym)
        {
          case SDLK_ESCAPE:
            done = 1;
          break;
          ///caso en que se apreta la tecla de arriba
          case SDLK_UP:

            if(game->man.enSuelo)
            {
              game->man.dy = -6;
              game->man.enSuelo = 0;
         
              
            }
            
          break;
        }
      }
      break;
      ///caso en que se quita el juego
      case SDL_QUIT:
        done = 1;
      break;
    }
  }

  ///Esto nos permite que mario salte mas, al dejar la tecla de arriba apretada
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if(state[SDL_SCANCODE_UP])
    {
      game->man.dy -=0.2f;
      ///Verifica colision con escalera
      for(int i = 0; i < 12; i++)
        {
          
          if ((collide2d(game->man.x, game->man.y, game->escaleras[i].x, game->escaleras[i].y, 30, 30, 30, 40)))
            { 
              if (!(collide2d(game->man.x, game->man.y, game->escaleras[i].x, game->escaleras[i].y, 30, 30, 30, 40)))
              { 
                if(state[SDL_SCANCODE_UP])
                {
                  game->man.dy +=GRAVEDAD;
                }
              
              }
              if(!(state[SDL_SCANCODE_UP]))
              {
                game->man.dy =0;
              }

              if(state[SDL_SCANCODE_UP])
              {
                game->man.dy -=0.22;
              }

              
            }
          
        }
    }

  ///Tecla para lanzar barril
  if(state[SDL_SCANCODE_P])
  {
    
    *newBarril = *newBarril + 1; 
  }
  ///Tecla para lanzar barril que baja
  if(state[SDL_SCANCODE_U])
  {
    
    *newBarrilBaja = *newBarrilBaja + 1; 
  }
  ///Tecla para lanzar barrilMIx
  if(state[SDL_SCANCODE_O])
  {
    
    *newBarrilMix = *newBarrilMix + 1; 
  }
    
  if(!(state[SDL_SCANCODE_UP]))
  {
    game->man.up = 0;
  }

    ///Tecla para lanzar llamas
  if(state[SDL_SCANCODE_F])
  {
    
    *newLlamas = *newLlamas + 1; 
  }
    
  if(!(state[SDL_SCANCODE_UP]))
  {
    game->man.up = 0;
  }

  ///Caminar de mario a la izquierda
  if(state[SDL_SCANCODE_LEFT])
  {
    game->man.dx -= 0.5;
    if(game->man.dx < -6)
    {
      game->man.dx = -6;
    }
    game->man.izq = 0;
    game->man.slowingDown = 0;
  }
  ///Caminar de mario a la derecha
  else if(state[SDL_SCANCODE_RIGHT])
  {
    game->man.dx += 0.5;
    if(game->man.dx > 6)
    {
      game->man.dx = 6;
    }
    game->man.izq = 1;
    game->man.slowingDown = 0;
  }
  ///mario no camina, es decir frena al no apretar la decla de la derecha o la izquierda
  else
  {
    game->man.animFrame = 0;
    game->man.dx *= 0.8f;
    game->man.slowingDown = 1;
    if(fabsf(game->man.dx) < 0.1f)
    {
      game->man.dx = 0;
    }
  }

  return done;
}



///Metodo para dibujar en pantalla todo lo que sea solicitado
///Recibe un render y un gameState
void doRender(SDL_Renderer *renderer, GameState *game, int newBarril, int newLlama, int newBarrilBaja, int newBarrilMix)
{
    int i;
    ///si el juego esta en estado vidas
    if(game->statusState == STATUS_STATE_LIVES){
        draw_satus_lives(game);
    }
    ///si el juego est� en estado  de game over
    else if(game->statusState == STATUS_STATE_GAMEOVER)
    {
      draw_game_over(game);
    }
    ///si el juego est� en estado win
    else if(game->statusState == STATUS_STATE_WIN)
    {
      draw_game_win(game);
    }
    ///si el juego esta en estado juego
    else if(game->statusState == STATUS_STATE_GAME)
    {
        ///Pone al color negro como color de dibujo
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

  ///Pinta la ventana de color negro
  SDL_RenderClear(renderer);

  ///Pone al blanco como color de dibujo
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  ///dibuja las escaleras
  for (i = 0; i < 12; i++ ){
    SDL_Rect escaleraRect = { game->escaleras[i].x, game->escaleras[i].y, 30, 50 };
    SDL_RenderCopy(renderer, game->escalera1, NULL, &escaleraRect);
  }
  ///dibuja los estañones
  SDL_Rect estanonRect = {game->estanon.x, game->estanon.y, 40, 40};
  SDL_RenderCopy(renderer, game->estanonFrames[game->estanon.estanonFrame], NULL, &estanonRect);

  ///dibujando el suelo
  for(i = 0; i < 135; i++)
  {
    SDL_Rect sueloRect = { game->piso[i].x, game->piso[i].y, game->piso[i].w, game->piso[i].h };
    SDL_RenderCopy(renderer, game->suelo, NULL, &sueloRect);
  }

  ///dibujando a DK
  SDL_Rect DKRect = { game->dk.x, game->dk.y, 70, 70 };
  SDL_RenderCopy(renderer, game->DK[0], NULL, &DKRect);

  ///Dibuja a pailine 
  SDL_Rect paulineRect = {game->pauline.x, game->pauline.y, 30, 30};
  SDL_RenderCopy(renderer, game->paulineFrames[game->pauline.paulineFrame], NULL, &paulineRect);

  ///dibujando a barriles
  for (i = 0; i < newBarril; i++)
  {
    SDL_Rect barrilRect = { game->barriles[i].x, game->barriles[i].y, 20, 20 };
    SDL_RenderCopy(renderer, game->barril, NULL, &barrilRect);
  }
  
  ///Dibuja las llamas
  for (i = 0; i < newLlama; i++)
  {
    SDL_Rect llamaRect = { game->llamas[i].x, game->llamas[i].y, 20, 20 };
    SDL_RenderCopy(renderer, game->llamaFrames[game->llamas[i].llamaFrame], NULL, &llamaRect);
  }

  ///Dibuja las barriles que caen
  for (i = 0; i < newBarrilBaja; i++)
  {
    SDL_Rect BarrilBajaRect = { game->barrilBaja[i].x, game->barrilBaja[i].y, 20, 20 };
    SDL_RenderCopy(renderer, game->barrilBajaFrames[game->barrilBaja[i].barrilBajanFrame], NULL, &BarrilBajaRect);
  }

  ///Dibuja las barriles mix
  for (i = 0; i < newBarrilMix; i++)
  {
    SDL_Rect BarrilMixRect = { game->barrilMix[i].x, game->barrilMix[i].y, 20, 20 };
    SDL_RenderCopy(renderer, game->barrilMixFrames[game->barrilMix[i].barrilMixFrame], NULL, &BarrilMixRect);
  }

  ///dibujando a mario
  SDL_Rect rect = {game->man.x, game->man.y, 30, 30 };
  SDL_RenderCopyEx(renderer, game->marioFrames[game->man.animFrame], NULL, &rect, 0, NULL, (game->man.izq == 0));

  
  ///dibuja a mario cuando muere
  if(game->man.muerto)
    {
      SDL_Rect rect = { game->man.x, game->man.y, 30, 30 };
      SDL_RenderCopy(renderer, game->marioMuerto,
                       NULL, &rect);
    }

    }

  ///Terminamos de dibujar la base del juego
  SDL_RenderPresent(renderer);
}




///****************************Parte de los barriles**********************************************




///Metodo encargado de mover los barriles
void moveBarril(int newBarril ,GameState *game){

  //Verifica colision con el suelo
  for(int i = 0; i < 135; i++)
  {
    float mw = 25, mh = 25;
    for (int j = 0; j < newBarril; j++)
    {
      float mx = game->barriles[j].x, my = game->barriles[j].y;
      float bx = game->piso[i].x, by = game->piso[i].y, bw = game->piso[i].w, bh = game->piso[i].h;
  
      if(mx+mw > bx && mx<bx+bw)
      {
        ///Estamos callendo en el suelo
        if(my+mh > by && my < by && game->barriles[j].dy > 0)
        {
          ///corrige y
          game->barriles[j].y = by-mh;
          my = by-mh;
          game->barriles[j].dy = 0;

        }
      }
    } 

  }
  ///Encargada de que los barriles no se salgan de la pantalla
  for (int i = 0; i < newBarril; i++)
  {
    game->barriles[i].x += game->barriles[i].dx;
    game->barriles[i].y += game->barriles[i].dy;

  ///Verifica que el barril no se salga por la derecha
    if (game->barriles[i].x >= 600){
      game->barriles[i].dx *= -1;
        
    }
  ///Verifica que el barill no se salga por la izquierda
    if (game->barriles[i].x <= 0){
      game->barriles[i].dx *= -1;

    }
  }
}

///Metodo encargado de mover los barriles
void moveBarrilMix(int newBarrilMix ,GameState *game){

  //Verifica colision con el suelo
  for(int i = 0; i < 135; i++)
  {
    float mw = 25, mh = 25;
    for (int j = 0; j < newBarrilMix; j++)
    {
      float mx = game->barrilMix[j].x, my = game->barrilMix[j].y;
      float bx = game->piso[i].x, by = game->piso[i].y, bw = game->piso[i].w, bh = game->piso[i].h;
  
      if(mx+mw > bx && mx<bx+bw)
      {
        ///Estamos callendo en el suelo
        if(my+mh > by && my < by && game->barrilMix[j].dy > 0)
        {
          ///corrige y
          game->barrilMix[j].y = by-mh;
          my = by-mh;
          game->barrilMix[j].dy = 0;

        }
      }
    } 

  }
  ///Encargada de que los barriles no se salgan de la pantalla
  for (int i = 0; i < newBarrilMix; i++)
  {
    game->barrilMix[i].x += game->barrilMix[i].dx;
    game->barrilMix[i].y += game->barrilMix[i].dy;

  ///Verifica que el barril no se salga por la derecha
    if (game->barrilMix[i].x >= 600){
      game->barrilMix[i].dx *= -1;
        
    }
  ///Verifica que el barill no se salga por la izquierda
    if (game->barrilMix[i].x <= 0){
      game->barrilMix[i].dx *= -1;

    }
  }
}

  ///Mueve las llamas en diversos ciclos
void moveLlamas(int newLlamas ,GameState *game){

  //Verifica colision con el suelo
  for(int i = 0; i < 135; i++)
  {
    float mw = 25, mh = 25;
    for (int j = 0; j < newLlamas; j++)
    {
      float mx = game->llamas[j].x, my = game->llamas[j].y;
      float bx = game->piso[i].x, by = game->piso[i].y, bw = game->piso[i].w, bh = game->piso[i].h;
  
      if(mx+mw > bx && mx<bx+bw)
      {
        ///Estamos callendo en el suelo
        if(my+mh > by && my < by && game->llamas[j].dy > 0)
        {
          ///corrige y
          game->llamas[j].y = by-mh;
          my = by-mh;
          game->llamas[j].dy = 0;

        }
      }
    } 

  }
  ///Encargada de que las llamas no se salgan de la pantalla
  for (int i = 0; i < newLlamas; i++)
  {
    game->llamas[i].x += game->llamas[i].dx;
    game->llamas[i].y += game->llamas[i].dy;

  ///Verifica que el llamas no se salga por la derecha
    if (game->llamas[i].x >= 600){
      game->llamas[i].dx *= -1;
        
    }
  ///Verifica que el llamas no se salga por la izquierda
    if (game->llamas[i].x <= 0){
      game->llamas[i].dx *= -1;

    }
  }

}

///Crea un barril cada vez que se presiona el botón
void createBarril(int newBarril, GameState *game)
{
  game->barriles[newBarril].x = 100;
  game->barriles[newBarril].y = 120;
  game->barriles[newBarril].dx = 1;
  game->barriles[newBarril].dy = 0;
}

///Crea una llama cada vez que se presiona el botón F
void createLlama(int newLlamas, GameState *game)
{
  game->llamas[newLlamas].x = 50;
  game->llamas[newLlamas].y = 620;
  game->llamas[newLlamas].dx = 1;
  game->llamas[newLlamas].dy = 0;
  game->llamas[newLlamas].llamaFrame = 0;
  game->llamas[newLlamas].gravedad = 1;
  game->llamas[newLlamas].check = 1;
  
}

///Crea un barril que baja cada vez que se presiona el botón P
void createBarrilBaja(int newBarrilBaja, int dy, GameState *game)
{
  int numero;
  numero = rand() % 600; 
  game->barrilBaja[newBarrilBaja].x = numero;
  game->barrilBaja[newBarrilBaja].y = 120;
  game->barrilBaja[newBarrilBaja].dy = dy;
  game->barrilBaja[newBarrilBaja].barrilBajanFrame = 0;
  
  
}
void createBarrilMix(int newBarrilMix, GameState *game){
  game->barrilMix[newBarrilMix].x = 100;
  game->barrilMix[newBarrilMix].y = 120;
  game->barrilMix[newBarrilMix].mix = 1;
  game->barrilMix[newBarrilMix].barrilMixFrame = 0;
  game->barrilMix[newBarrilMix].dx = 1;
  game->barrilMix[newBarrilMix].dy = 0;
}

///Mueve a Pauline 
void movePauline(GameState *game){
    game->pauline.x += game->pauline.dx;
    

  ///Verifica que pauline no se salga por la derecha
    if (game->pauline.x >= 300){
      game->pauline.dx *= -1;
        
    }
  ///Verifica que pauline no se salga por la izquierda
    if (game->pauline.x <= 100){
      game->pauline.dx *= -1;

    }
}

///Mueve el barril que cae en y
void moveBarrilBaja(int newBarrilBaja ,GameState *game){
  int i;
  for (int i = 0; i < newBarrilBaja; i++)
  {
    game->barrilBaja[i].y += game->barrilBaja[i].dy;
  }
}

int barrel_event(char *buffer) {
  int n = 0;
  while(buffer[n] != '\0'){
    n++;
  }
  if(buffer[n-1] == '1') {
    return 1;
  }
  else if(buffer[n-1] == '2') {
    return 2;
  }
  else if(buffer[n-1] == '3') {
    return 3;
  }
  return 0;
}

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


/// Funcion main, esta funcion nos permite correr el juego juntando todo lo
/// necesario para el buen funcionamiento
int main(int argc, char *argv[])
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

  GameState gameState;
  SDL_Window *window = NULL;        /// Declara la ventana
  SDL_Renderer *renderer = NULL;    /// Declara el renderer

  SDL_Init(SDL_INIT_VIDEO);        /// Inicializa SDL2, la libreria de juego



  ///Crea la ventana del juego con las siguientes caracteristicas:
  window = SDL_CreateWindow("DK Arcade",                  /// titulo de la ventana
                            SDL_WINDOWPOS_UNDEFINED,      /// posicion en x
                            SDL_WINDOWPOS_UNDEFINED,      /// posicion en y
                            600,                          /// width, en pixeles
                            700,                          /// height, en pixeles
                            0                             /// flags
                            );

  ///crea un render para dibujar todo en la ventana
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  ///asigna al render creado el render con el gameState
  gameState.renderer = renderer;

  SDL_RenderSetLogicalSize(renderer, 600, 700);

  ///Inicializar el font
  TTF_Init();

  ///Llama al metodo loadGame que carga las bases de juego
  loadGame(&gameState);

  /// Abre la ventana
  int done = 0;
  ///Variables para crear barriles
  int temporalBarril = 0;
  int newBarril = 0;
  ///Variables para crear llamas
  int temporalLlama = 0;
  int newLlama = 0;
  ///Variables para crear barriles que bajan
  int temporalBarrilBaja = 0;
  int newBarrilBaja = 0;
  ///Variables para crear barriles mix 
  int temporalBarrilMix = 0;
  int newBarrilMix = 0;

  /// Loop del evento principal del juego
  while(!done)
  {
    // Da al informacion del juego al servidor
    send_info(sockfd, &gameState, &temporalBarril, &temporalBarrilBaja, &temporalBarrilMix);
    
    ///Verifica eventos
    done = processEvents(window, &gameState, &temporalBarril, &temporalLlama, &temporalBarrilBaja, &temporalBarrilMix);

    ///Verifica  que los como se crean lo barriles para saber cuantos se deben pintar
    if (temporalBarril > 0 && newBarril < NUM_BARRILES) 
    {
      ///init barril
      createBarril(newBarril, &gameState);
      newBarril += 1;
      temporalBarril = 0;
    }

    ///Verifica como se crean las llamas para saber cuantos se deben pintar
    if (temporalLlama > 0 && newLlama < NUM_LLAMAS) 
    {
      ///init llama
      createLlama(newLlama, &gameState);
      newLlama += 1;
      temporalLlama = 0;
    }

    ///Verifica como se crean los barriles que bajan para saber cuantos se deben pintar
    if (temporalBarrilBaja > 0 && newBarrilBaja < NUM_BARRIL_BAJA) 
    {
      ///init llama
      createBarrilBaja(newBarrilBaja, 1, &gameState);
      newBarrilBaja += 1;
      temporalBarrilBaja = 0;
    }
    ///Verifica como se crean los barriles mix para saber cuantos se deben pintar
    if (temporalBarrilMix > 0 && newBarrilMix < NUM_BARRIL_BAJA) 
    {
      ///init llama
      createBarrilMix(newBarrilMix, &gameState);
      newBarrilMix += 1;
      temporalBarrilMix = 0;
    }

    ///Llama al metodo process que nos permite crear las animaciones de movimiento
    process(newBarril, newLlama, newBarrilBaja, newBarrilMix, &gameState);
    ///Llama al metodo que verifica colosiones entre objetos
    collisionDetect(&gameState);

    ///Llama al metodo que dezplega el render
    doRender(renderer, &gameState, newBarril, newLlama, newBarrilBaja, newBarrilMix);

    ///Llama el método para rodar barril
    moveBarril(newBarril, &gameState);

    ///Llama al método moverBarrilMix
    moveBarrilMix(newBarrilMix, &gameState);

    ///Llama el método para mover llamas
    moveLlamas(newLlama, &gameState);

    moveBarrilBaja(newBarrilBaja, &gameState);

    ///Mover Pauline 
    movePauline(&gameState);

  }


  ///Al cerrar el juego destruye las texturas para liberar memoria
  //SDL_DestroyTexture(gameState.DK);
  SDL_DestroyTexture(gameState.marioFrames[0]);
  SDL_DestroyTexture(gameState.marioFrames[1]);
  SDL_DestroyTexture(gameState.suelo);
  if(gameState.label != NULL)
    SDL_DestroyTexture(gameState.label);
  TTF_CloseFont(gameState.font);




  ///Cierra y destruye la ventana y el render
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  ///Destruye el font
  TTF_Quit();

  //Cierra el socket
  close(sockfd);

  /// Limpia todo y se sale
  SDL_Quit();
  return 0;
}
