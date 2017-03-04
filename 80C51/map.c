#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "t6963c.h"

#include "map.h"
#include "gameboard.h"


unsigned char __xdata LTBLMAP[11][17];  // Y /X
unsigned int min =0;
unsigned int max = 8;
		

unsigned char getMAP(unsigned int x, unsigned int y){
	return LTBLMAP[y][x];
}

void MAP_initialize(){
	unsigned int hauteur=0;
	unsigned int i=0;


	for(i=0;i<WIDTH_MAP;i++){
		hauteur = MAP_hauteur(min,max);
		max = hauteur + 1;
		min =  hauteur - 1;
		MAP_create(i,hauteur);
	}
	

}

unsigned int MAP_hauteur(unsigned int min, unsigned int max){
	
	unsigned int random=0;
	random  = rand() % (max-min +1)+min ;
	//random = 5;
	return random;

}


void MAP_create(unsigned int ligne, unsigned int haut_obs){
	unsigned int n=0;

	for(n=0;n<=HEIGHT_MAP;n++){
		if(n < haut_obs){
			LTBLMAP[n][ligne]=1;
			
		}else{
			if(n < (haut_obs + SPACE_CAR)){
				LTBLMAP[n][ligne]=0;
			}else{
				LTBLMAP[n][ligne]=1;
			}
		}
	}

}
