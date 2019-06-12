#include <stdio.h>
#include "main.h"
#include <SDL2/SDL.h>

///Funcion que inicia el estado de vida
///Recibe un gameState
void init_status_lives(GameState *game)
{
    char vida[128] = "";
    sprintf(vida, "x %d", (int)game->man.lives);
    SDL_Color white ={255,255,255,255};

    SDL_Surface *tmp = TTF_RenderText_Blended(game->font, vida, white);
    game->labelW = tmp->w;
    game->labelH=tmp->h;
    game->label =SDL_CreateTextureFromSurface(game->renderer, tmp);
    SDL_FreeSurface(tmp);


}
///Funcion que dibuja el estado de vida
///Recibe un gameState
void draw_satus_lives(GameState *game)
{
    SDL_SetRenderDrawColor(game->renderer, 25, 25, 20, 20);

    SDL_RenderClear(game->renderer);

    ///dibujando a mario
  SDL_Rect rect = { 220, 216, 30, 30 };
  SDL_RenderCopyEx(game->renderer, game->marioFrames[0], NULL, &rect, 0, NULL, (game->man.izq == 0));

    ///color blanco para dibujar
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    ///dibuja el label en pantalla
    SDL_Rect textRect = {320, 240-game->labelH/2, game->labelW,game->labelH};
    SDL_RenderCopy(game->renderer, game->label, NULL, &textRect);

}
///Funcion que cierra el estado de vida
///Recibe un gameState
void shutdown_status_lives(GameState *game)
{
    SDL_DestroyTexture(game->label);
    game->label=NULL;
}




void init_game_over(GameState *game)
{
  //Create label textures for status screen
  SDL_Color white = { 255, 255, 255, 255 };

  SDL_Surface *tmp = TTF_RenderText_Blended(game->font, "GAME OVER!", white);
  game->labelW = tmp->w;
  game->labelH = tmp->h;
  game->label = SDL_CreateTextureFromSurface(game->renderer, tmp);
  SDL_FreeSurface(tmp);
}

void draw_game_over(GameState *game)
{
  SDL_Renderer *renderer = game->renderer;
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  //Clear the screen
  SDL_RenderClear(renderer);

  //set the drawing color to white
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  SDL_Rect textRect = { 320-game->labelW/2, 240-game->labelH/2, game->labelW, game->labelH };
  SDL_RenderCopy(renderer, game->label, NULL, &textRect);
}

void shutdown_game_over(GameState *game)
{
  SDL_DestroyTexture(game->label);
  game->label = NULL;
}

void init_game_win(GameState *game)
{
  //Create label textures for status screen
  SDL_Color white = { 255, 255, 255, 255 };

  SDL_Surface *tmp = TTF_RenderText_Blended(game->font, "You live..", white);
  game->labelW = tmp->w;
  game->labelH = tmp->h;
  game->label = SDL_CreateTextureFromSurface(game->renderer, tmp);
  SDL_FreeSurface(tmp);
}

void draw_game_win(GameState *game)
{
  SDL_Renderer *renderer = game->renderer;
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  //Clear the screen
  SDL_RenderClear(renderer);

  //set the drawing color to white
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  SDL_Rect textRect = { 320-game->labelW/2, 240-game->labelH/2, game->labelW, game->labelH };
  SDL_RenderCopy(renderer, game->label, NULL, &textRect);
}

void shutdown_game_win(GameState *game)
{
  SDL_DestroyTexture(game->label);
  game->label = NULL;
}
