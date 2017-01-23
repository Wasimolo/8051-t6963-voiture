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
	Voiture voiture = {NONE, {10, 10}, ALIVE};
	Arrow arrow;

	GMB_draw(VOITURE_LIMIT_X0, VOITURE_LIMIT_Y0, VOITURE_LIMIT_X1, VOITURE_LIMIT_Y1);
	MAP_initialize();


	do {
		arrow = KEYBOARD_readArrows(keyboard);
		voiture.status = VOITURE_iterate(&voiture, arrow);
		pause(20000);
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

	while(1);
}
#endif