#include <string.h>
#include "main.h"
#include "t6963c.h"
#include "bdd.h"
#include "gameboard.h"
#include "voiture.h"
#include "test.h"

/**
 * Modifie les coordonnées de la postion de la voiture selon la direction.
 * @param voiture La description de la voiture.
 */
void VOITURE_move(Voiture *voiture) {
   switch (voiture->direction) {
      case MOVES_UP:
     voiture->position.y --;
      break;
      case MOVES_DOWN:
     voiture->position.y ++;
      break;
      }
}

/** 
  * Contrôles si la pièce de la voiture est valide 
  * ou pas avec sa position.
  */

Status VOITURE_poisitionCTR(unsigned char c, unsigned char y ){
	
	Status status_life;

	if((y > VOITURE_LIMIT_Y0 ) && (y < VOITURE_LIMIT_Y1 )){
                status_life=ALIVE;
            }else{
                status_life=DEAD;
            }
	switch (c){
        case EMPTY:
            /*if((y > VOITURE_LIMIT_Y0 ) && (y < VOITURE_LIMIT_Y1 )){
                status_life=ALIVE;
            }else{
                status_life=DEAD;
            }*/
            break;
        case OBSTACLE:
            status_life=DEAD;
            break;
    }
	
	return status_life;

}	


/**
 * Décide si la voiture vit ou meurt selon
 * sa position et ce qui se trouve à cet endroit.
 * @param voiture La description de la voiture.
 * Rappel composition de la voiture :
 * Left Back  | Left Front
 * Right Back | Right Front
 */
void VOITURE_liveOrDie(Voiture *voiture){


    unsigned char left_back = T6963C_readFrom(voiture->position.x, voiture->position.y);
	unsigned char left_front = T6963C_readFrom(voiture->position.x+1, voiture->position.y);
	unsigned char right_back = T6963C_readFrom(voiture->position.x, voiture->position.y+1);
    unsigned char right_front = T6963C_readFrom(voiture->position.x+1, voiture->position.y+1);
	unsigned char right_add = T6963C_readFrom(voiture->position.x+2, voiture->position.y);
    unsigned char left_add = T6963C_readFrom(voiture->position.x+2, voiture->position.y+1);

	if(voiture->direction==NONE){
		voiture->status = VOITURE_poisitionCTR(right_add,voiture->position.y);
		if(voiture->status == ALIVE){voiture->status = VOITURE_poisitionCTR(left_add,voiture->position.y);}
	}else{
	
		//Contrôle si la voiture est en mouvement
		voiture->status = VOITURE_poisitionCTR(left_back,voiture->position.y);
		if(voiture->status == ALIVE){voiture->status = VOITURE_poisitionCTR(left_front,voiture->position.y);}
		if(voiture->status == ALIVE){voiture->status = VOITURE_poisitionCTR(right_back,voiture->position.y+1);}
		if(voiture->status == ALIVE){voiture->status = VOITURE_poisitionCTR(right_front,voiture->position.y+1);}
	}

	

	
}



void VOITURE_show(Voiture *voiture){

   T6963C_writeAt(voiture->position.x,voiture->position.y,VOITURE_BACK_LEFT);
   T6963C_writeAt(voiture->position.x+1,voiture->position.y,VOITURE_FRONT_LEFT);
   T6963C_writeAt(voiture->position.x,voiture->position.y+1,VOITURE_BACK_RIGHT);
   T6963C_writeAt(voiture->position.x+1,voiture->position.y+1,VOITURE_FRONT_RIGHT); 
   
   if (voiture->direction == MOVES_UP){
		T6963C_writeAt(voiture->position.x,voiture->position.y+2,EMPTY);
		T6963C_writeAt(voiture->position.x+1,voiture->position.y+2,EMPTY);
	}

	if (voiture->direction == MOVES_DOWN){
		T6963C_writeAt(voiture->position.x,voiture->position.y-1,EMPTY);
		T6963C_writeAt(voiture->position.x+1,voiture->position.y-1,EMPTY);
	}


	
}

/**
 * Décide de varier la direction de la voiture selon la direction indiquée.
 * @param voiture La description de la voiture.
 * @param arrow La direction désirée.
 */
void VOITURE_turn(Voiture *voiture, Arrow arrow){
switch (arrow) {
        case ARROW_UP:
                    voiture->direction=MOVES_UP;
        break;
        
        case ARROW_DOWN:
                    voiture->direction=MOVES_DOWN;
        break;
                
        case ARROW_NEUTRAL:
                voiture->direction=NONE;
        break;
    }
}

/**
 * Effectue une itération dans la vie de la voiture.
 * @param viture La définition de la voiture.
 * @return L'état de la voiture après l'itération.
 */
Status VOITURE_iterate(Voiture *voiture, Arrow arrow){ 
   if(voiture->direction != NONE){
      VOITURE_move(voiture);
   }
   VOITURE_show(voiture);
   VOITURE_turn(voiture, arrow);

   VOITURE_liveOrDie(voiture);

   return voiture->status;

}

#ifdef TEST

// ========================== Tests unitaires =================================
// Chaque test vérifie le comportement d'une fonctionnalité en établissant
// un état initial et en vérifiant l'état final.
int testVoitureTurnsTo (Direction currentDirection, Arrow turn, Direction expectedResult, char *testCode) {
   Voiture voiture = {MOVES_UP, {10, 10}, ALIVE};
   voiture.direction = currentDirection;
   VOITURE_turn(&voiture, turn);
   
   return assertEquals(expectedResult, voiture.direction, testCode);        
}

int testVoitureTurns() {
   int testsInError = 0;
   
   testsInError += testVoitureTurnsTo(MOVES_DOWN, ARROW_UP,    MOVES_UP,    "VT01");
   testsInError += testVoitureTurnsTo(MOVES_DOWN, ARROW_DOWN,    MOVES_DOWN,    "VT02");
   
   testsInError += testVoitureTurnsTo(MOVES_UP, ARROW_UP,    MOVES_UP,    "VT11");
   testsInError += testVoitureTurnsTo(MOVES_UP, ARROW_DOWN,    MOVES_DOWN,    "VT12");
   
   return testsInError;
}

int testVoitureMoves() {
   int testsInError = 0;
   Voiture voiture;
   voiture.position.x = 10;
   voiture.position.y = 10;
   
   voiture.direction = MOVES_UP;
   VOITURE_move(&voiture);
   testsInError += assertEquals(9, voiture.position.y, "VM001");
   
   voiture.direction = MOVES_DOWN;
   VOITURE_move(&voiture);
   testsInError += assertEquals(10, voiture.position.y, "VM002");
   
   return testsInError;
}

int testVoitureHitsABorder() {
    int testsInError = 0;

    Voiture voiture;

    voiture.status = ALIVE;
    voiture.position.x = VOITURE_LIMIT_X0 + 1;
    voiture.position.y = VOITURE_LIMIT_Y0 + 1;
    VOITURE_liveOrDie(&voiture);
    testsInError += assertEquals(voiture.status, ALIVE, "VH01");

    voiture.status = ALIVE;
    voiture.position.x = VOITURE_LIMIT_X0 + 1;
    voiture.position.y = VOITURE_LIMIT_Y0;
    VOITURE_liveOrDie(&voiture);
    testsInError += assertEquals(voiture.status, DEAD, "VH02");

    voiture.status = ALIVE;
    voiture.position.x = VOITURE_LIMIT_X1 - 1;
    voiture.position.y = VOITURE_LIMIT_Y1 - 1;
    VOITURE_liveOrDie(&voiture);
    testsInError += assertEquals(voiture.status, DEAD, "VH03");

    return testsInError;
}

// =========================== Tests de comportement ============================
// Chaque test:
// 1- Établit un état initial.
// 2- Simule un scénario qu'un utilisateur pourrait réaliser manuellement.
// 3- Vérifie, en contrôlant le contenu de l'écran, que ce 
//    que percevrait l'utilisateur est juste


/**
 * Collection de tests.
 * Les tests en erreur sont affichés à l'écran.
 * @return Le nombre de tests échoués.
 */
int testVoiture() {
    int testsInError = 0;

    // Tests unitaires:
    testsInError += testVoitureTurns();
    testsInError += testVoitureMoves();
    testsInError += testVoitureHitsABorder();

    // Tests de comportement:
    //testsInError += bddSnakeHitsAnObstacle();

    // Nombre de tests en erreur:
    return testsInError;
}

#endif