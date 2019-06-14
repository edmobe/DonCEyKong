#ifndef Tarea3_socket_h
#define Tarea3_socket_h

///Prototipo de la funcion barrel_event
int barrel_event(char *buffer);

///Prototipo de la funcion send_info
void send_info(int sockfd, GameState *game, int *newBarril, int *newBarrilBaja, int *newBarrilMix);

#endif /// Tarea3_socket.h