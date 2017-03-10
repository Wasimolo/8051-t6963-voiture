#include <mcs51reg.h>
#include "stdio-t6963c.h"
#include "test.h"
#include "buffer.h"
#include "voiture.h"
#include "map.h"
#include "keyboard.h"
#include "gameboard.h"

#ifndef TEST

void pause(unsigned int t) {
	unsigned int n;
	for (n=0; n < t; n++);
}

void initialize() {
	STDIO_initialize();
	GMB_initialize();
	MAP_initialize();
}

void play() {
	unsigned char *keyboard = (unsigned char __xdata *) 0x3000;
	unsigned char position=0;
	Voiture voiture = {NONE, {2, 10}, ALIVE};
	Arrow arrow;

	do {
		arrow = KEYBOARD_readArrows(keyboard);
		voiture.status = VOITURE_iterate(&voiture, arrow);
		position = GMP_MAP();
		VOITURE_show(&voiture);
		if(position == LONG_MAP){voiture.status = END; }

	} while (voiture.status == ALIVE);
	if(voiture.status == DEAD){	
		GMB_display(3, 7, " La voiture est raide ");
	}else{
		GMB_display(3, 7, " Fin . BARVO !!! ");
	}
}

void title(){
	unsigned char *keyboard = (unsigned char __xdata *) 0x3000;
	Voiture voiture_titre_1 = {NONE, {2, 3}, ALIVE};
	Voiture voiture_titre_2 = {NONE, {10, 13}, ALIVE};
	Voiture voiture_titre_3 = {NONE, {20, 2}, ALIVE};
	Voiture voiture_titre_4 = {NONE, {26, 12}, ALIVE};
	Arrow arrow;

	GMB_display(3, 7, "JuRocing:Rally Race 4.0");
	VOITURE_show(&voiture_titre_1);
	VOITURE_show(&voiture_titre_2);
	VOITURE_show(&voiture_titre_3);
	VOITURE_show(&voiture_titre_4);
	do{
		arrow = KEYBOARD_readArrows(keyboard);
	}while(arrow == ARROW_NEUTRAL);
	
	GMB_clear(VOITURE_LIMIT_X0,VOITURE_LIMIT_Y0,VOITURE_LIMIT_X1,VOITURE_LIMIT_Y1);

	return;

}

void main(void) {

	initialize();
	title();
	play();

	while(1);

}

#else
#include <stdio.h>
void main(void) {
   int testsInError = 0;
   printf("%d\n",testsInError);
   STDIO_initialize();
   testsInError += testVoiture();
   testsInError += testMap();
   testsInError += testGameboard();
   
   printf("%d tests en erreur", testsInError);
   
   while(1);
}
#endif