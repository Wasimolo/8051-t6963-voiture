#ifndef HGH
#define HGH

#define WIDTH_MAP 30
#define HEIGHT_MAP 16
#define SPACE_CAR 5
#define PLAGE_VOITURE 4
#define LONG_MAP 255


void MAP_initialize();
void MAP_begin();
unsigned int MAP_hauteur( unsigned int min, unsigned int max);
void MAP_minmax(unsigned int *min, unsigned int *max, unsigned int hauteur);
unsigned char getMAP(unsigned int x);
#endif