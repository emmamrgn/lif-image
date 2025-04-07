#include <vector>

struct Scene
{
    std::vector<Sphere> spheres;
    Plan plan;
    std::vector<Source> sources;
};
