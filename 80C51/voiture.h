#ifndef ___VOITURE_H
#define ___VOITURE_H

#include "keyboard.h"
#include "main.h"

typedef enum {
    MOVES_UP,
    MOVES_DOWN,
    NONE
} Direction;

typedef enum {
    ALIVE,
    DEAD,
	END
} Status;

typedef struct {
    Direction direction;
    Position position;
    Status status;
} Voiture;

void VOITURE_move(Voiture *voiture);
void VOITURE_liveOrDie(Voiture *voiture);
void VOITURE_show(Voiture *voiture);
void VOITURE_turn(Voiture *voiture, Arrow arrow);
Status VOITURE_iterate(Voiture *voiture, Arrow arrow);
#ifdef TEST
int testVoiture();
#endif

#endif