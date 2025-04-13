#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "plan.h"
#include "sphere.h"
#include "cube.h"
#include "source.h"

struct Scene
{
    Plan plan;
    std::vector<Sphere> spheres;
    std::vector<Cube> cubes;
    std::vector<Source> sources;
};

#endif // SCENE_H
