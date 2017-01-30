#ifndef ___MAP_H
#define ___MAP_H


#define WIDTH_MAP 16
#define HEIGHT_MAP 10
#define SPACE_CAR 5


unsigned char __xdata MAP[WIDTH_MAP][HEIGHT_MAP]

void MAP_initialize();
unsigned char MAP_hauteur();
void MAP_create();


#endif