#include <algorithm>
#include <cmath>
#include <vector>

#include "vec.h"

Point Origin( )
{
    return Point(0, 0, 0);
}


float distance( const Point& a, const Point& b )
{
    return length(a - b);
}

float distance2( const Point& a, const Point& b )
{
    return length2(a - b);
}

Point center( const Point& a, const Point& b )
{
    return Point((a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2);
}


Point min( const Point& a, const Point& b )
{ 
    return Point( std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z) ); 
}

Point max( const Point& a, const Point& b ) 
{ 
    return Point( std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z) ); 
}

 
Vector operator- ( const Point& a, const Point& b )
{
    return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
}

Point operator* ( const float k, const Point& a )
{
    return Point(k * a.x, k * a.y, k * a.z);
}

Point operator* ( const Point& a, const float k )
{
    return k * a;
}

Point operator/ ( const Point& a, const float k )
{ 
    float kk= 1.f / k; 
    return kk * a; 
}

Point operator+ ( const Point& a, const Point& b )
{
    return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector operator- ( const Vector& v )
{
    return Vector(-v.x, -v.y, -v.z);
}

Point operator+ ( const Point& a, const Vector& v )
{
    return Point(a.x + v.x, a.y + v.y, a.z + v.z);
}

Point operator+ ( const Vector& v, const Point& a )
{
    return a + v;
}

Point operator- ( const Vector& v, const Point& a )
{
    return a + (-v);
}

Point operator- ( const Point& a, const Vector& v )
{
    return a + (-v);
}

Vector operator+ ( const Vector& u, const Vector& v )
{
    return Vector(u.x + v.x, u.y + v.y, u.z + v.z);
}

Vector operator- ( const Vector& u, const Vector& v )
{
    return Vector(u.x - v.x, u.y - v.y, u.z - v.z);
}

Vector operator* ( const float k, const Vector& v )
{
    return Vector(k * v.x, k * v.y, k * v.z);
}

Vector operator* ( const Vector& v, const float k )
{
    return k * v;
}

Vector operator* ( const Vector& a, const Vector& b )
{
    return Vector(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vector operator/ ( const Vector& v, const float k )
{
    float kk= 1 / k;
    return kk * v;
}

Vector normalize( const Vector& v )
{
    float kk= 1 / length(v);
    return kk * v;
}

Vector cross( const Vector& u, const Vector& v )
{
    return Vector(
        (u.y * v.z) - (u.z * v.y),
        (u.z * v.x) - (u.x * v.z),
        (u.x * v.y) - (u.y * v.x));
}

float dot( const Vector& u, const Vector& v )
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

float length( const Vector& v )
{
    return std::sqrt(length2(v));
}

float length2( const Vector& v )
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

// infini
// #include <limits>

// const float inf= std::numeric_limits<float>::infinity();

// float intersect_plan( /* parametres du plan */ const Point& a, const Vector& n, /* parametres du rayon */ const Point& o, const Vector& d ) {
//     float de = dot(n, d);
//     if (de == 0) return inf; // Avoid division by zero
//     float t = dot(n, a - o) / de;
//     if (t < 0) return inf;
//     return t;
// }


// float intersect_sphere( /* parametres de la sphere */ const Point& c, const float r, /* parametres du rayon */ const Point& o, const Vector& d ){
//     Vector oc= c - o;
    
//     float a= dot(d,d);
//     float b= 2 * dot(d, oc);
//     float k= dot(oc, oc) - r*r;

//     float det= b*b - 4*a*k;

//     if(det < 0) return inf;
//     float t1= (-b - std::sqrt(det)) / (2*a);
//     float t2= (-b + std::sqrt(det)) / (2*a);
//     if (t1 <= 0 &&  t1>0) return t2;
//     if (t2 <= 0 && t2>0) return t1;

//     return std::min(t1, t2);
// }

