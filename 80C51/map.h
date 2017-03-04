#ifndef HGH
#define HGH

#define WIDTH_MAP 19
#define HEIGHT_MAP 13
#define SPACE_CAR 5



void MAP_initialize();
unsigned int MAP_hauteur( unsigned int min, unsigned int max);
void MAP_create(unsigned int ligne, unsigned int haut_obs);
unsigned char getMAP(unsigned int x, unsigned int y);
#endif