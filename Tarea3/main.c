#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <time.h>
#include "main.h"
#include "status.h"

#define GRAVEDAD 0.75f


///Metodo que carga toda la base de nuestro juego
///Recibe un gameState
void loadGame(GameState *game)
{
  SDL_Surface *surface = NULL;

  ///Carga la imagen del barril 1 y crea texturas con el render a partir de ella
  surface = IMG_Load("media/barril3.png");
  game->barril = SDL_CreateTextureFromSurface(game->renderer, surface);
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

  ///init el estado del juego
  game->statusState=STATUS_STATE_LIVES;

  ///init estado de la vidas
  init_status_lives(game);
  game->deathCountdown = -1;

  ///init barril
  game->barriles[0].x = 300;
  game->barriles[0].y = 100;

  ///init label para escribir en pantalla
  game->label=NULL;

  ///init el tiempo
  game->time = 0;

  ///init DK
  game->dk.x = 5;
  game->dk.y = 100;

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
    game->escaleras[i+1].y=temporal-40;
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
  for (int i = 10; i < 12; i += 2)
  {
    game->escaleras[i].x=315;
    game->escaleras[i].y=115;
    game->escaleras[i+1].x=315;
    game->escaleras[i+1].y=115-40;
    
  }


}







///Metodo que nos permite realizar animaciones con las imagenes
///recibe un gameState
void process(GameState *game)
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
        if(man->x > 38320)
      {
        init_game_win(game);
        game->statusState = STATUS_STATE_WIN;
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
  for(int i = 0; i < NUM_BARRILES; i++)
  {
    if(collide2d(game->man.x, game->man.y, game->barriles[i].x, game->barriles[i].y, 48, 48, 32, 32))
    {
      game->man.muerto = 1;
    }
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
int processEvents(SDL_Window *window, GameState *game)
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
              game->man.dy = -8;
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
    game->man.dy -= 0.2f;
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
void doRender(SDL_Renderer *renderer, GameState *game)
{
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
  for (int i = 0; i < 12; i++ ){
    SDL_Rect escaleraRect = { game->escaleras[i].x, game->escaleras[i].y, 30, 50 };
    SDL_RenderCopy(renderer, game->escalera1, NULL, &escaleraRect);
  }

  ///dibujando el suelo
  for(int i = 0; i < 135; i++)
  {
    SDL_Rect sueloRect = { game->piso[i].x, game->piso[i].y, game->piso[i].w, game->piso[i].h };
    SDL_RenderCopy(renderer, game->suelo, NULL, &sueloRect);
  }

  ///dibujando a DK
  SDL_Rect DKRect = { game->dk.x, game->dk.y, 50, 50 };
  SDL_RenderCopy(renderer, game->DK[0], NULL, &DKRect);

  ///dibujando a barriles
  SDL_Rect barrilRect = { game->barriles[0].x, game->barriles[0].y, 30, 30 };
  SDL_RenderCopy(renderer, game->barril, NULL, &barrilRect);

  ///dibujando a mario
  SDL_Rect rect = { game->man.x, game->man.y, 30, 30 };
  SDL_RenderCopy(renderer, game->marioFrames[game->man.animFrame], NULL, &rect);

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







/// Funcion main, esta funcion nos permite correr el juego juntando todo lo
/// necesario para el buen funcionamiento
int main(int argc, char *argv[])
{
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

  /// Loop del evento principal del juego
  while(!done)
  {
    ///Verifica eventos
    done = processEvents(window, &gameState);
    ///Llama al metodo process que nos permite crear las animaciones de movimiento
    process(&gameState);
    ///Llama al metodo que verifica colosiones entre objetos
    collisionDetect(&gameState);

    ///Llama al metodo que dezplega el render
    doRender(renderer, &gameState);

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

  /// Limpia todo y se sale
  SDL_Quit();
  return 0;
}
