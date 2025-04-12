#ifndef CUBE_H
#define CUBE_H

#include "vec.h"
#include "color.h"

struct Cube
{
    Point p;        // point en bas à gauche du cube
    float l;        // longueur d'un côté du cube
    Color color;    // couleur
    float mirror;   // pourcentage de lumière réfléchie
};

#endif