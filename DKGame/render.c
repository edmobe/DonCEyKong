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

//GUI
#define GRAVEDAD 0.70f



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
  SDL_RenderCopy(renderer, game->DK[game->dk.DKFrame], NULL, &DKRect);

  ///Dibuja a pauline 
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