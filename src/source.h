#ifndef _SOURCE_H
#define _SOURCE_H

#include "vec.h"
#include "color.h"

struct Source
{
    Point a;    // position de la source de lumiere
    float p;    // puissance de la lumiere
    Color color;    // couleur

};

#endif