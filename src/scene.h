#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "plan.h"
#include "sphere.h"
#include "hit.h"
// #include "cube.h"
#include "source.h"

struct Scene
{
    std::vector<Sphere> spheres;
    // std::vector<Cube> cubes;
    Plan plan;
    std::vector<Source> sources;
};

#endif // SCENE_H