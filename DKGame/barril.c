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


///****************************Parte de los barriles**********************************************

void masVel(GameState *game){
  int i;
  for(i=0; i < NUM_BARRILES; i++)
  {
    game->barriles[i].masVel +=0.25;
    
  }
  for(i=0; i < NUM_BARRIL_BAJA; i++)
  {
    game->barrilBaja[i].masVel +=0.25;
    
  }
  for(i=0; i < NUM_BARRIL_MIX; i++)
  {
    game->barrilMix[i].masVel +=0.25;
    
  }
  
}


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
  int numero;
  numero = rand() % 20; 

  //Verifica colision con el suelo
  for(int i = 0; i < 135; i++)
  {
    float mw = 25, mh = 25;
    for (int j = 0; j < newBarrilMix; j++)
    {

      if(numero < 10 && game->barrilMix[j].controlador == 0){
        game->barrilMix[j].mix = 0;
      }

      else if(game->barrilMix[j].mix == 1)
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
      else if(game->barrilMix[j].mix == 0)
        {
          if(game->barrilMix[j].controlador <= 5){
            game->barrilMix[j].y += 2;
            game->barrilMix[j].controlador += 1;
          }
          else
          {
            game->barrilMix[j].mix = 1;
            game->barrilMix[j].controlador = 0;
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
  game->barriles[newBarril].collidFire = 0;
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
  numero = rand() % 595; 
  game->barrilBaja[newBarrilBaja].x = numero;
  game->barrilBaja[newBarrilBaja].y = 120;
  game->barrilBaja[newBarrilBaja].dy = dy + game->barrilBaja[newBarrilBaja].masVel;
  game->barrilBaja[newBarrilBaja].barrilBajanFrame = 0;
  game->barrilBaja[newBarrilBaja].collideFire = 0;
  
  
}
void createBarrilMix(int newBarrilMix, GameState *game){
  game->barrilMix[newBarrilMix].x = 100;
  game->barrilMix[newBarrilMix].y = 120;
  game->barrilMix[newBarrilMix].mix = 1;
  game->barrilMix[newBarrilMix].barrilMixFrame = 0;
  game->barrilMix[newBarrilMix].dx = 1+ game->barrilMix[newBarrilMix].masVel;
  game->barrilMix[newBarrilMix].dy = 0;
  game->barrilMix[newBarrilMix].controlador = 0;
  game->barrilMix[newBarrilMix].collideFire = 0;
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