#ifndef Tarea3_collide_h
#define Tarea3_collide_h

///Prototipo de la funcion collide2d
int collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2);

///Prototipo de la funcion collisionDetect
void collisionDetect(int *newLlama, GameState *game, int *newBarril, int *newBarrilBaja, int *newBarrilMix, int *newLlam);

#endif /// Tarea3_collide.h