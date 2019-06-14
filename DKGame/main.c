//GUI
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

int barrel_event(char *buffer) {
    const int pos = 3;
    int i = 2;
    int n;
    for(n = 0; n < pos; n++){
      while(buffer[i] != '/') {
        i++;
      }
      i++;

    }

  if(buffer[i] == '1') {
    return 1;
  }
  else if(buffer[i] == '2') {
    return 2;
  }
  else if(buffer[i] == '3') {
    return 3;
  }
  return 0;
}

///*************************************************************************************************************
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

    buffer[i] = '/';
    buffer[i+1] = game->man.direction;

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
///******************************************************************************************************

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
    process(newBarril, newLlama, newBarrilBaja, newBarrilMix, &gameState, &newLlama, &newBarril, &newBarrilBaja, &newBarrilMix);
    ///Llama al metodo que verifica colosiones entre objetos
    collisionDetect(&temporalLlama, &gameState, &newBarril, &newBarrilBaja, &newBarrilMix, &newLlama);

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
