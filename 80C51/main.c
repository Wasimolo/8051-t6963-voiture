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
}

void play() {
	unsigned char *keyboard = (unsigned char __xdata *) 0x3000;
	Voiture voiture = {NONE, {2, 10}, ALIVE};
	Arrow arrow;

	MAP_initialize();


	do {
		arrow = KEYBOARD_readArrows(keyboard);
		voiture.status = VOITURE_iterate(&voiture, arrow);
		GMP_MAP();
		VOITURE_show(&voiture);
		//pause(20000);
	} while (voiture.status != DEAD);
	GMB_display(3, 7, " La voiture est raide ");
}

void main(void) {

	initialize();
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
   
   printf("%d tests en erreur", testsInError);
   
   while(1);
}
#endif