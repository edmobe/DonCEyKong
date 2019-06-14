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

///Metodo que nos permite realizar animaciones con las imagenes
///recibe un gameState
void process(int newBarril, int newLlama, int newBarrilBaja, int newBarrilMix, GameState *game, int *newLlam, int *newBarri, int *newBarrilBaj, int *newBarrilMi)
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

      ///Animación de DK
      if (game->time % 8 == 0){
        if(game->dk.DKFrame == 0)
          {
            game->dk.DKFrame = 1;
                   
          }
          else if(game->dk.DKFrame == 1)
          {
            game->dk.DKFrame = 2;

          } 
          else 
          {
            game->dk.DKFrame = 0;
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
          game->man.y = 625;
          game->man.dx = 0;
          game->man.dy = 0;
          game->man.enSuelo = 0;
          *newBarri=0;
          *newBarrilBaj=0;
          *newBarrilMi=0;
          *newLlam=0;
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