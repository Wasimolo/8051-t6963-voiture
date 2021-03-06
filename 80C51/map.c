#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "t6963c.h"
#include "map.h"
#include "gameboard.h"
#include "test.h"

unsigned char __xdata LTBLMAP[LONG_MAP];  //Longueur MAP
unsigned int min =0;
unsigned int max = 8;


/**
 * Initialise la map
 * Incr�mente de le tableau al�atoirement
 * 
 */

void MAP_initialize(){
	unsigned int hauteur=0;
	unsigned int i=0;
	MAP_begin();

	for(i=10;i<LONG_MAP;i++){
		hauteur = MAP_hauteur(min,max);
		MAP_minmax(&min,&max,hauteur);
		LTBLMAP[i]=hauteur;
	}
}

/**
 * Initialise les premi�res colonnnes de la map
 * haut de h pour placer la voiture sur la route correctement
 *
 */

void MAP_begin(){
	unsigned int i=0;
	for(i=0;i<=LONG_MAP;i++){
		LTBLMAP[i]= 1;
	}
}


/**
 * Retourne une valeur random dans l'interval min & max.
 * 
 * @param min Pointeur sur la variable minimum
 * @param min Pointeur sur la variable maximum
 *
 */

unsigned int MAP_hauteur(unsigned int min, unsigned int max){
	
	unsigned int random=0;
	random  = rand() % (max-min +1)+min ;
	
	return random;
}


/**
 * Modifie les valeurs min et max pour la fonction random
 * G�re un saut de 1 maximum
 * @param min Pointeur sur la variable minimum
 * @param min Pointeur sur la variable maximum
 *
 */

void MAP_minmax(unsigned int *min, unsigned int *max, unsigned int hauteur){
	if (hauteur > 8) {
				*max = 8;
			}else{
				*max = hauteur + 1;
			}

			if(hauteur > 1){	
				*min =  hauteur - 1;
			}
	return;

}

/**
 * Retourne valeur de la hauteur selon l'index
 * 
 * @param x Index du tableau
 */

unsigned char getMAP(unsigned int x){
	return LTBLMAP[x];
}

#ifdef TEST

int bddMapRandom() {
	 int testsInError = 0;
	 unsigned int nbr_rdm1=1;
	 unsigned int nbr_rdm2=1;
	 unsigned int nMin =0;
	 unsigned int nMax = 8;

	 
	 nbr_rdm1 = MAP_hauteur(nMin,nMax);
	 MAP_minmax(&nMin,&nMax,nbr_rdm1);
	 nbr_rdm2 = MAP_hauteur( nMin,nMax);


	 testsInError += assertNotEquals(nbr_rdm1, nbr_rdm2, "MAP01");
}

int testMap() {
	int testsInError = 0;	
	testsInError += bddMapRandom();

	return testsInError;
}


#endif
