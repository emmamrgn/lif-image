#ifndef PLAN_H
#define PLAN_H

#include "vec.h"
#include "color.h"

struct Plan
{
    Point a;        // point sur le plan
    Vector n;       // normale du plan
    Color color;    // couleur
    float mirror;   // pourcentage de lumière réfléchie
};

#endif // PLAN_H