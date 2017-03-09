#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "t6963c.h"
#include "map.h"
#include "gameboard.h"


unsigned char __xdata LTBLMAP[LONG_MAP];  //Longueur MAP
unsigned int min =0;
unsigned int max = 8;

void MAP_initialize(){
	unsigned int hauteur=0;
	unsigned int i=0;
	MAP_begin();

	for(i=10;i<LONG_MAP;i++){
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
	for(i=0;i<=LONG_MAP;i++){
		LTBLMAP[i]= 1;
	}
}

unsigned int MAP_hauteur(unsigned int min, unsigned int max){
	
	unsigned int random=0;
	random  = rand() % (max-min +1)+min ;
	
	return random;
}

unsigned char getMAP(unsigned int x){
	return LTBLMAP[x];
}

