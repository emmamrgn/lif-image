#include "color.h"
#include "image.h"
#include "image_io.h"
#include <random>

#include "plan.h"
#include "sphere.h"
#include "source.h"
#include "scene.h"
#include "hit.h"
#include "cube.h"


int ANTIALIASING = 3;
// Color BACKGROUND_COLOR = Color(40, 0, 40,1);  
Color BACKGROUND_COLOR = Color(0.7,0.9,0.9,1);

// Intersection entre un rayon et un plan
Hit intersect(const Plan& plan, const Point& o, const Vector& d)
{
    float t = dot(plan.n, Vector(o,plan.a)) / dot(plan.n,d);

    if(t < 0)
        return {inf, plan.n, plan.color, plan.mirror};  // l'intersection n'est pas valide / derriere l'origine du rayon
    else
        return {t, plan.n, plan.color, plan.mirror};    // renvoie la position de l'intersection, + la normale et la couleur du plan
}

// Intersection entre un rayon et une sphere
Hit intersect(const Sphere& sphere, const Point& o, const Vector& d)
{

    float a= dot(d,d);
    float b= dot(2*d,Vector(sphere.c,o));
    float k= dot(Vector(sphere.c,o),Vector(sphere.c,o)) - sphere.r*sphere.r;

    float det= b*b - 4*a*k;

    if ( (o.x-sphere.c.x)*(o.x-sphere.c.x) + (o.y-sphere.c.y)*(o.y-sphere.c.y) + (o.z-sphere.c.z)*(o.z-sphere.c.z) < (sphere.r*sphere.r)) {
        float t1 = (-b+sqrt((b*b)-4*a*k))/(2*a);
        Point p_inter = o + t1 *d; // point d'intersection
        Vector p_inter_norm = Vector(sphere.c,p_inter); // normale de ce point

        return {t1, p_inter_norm, sphere.color, sphere.mirror};
    }

    if (det >= 0) {
        float t1 = (-b+sqrt((b*b)-4*a*k))/(2*a);
        float t2 = (-b-sqrt((b*b)-4*a*k))/(2*a);

        if (t1 < 0 && t2 < 0) {
            return {inf, Vector(-1,-1,-1), sphere.color, sphere.mirror};
        }
        else {
            Point p_inter = o + std::min(t1,t2) *d; // point d'intersection
            Vector p_inter_norm = Vector(sphere.c, p_inter); // normale de ce point
            return {std::min(t1,t2), p_inter_norm, sphere.color, sphere.mirror};
        }
    }
    else return {inf, Vector(-1,-1,-1), sphere.color, sphere.mirror};
}

// Intersection entre un rayon et un cube
Hit intersect(const Cube& cube, const Point& o, const Vector& d)
{
    // distances d'intersection entre le rayon et les plans du cube
    float t_x_min = (cube.p.x - o.x) / d.x;
    float t_x_max = (cube.p.x + cube.l - o.x) / d.x;
    float t_y_min = (cube.p.y - o.y) / d.y;
    float t_y_max = (cube.p.y + cube.l - o.y) / d.y;
    float t_z_min = (cube.p.z - o.z) / d.z;
    float t_z_max = (cube.p.z + cube.l - o.z) / d.z;

    // distance minimum et distance maximum 
    float t_min = std::max({std::min(t_x_min, t_x_max), std::min(t_y_min, t_y_max), std::min(t_z_min, t_z_max)});
    float t_max = std::min({std::max(t_x_min, t_x_max), std::max(t_y_min, t_y_max), std::max(t_z_min, t_z_max)});
    // pour le premier std::max/min de chaque ligne, j'ai testé en les inversant au début mais ça ne fonctionnait pas, donc je les laisse comme ça

    // si t_max < 0, le cube est derriere le rayon, on retourne inf
    if (t_max < 0)
        return {inf, Vector(-1,-1,-1), cube.color, cube.mirror};

    // si t_min > t_max, le rayon ne touche pas le cube, on retourne inf
    if (t_min > t_max)
        return {inf, Vector(-1,-1,-1), cube.color, cube.mirror};

    Vector p_inter_norm;

    // en fonction des cas, on calcule la normale du plan d'intersection
    if (t_min == t_x_min)
        p_inter_norm = Vector(-1, 0, 0);
    else if (t_min == t_x_max)
        p_inter_norm = Vector(1, 0, 0);
    else if (t_min == t_y_min)
        p_inter_norm = Vector(0, -1, 0);
    else if (t_min == t_y_max)
        p_inter_norm = Vector(0, 1, 0);
    else if (t_min == t_z_min)
        p_inter_norm = Vector(0, 0, -1);
    else if (t_min == t_z_max)
        p_inter_norm = Vector(0, 0, 1);

    return {t_min, p_inter_norm, cube.color, cube.mirror};
}

// Intersection entre un rayon et une scene
Hit intersect(const Scene& scene, const Point& o, const Vector& d)
{
    Hit temp = {inf, Vector(-1,-1,-1), Black(), 0};

    for(unsigned i= 0 ; i < scene.spheres.size(); i++)
    {
        // on teste avec la sphere
        Hit h= intersect(scene.spheres[i], o, d);
        if(h.t < temp.t)
            temp = h;
    }

    for(unsigned i= 0 ; i < scene.cubes.size(); i++)
    {
        // on teste avec le cube
        Hit h= intersect(scene.cubes[i], o, d);
        if(h.t < temp.t)
            temp = h;
    }

    // on teste avec le plan
    Hit h= intersect(scene.plan, o, d);
    if(h.t < temp.t)
            temp = h;

            

    return temp;
}

// Direction mirroir
Vector miroir(const Vector& n, const Vector& v)
{
    //assert(dot(n, v) < 0);
    return v - 2*dot(n, v)*n;
}

// Creation de sources de lumiere dans un tableau (vector)
std::vector<Source> creationSource(const Point& a, const Vector& u, const Vector& v, const Color& emission, const int n, float puissance)
{
    float puissance_individuelle = puissance/n;

    std::vector<Source> planSources;
    for (int i = 0; i < n/2; i ++)
    for (int j = 0; j < n/2; j ++)
    {
        float b= float (i ) / float (n/2) ;
        float c= float (j ) / float (n/2) ;
        Point s= a + b *u + c *v; // position du point dans la grille
        planSources.push_back({s,puissance_individuelle,emission});
    }

    return planSources;
}

// Eclairage d'un point
Color eclairagePoint(const Point& p, const Vector& n, const Color& color, const Scene scene) {
    
    Color pixel;

    for (unsigned int i=0; i<scene.sources.size(); i++) {
        Vector vec_source = Vector(p, scene.sources[i].a);
        if (intersect(scene, p, vec_source).t > 0 && intersect(scene, p, vec_source).t < 1) {
            pixel = pixel + Black();
        }
        else {
            float cos_theta = std::max(float(0), dot(normalize(n), normalize(vec_source)));
            pixel = pixel + (scene.sources[i].p *scene.sources[i].color * color * cos_theta/length2(vec_source));
        }
    }

    return pixel;
}

// Affichage de l'image
void affichage(Image& image, Scene scene) {
    float ratio = float(image.width())/float(image.height());   // ratio de l'image
    float cos_theta;
    Point o = Point(0, 0, 0);    // position de la camera, l'origine

    #pragma omp parallel for schedule(dynamic, 1)
    // Parcours de chaque pixel de l'image
    for(int py= 0; py < image.height(); py++)
    for(int px= 0; px < image.width(); px++)
    {        

        Color pixel;
        std::default_random_engine rng;
        std::uniform_real_distribution<float> u;

        for ( int pa = 0; pa < ANTIALIASING ; pa ++) { // plusieurs rayon pour chaque pixel

            float ux = u(rng);
            float uy = u(rng);

            float x = float(px + ux)/float(image.width())*2-1; 
            float y = float(py + uy)/float(image.height())*2-1;

            Point e;    // point touché

            // On adapte les coordonées en fonction du ratio de l'image
            if (ratio > 1) {
                e = Point(x*ratio, y, -1);
            }
            else if (ratio <=1) {
                e = Point(x, y/ratio, -1);
            }

            Vector d= Vector(o, e); // direction : extremite - origine
            d = normalize(d);
        
            Hit intersection = intersect(scene, o, d);
            
            if (intersection) {
                Point p_inter = o + intersection.t *d;
                p_inter = p_inter + 0.001 * intersection.n; 

                pixel = pixel + eclairagePoint(p_inter,intersection.n,intersection.color,scene);
            }
            else 
            {
                pixel = pixel + BACKGROUND_COLOR;
            }
        }
        image(px,py) = Color(pixel / ANTIALIASING, 1); // on fait une moyenne des couleurs des pixels voisins
    }

    // boucle pour les reflections

    for(int py= 0; py < image.height(); py++)
    for(int px= 0; px < image.width(); px++) {

        float x = float(px)/float(image.width())*2-1; 
        float y = float(py)/float(image.height())*2-1;
        
        Point e;    // point touché
        Color pixel;

        // On adapte les coordonées en fonction du ratio de l'image
        if (ratio > 1) {
            e = Point(x*ratio, y, -1);
        }
        else if (ratio <=1) {
            e = Point(x, y/ratio, -1);
        }

        Vector d= Vector(o, e); // direction : extremite - origine
        d = normalize(d);
    
        Hit intersection = intersect(scene, o, d);

        if (intersection.mirror > 0) {
            Vector reflection = miroir(intersection.n, d);
            Point p_inter = o + intersection.t *d;
            p_inter = p_inter + 0.001 * intersection.n; 

            Hit object = intersect(scene, p_inter, reflection);

            if (object) {
                Point p_inter2 = p_inter + object.t *reflection;
                p_inter2 = p_inter2 + 0.001 * object.n; 
                Vector vec_source2 = Vector(p_inter2,scene.sources[0].a);

                cos_theta = std::max(float(0), dot(normalize(object.n), normalize(vec_source2)));
                pixel = (scene.sources[0].p * scene.sources[0].color * object.color * cos_theta/length2(vec_source2)); // On recupere la couleur de l'objet dans la direction mirroir
                pixel = pixel * (intersection.mirror + (1-intersection.mirror)*(pow((1-cos_theta),5))); // On calcule le coefficient de reflexion de Fresnel
                image(px,py) = Color(pixel, 1);
            }
            else {
                pixel = intersection.mirror * BACKGROUND_COLOR; // On recupere la couleur de l'objet dans la direction mirroir
                image(px,py) = Color(pixel, 1);

            }
        }
    } 
}

// Fonction principale
int main( )
{
    // cree l'image resultat
    Image image(1024, 700);    // par exemple...

    // les objets
    Sphere s_rouge = {Point(0, 0, -5), 2, Red(), 0};
    Sphere s_yellow = {Point(2, -1, -3), 1, Yellow(), 1};
    Sphere s_miroir = {Point(-1.5, 0, -2.5), 0.5, Green(), 0};

    Cube c_bleu = {Point(0, 0, -5), 1, Color(0.5, 0.5, 1, 1), 0};

    // le plan
    Plan plan = {Point(0,-1,0), Vector(0,1,0), White(), 0};

    // les sources de lumieres
    Source source1 = {Point(4,2,-2), 5, Color(0.5, 1, 0.5, 1)};
    Source source2 = {Point(-4,4,-4), 1, White()};
    Source source3 = {Point(0,3,0), 5, White()+Blue()};

    std::vector<Source> panneauSources = creationSource(Point(-2,2,3), Vector(5,0,0),Vector(0,5,0), Color(1, 0.8, 0.8, 1), 10, 20);

    panneauSources.push_back(source1);
    panneauSources.push_back(source2);
    panneauSources.push_back(source3);

    // la scene
    Scene scene;
    scene.plan = plan;
    scene.spheres.push_back(s_rouge);
    scene.spheres.push_back(s_yellow);
    scene.spheres.push_back(s_miroir);

    scene.cubes.push_back(c_bleu);

    for (unsigned int i=0; i<panneauSources.size(); i++) {
        scene.sources.push_back(panneauSources[i]);
    }

    affichage(image,scene);

    write_image(image, "img/renduImage.png");

    return 0;
}