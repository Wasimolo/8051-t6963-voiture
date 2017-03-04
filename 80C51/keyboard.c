
#include "keyboard.h"
#include "test.h"

#define KEY_NONE 0xFF
#define KEY_8 0xFD
#define KEY_2 0xFD

/**
 * Detecte les touches 8 et 2 comme des fleches.
 * - '8' --> Fleche montante.
 * - '2' --> Fleche vers le bas.
 * @param keyboard Tableau avec l'état des 4 lignes du clavier.
 * @return La fleche correspondante à la touche enfoncée, ou ARROW_NEUTRAL
 * si aucune touche est enfoncée.
 */
Arrow KEYBOARD_readArrows(unsigned char *keyboard) {

   if (keyboard[0] == KEY_8){
      return ARROW_UP;
   }
   if (keyboard[2] == KEY_2){
      return ARROW_DOWN;
   }
   return ARROW_NEUTRAL;

}

#ifdef TEST

int testKeyboardArrows() {
	int testsInError = 0;
	unsigned char keys[4] = {KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE};

	testsInError += assertEquals(KEYBOARD_readArrows(keys), ARROW_NEUTRAL, "KB001");
	
	keys[0] = KEY_8;
	testsInError +=assertEquals(KEYBOARD_readArrows(keys), ARROW_UP, "KB002");
	keys[0] = KEY_NONE;
	keys[2] = KEY_2;
	testsInError +=assertEquals(KEYBOARD_readArrows(keys), ARROW_DOWN, "KB005");

	return testsInError;
}

int testKeyboard() {
	int testsInError = 0;

	testsInError += testKeyboardArrows();
	
	return testsInError;
}

#endif
