#ifndef SCENE_H
#define SCENE_H

#include <vector>

struct Scene
{
    Plan plan;
    std::vector<Sphere> spheres;
    // std::vector<Cube> cubes;
    std::vector<Source> sources;
};

#endif // SCENE_H
