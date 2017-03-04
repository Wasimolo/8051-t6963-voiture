#ifndef ___GAMEBOARD_H
#define ___GAMEBOARD_H

#ifdef TEST
#define CHAR_BASE 0x00
int testGameboard();
#else
#define CHAR_BASE 0x80
#endif


#define EMPTY 0x00

#define VOITURE_BACK_LEFT (0x21 + CHAR_BASE)
#define VOITURE_FRONT_LEFT (0x22 + CHAR_BASE)
#define VOITURE_BACK_RIGHT (0x23 + CHAR_BASE)
#define VOITURE_FRONT_RIGHT (0x24 + CHAR_BASE)
#define BARRIERE_UP (0x25 + CHAR_BASE)
#define BARRIERE_DOWN (0x26 + CHAR_BASE)
#define OBSTACLE (0x27 + CHAR_BASE)
#define GAZON (0x28 + CHAR_BASE)

/*#define SNAKE_BODY (0x11 + CHAR_BASE)
#define SNAKE_SWALLOW (0x12 + CHAR_BASE)
#define SNAKE_HEAD (0x13 + CHAR_BASE)
#define SNAKE_DEAD (0x14 + CHAR_BASE)
#define FRUIT (0x15 + CHAR_BASE)*/



void GMB_initialize();
void GMB_draw(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1);
void GMB_clear(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1);
void GMB_display(unsigned char x0, unsigned char y0, char *text);
void GMP_MAP();

#endif
