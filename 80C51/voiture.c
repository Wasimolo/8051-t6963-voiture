#include <string.h>
#include "main.h"
#include "t6963c.h"
#include "bdd.h"
#include "gameboard.h"
#include "voiture.h"

void VOITURE_move(Voiture *voiture) {
	switch (voiture->direction) {
		case MOVES_UP:
				voiture->position.y --;
		break;
	
		case MOVES_DOWN:
				voiture->position.y ++;
	}
}

void VOITURE_liveOrDie(Voiture *voiture){
	unsigned char c = T6963C_readFrom(voiture->position.x, voiture->position.y);
	
	switch (c){
		case FRUIT:
			snake->status=EATING;
			break;
		case 0x00:
			if(((voiture->position.x > VOITURE_LIMIT_X0) && ((voiture->position.x < VOITURE_LIMIT_X1))) && ((voiture->position.y > VOITURE_LIMIT_Y0 ) && (voiture->position.y < VOITURE_LIMIT_Y1 ))){
				voiture->status=ALIVE;
			}else{
				voiture->status=DEAD;
			}
			break;
		default: 
			voiture->status=DEAD;
			break;
		}
}

void VOITURE_show(Voiture *voiture){}
	unsigned char nbr_corps=0;
	unsigned char x=0, y=0;
	unsigned int i=0;

		T6963C_writeAt(voiture->position.x,voiture->position.y,);
			
	//Initialise le snake avec un corps 
	if(snake->caloriesLeft> 0){ //snake->status = ALIVE  &&
	
		snake->caloriesLeft--;
	}else{

		if(snake->status==ALIVE){	

			x = BUFFER_out();
			y = BUFFER_out();
			T6963C_writeAt(x,y,EMPTY);
		}
	}
	
}

void VOITURE_turn(Voiture *voiture, Arrow arrow){
switch (arrow) {
		case ARROW_UP:
					voiture->direction=MOVES_UP;
		break;
		
		case ARROW_DOWN:
					voiture->direction=MOVES_DOWN;
		break;
				
		case ARROW_NEUTRAL:
				snake->direction=snake->direction;
		break;
	}
}

Status VOITURE_iterate(Voiture *voiture, Arrow arrow){ 

	return voiture->status;

}
