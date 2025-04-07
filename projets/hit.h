#ifndef _HIT_H
#define _HIT_H

#include <limits>
#include "vec.h"
#include "color.h"

const float inf= std::numeric_limits<float>::infinity();

struct Hit // infos sur une intersection
{
    float t;        // position sur le rayon ou inf
    Vector n;       // normale du point d'intersection, s'il existe
    Color color;    // couleur du point d'intersection, s'il existe
    float mirror; // pourcentage de lumière réfléchie de l'objet touché
    operator bool() { return t >= 0 && t < inf; } // renvoie vrai si l'intersection existe et quelle est valide

};

#endif