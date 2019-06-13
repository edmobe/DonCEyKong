#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define STATUS_STATE_LIVES 0
#define STATUS_STATE_GAME 1
#define STATUS_STATE_GAMEOVER 2
#define STATUS_STATE_WIN 3

#define NUM_PISO 135
#define NUM_BARRILES 15
#define NUM_BARRIL_BAJA 15
#define NUM_BARRIL_MIX 15
#define NUM_ESCALERAS 12
#define NUM_LLAMAS 50

#ifndef Tarea3_main_h
#define Tarea3_main_h

///estructura de mario
typedef struct
{
  float x, y;
  float dx, dy;
  int enSuelo, muerto;
  int lives;
  int up, down;

  int animFrame, izq, slowingDown;
} Man;

///EStructura de Pauline
typedef struct
{
  int x, y, dx, paulineFrame;
}Pauline;

///estructura de DK
typedef struct
{
  int x, y;
} Enemy;

///estructura del piso
typedef struct
{
    int x, y, w, h;
}Piso;

///Estructura del barril 1
typedef struct
{
    int x, y;
    float dx, dy;
}Barril;

///Bariles bajan
typedef struct
{
    int x, y, barrilBajanFrame;
    float dy;
}BarrilBajan;

///Barril Mix
typedef struct
{
    int x, y, barrilMixFrame, mix, animation;
    float dy, dx;
}BarrilMix;

///Estructura de las llamas
typedef struct 
{
  int x, y, llamaFrame, gravedad, check;
  float dx, dy;
}Llama;

///Estructura para la escalera
typedef struct 
{
   int x, y;
}Escalera;

typedef struct
{
  int x, y, estanonFrame;
}Estanon;

///estructura para los estados de juego basicamente se pasan
///las estructuras que se crean en el juego
typedef struct
{
  ///Players
  Man man;

  ///Donkey kong
  Enemy dk;

  ///Pauline
  Pauline pauline;

  ///Llama
  Llama llamas[NUM_LLAMAS];

  ///Estañon de fuego
  Estanon estanon;

  ///Piso
  Piso piso[NUM_PISO];

  ///Barriles
  Barril barriles[NUM_BARRILES];

  ///Barriles que bajan
  BarrilBajan barrilBaja[NUM_BARRIL_BAJA];

  ///Barriles mix
  BarrilMix barrilMix[NUM_BARRIL_MIX];

  ///Escalera
  Escalera escaleras[NUM_ESCALERAS];

  ///Images
  SDL_Texture *barrilMixFrames[6];
  SDL_Texture *barrilBajaFrames[2];
  SDL_Texture *llamaFrames[5];
  SDL_Texture *paulineFrames[5];
  SDL_Texture *barril;
  SDL_Texture *estanonFrames[2];
  SDL_Texture *escalera1;
  SDL_Texture *DK[2];
  SDL_Texture *marioFrames[2];
  SDL_Texture *marioMuerto;
  SDL_Texture *suelo;
  SDL_Texture *label;
  int labelW, labelH;

  ///Fonts
  TTF_Font *font;

  ///tiempo
  int time, deathCountdown;
  int statusState;

  ///Renderer
  SDL_Renderer *renderer;
} GameState;


#endif /// Tarea3_main_h
