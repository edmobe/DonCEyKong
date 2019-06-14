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


///Util funcion que nos permite saber si dos rectangulos (imagenes) estan chocando
int collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2)
{
  return (!((x1 > (x2+wt2)) || (x2 > (x1+wt1)) || (y1 > (y2+ht2)) || (y2 > (y1+ht1))));
}




///Metodo para verificar las colisiones
///Recibe un gameState
void collisionDetect(int *newLlama, GameState *game, int *newBarril, int *newBarrilBaja, int *newBarrilMix, int *newLlam)
{

  ///Verifica si mario se cae
  if(game->man.y > 700){
    game->man.muerto = 1;
  }
   ///Verifica choques con barriles y mario y llamas
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
  for(i = 0; i < NUM_BARRIL_MIX; i++)
  {
    if(collide2d(game->man.x, game->man.y, game->barrilMix[i].x, game->barrilMix[i].y, 30, 30, 20, 20))
    {
      game->man.muerto = 1;
    }
  }
  for(i = 0; i < NUM_LLAMAS; i++)
  {
    if(collide2d(game->man.x, game->man.y, game->llamas[i].x, game->llamas[i].y, 30, 30, 20, 20))
    {
      game->man.muerto = 1;
    }
  }
  if(collide2d(game->man.x, game->man.y, game->dk.x, game->dk.y, 30, 30, 70, 70))
    {
      game->man.muerto = 1;
    }

  ///Choque de barril con el estañon
  for(i = 0; i < NUM_BARRILES; i++)
  {
    if(collide2d(game->estanon.x, game->estanon.y, game->barriles[i].x, game->barriles[i].y, 20, 20, 40, 40) && game->barriles[i].collidFire == 0)
    {
      *newLlama = *newLlama + 1;
      game->barriles[i].collidFire = 1;
      
     
    }
  }
  for(i = 0; i < NUM_BARRIL_BAJA; i++)
  {
    if(collide2d(game->estanon.x, game->estanon.y, game->barrilBaja[i].x, game->barrilBaja[i].y, 20, 20, 40, 40) && game->barrilBaja[i].collideFire == 0)
    {
      *newLlama = *newLlama + 1;
      game->barrilBaja[i].collideFire = 1;
    }
  }
  for(i = 0; i < NUM_BARRIL_MIX; i++)
  {
    if(collide2d(game->estanon.x, game->estanon.y, game->barrilMix[i].x, game->barrilMix[i].y, 20, 20, 40, 40) && game->barrilMix[i].collideFire == 0)
    {
      *newLlama = *newLlama + 1;
      game->barrilMix[i].collideFire = 1;

    }
  }

  ///Colisiones de las llamas con las escaleras
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
        game->statusState = STATUS_STATE_LIVES;
        game->time = 0;

          ///reset
          game->man.muerto = 0;
          game->man.x = 100;
          game->man.y = 625;
          game->man.dx = 0;
          game->man.dy = 0;
          game->man.enSuelo = 0;
          game->man.lives++;
          masVel(game);
          *newBarril=0;
          *newBarrilBaja=0;
          *newBarrilMix=0;
          *newLlam=0;
          

          
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