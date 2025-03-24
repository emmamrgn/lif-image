// #include "plan.h"

// Hit Plan::intersect(const Point& o, const Vector& d, const float tmax) const {
//     float de = dot(n, d);
//     if (de == 0) return Hit(); // Avoid division by zero
//     float t = dot(n, a - o) / de;
//     if (t < 0 || t > tmax) return Hit();
//     Point p = o + t * d;
//     return Hit(t, p, n, color);
// }

