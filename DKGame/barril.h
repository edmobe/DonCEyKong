#ifndef Tarea3_barril_h
#define Tarea3_barril_h

///Prototipo de la funcion collide2d
void masVel(GameState *game);

///Prototipo de la funcion collisionDetect
void moveBarril(int newBarril ,GameState *game);

///Prototipo de la funcion movebarrilMix
void moveBarrilMix(int newBarrilMix ,GameState *game);

///Prototipo de la funcion moveLlamas
void moveLlamas(int newLlamas ,GameState *game);

///Prototipo de la funcion createBarril
void createBarril(int newBarril, GameState *game);

///Prototipo de la funcion createLlama
void createLlama(int newLlamas, GameState *game);

///Prototipo de la funcion createBarrilBaja
void createBarrilBaja(int newBarrilBaja, int dy, GameState *game);

///Prototipo de la funcion createBarrilMix
void createBarrilMix(int newBarrilMix, GameState *game);

///Prototipo de la funcion movePauline
void movePauline(GameState *game);

///Prototipo de la funcion moveBarrilBaja
void moveBarrilBaja(int newBarrilBaja ,GameState *game);

#endif /// Tarea3_barril.h