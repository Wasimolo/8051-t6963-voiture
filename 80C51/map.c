#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "t6963c.h"

#include "map.h"
#include "gameboard.h"


unsigned char __xdata LTBLMAP[255];  //Longueur MAP
unsigned int min =0;
unsigned int max = 8;
		



void MAP_initialize(){
	unsigned int hauteur=0;
	unsigned int i=0;
	MAP_begin();
	/*LTBLMAP[0] = 1;
	LTBLMAP[12] = 7;
	LTBLMAP[13] = 6;
	LTBLMAP[14] = 5;
	LTBLMAP[15] = 4;
	LTBLMAP[16] = 3;
	LTBLMAP[17] = 5;
	LTBLMAP[18] = 4;
	LTBLMAP[19] = 3;
	LTBLMAP[20] = 5;
	LTBLMAP[21] = 4;
	LTBLMAP[22] = 3;
	LTBLMAP[23] = 5;
	LTBLMAP[24] = 4;
	LTBLMAP[25] = 3;*/

	for(i=10;i<255;i++){
		hauteur = MAP_hauteur(min,max);
			if (hauteur > 8) {
				max = 8;
			}else{
				max = hauteur + 1;
			}

			if(hauteur > 1){	
				min =  hauteur - 1;
			}
		LTBLMAP[i]=hauteur;
	}
	

}

void MAP_begin(){
	unsigned int i=0;
	for(i=0;i<=255;i++){
		LTBLMAP[i]= 1;
	}
}

unsigned int MAP_hauteur(unsigned int min, unsigned int max){
	
	unsigned int random=0;
	random  = rand() % (max-min +1)+min ;
	//random = 5;
	return random;
}

unsigned char getMAP(unsigned int x){
	return LTBLMAP[x];
}

