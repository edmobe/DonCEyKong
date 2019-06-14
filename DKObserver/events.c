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
      ///caso en que se apreta una tecla
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
              game->man.animFrame=2;
              ///Animación de mario en escaleras
              if (game->time % 8 == 0){
                if(game->man.animFrame == 2)
                {
                  game->man.animFrame = 3;
                   
                }              
                 else 
                {
                   game->man.animFrame = 2;
                }
              }
              if (!(collide2d(game->man.x, game->man.y, game->escaleras[i].x, game->escaleras[i].y, 30, 30, 30, 40)))
              { 
                game->man.animFrame=0;
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

///****************************************************************************************************************
  ///Caminar de mario a la izquierda
  if(game->man.direction  == 'L')
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
  else if(game->man.direction == 'R')
  {
    
    game->man.dx += 0.5;
    if(game->man.dx > 6)
    {
      game->man.dx = 6;
    }
    game->man.izq = 1;
    game->man.slowingDown = 0;
  }
  ///*****************************************************************************************************************
  ///mario no camina, es decir frena al no apretar la decla de la derecha o la izquierda
  else
  {
    game->man.direction = 'S';
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
