#ifndef SPHERE_H
#define SPHERE_H

#include "vec.h"
#include "color.h"

struct Sphere
{
    Point c;        // centre de la sphere
    float r;        // rayon de la sphere
    Color color;    // couleur
    float mirror;   // pourcentage de lumière réfléchie
};

#endif // SPHERE_H