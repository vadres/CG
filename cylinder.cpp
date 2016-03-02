#include "cylinder.h"

Cylinder::Cylinder()
{
    this->center   = Vector3f(0,0,0);
    this->up       = Vector3f(0,0,0);
    this->radius   = 2.0f;
    this->height   = 2.0f;
    this->material = new Material();
}

Cylinder::Cylinder(const Vector3f &pos, const Vector3f &pos2, float ra, float h){
    this->center  = pos;
    this->center2 = pos2;
    this->up = (pos2 - pos).normalize();
    this->radius = ra;
    this->height = h;
    this->material = new Material();
}

RayCastingResult* Cylinder::hit(const Ray3f &ray, RayCastingResult *result){
    if (!result) {
        result = new RayCastingResult();
    }

    result->object = this;

    vector<double> points;
    Vector3f alpha   = up.mult(ray.getDirection().dot(up));
    Vector3f deltaP  = (ray.getOrigin() - center);
    Vector3f beta    = up.mult(deltaP.dot(up));

    Vector3f p1;
    Vector3f p2;

    double a = (ray.getDirection() - alpha).lenght2();
    double b = 2 * ((ray.getDirection() - alpha).dot(deltaP - beta));
    double c = (deltaP - beta).lenght2() - radius * radius;

    double discriminant = b*b - 4*a*c;

    if (discriminant < 0) {
        return result;
    }
    else {
        discriminant = sqrt(discriminant);
        double t1 = ((-1 * b) + discriminant) / (2 * a);
        double t2 = ((-1 * b) - discriminant) / (2 * a);

        if(t1>=0){
            p1 = (ray.pointAt(t1) - center).normalize();//ray.getOrigin() +  ray.getDirection() * t1;
            p2 = (ray.pointAt(t1) - center2).normalize();
            if(up.dot(p1) > 0 &&
               up.dot(p2) < 0)
            {

                points.push_back(t1);
            }
        }
        if(t2>=0) {
            p1 = (ray.pointAt(t2) - center).normalize();//ray.getOrigin() +  ray.getDirection() * t2;
            p2 = (ray.pointAt(t2) - center2).normalize();
            if(up.dot(p1) > 0 &&
               up.dot(p2) < 0)
            {
                points.push_back(t2);
            }
        }
    }
    double t3;
    double t4;
    if (test_plan(ray, center, t3)){
       Vector3f q3 = ray.pointAt(t3);
       if ((q3 - center).lenght2() <= radius * radius){
          points.push_back(t3);
       }
    }
    if (test_plan(ray, center2, t4)){
       Vector3f q4 = ray.pointAt(t4);
       if ((q4 - center2).lenght2() <= radius * radius){
          points.push_back(t4);
       }
    }

    double minT = INFINITY;
    bool flag = false;
    for(int i=0;i<points.size();i++){
        if(minT > points[i] && points[i]>=0) {
            minT = points[i];
            flag = true;
        }
    }
    if(flag) {
        Vector3f p1;

        p1 = ray.pointAt(minT);

        result->addResult(p1, minT);
        result->addResult(p1, minT);
        result->normal   = getNormal(p1);
        result->material = getMaterial();
    }

    return result;
}

bool Cylinder::test_plan(const Ray3f &ray, const Vector3f &point, double &t_flag){
    Vector3f D = ray.getDirection();
    Vector3f O = ray.getOrigin();
    Vector3f P = point;
    Vector3f N = up;

    float denom = D.dot(N);
    if (denom != 0) {
        t_flag = (P - O).dot(N) / denom;
        return (t_flag >= 0);
    }

    return false;
}

Vector3f Cylinder::getNormal(const Vector3f &point){
 //   return (point - center).mult(2).normalize();

    Vector3f co  = point - center;
    Vector3f co2 = co - up.mult(height);

    if(co.lenght2() <= radius * radius){
        return up.normalize();
    }
    if(co2.lenght2() <= radius * radius){
        return up.normalize();
    }

    Vector3f normal = co - co.project(up);

    return normal.normalize();
}

Vector3f Cylinder::getNormal(){
    return Vector3f(0,0,0);
}

Material* Cylinder::getMaterial(){
    return material;
}

string Cylinder::getName(){
    return "cylinder";
}

Cylinder::~Cylinder(){
    if (material) {
        delete material;
    }
}

/*
    double a = (ray.getDirection() - alpha).lenght2();
    double b = 2 * ((ray.getDirection() - alpha).dot(deltaP - beta));
    double c = (deltaP - beta).lenght2() - radius * radius;

    double discriminant = b*b - 4*a*c;

    if (discriminant < 0) {
        return result;
    }
    else {
        discriminant = sqrt(discriminant);
        double t1 = ((-1 * b) + discriminant) / (2 * a);
        double t2 = ((-1 * b) - discriminant) / (2 * a);

        if(t1>=0){
            q = ray.pointAt(t1);//ray.getOrigin() +  ray.getDirection() * t1;
            if(up.dot((q - center0).normalize()) > 0 &&
               up.dot((q - center2).normalize()) < 0)
            {

                points.push_back(t1);
            }
        }
        if(t2>=0) {
            q = ray.pointAt(t2);//ray.getOrigin() +  ray.getDirection() * t2;
            if(up.dot((q - center0).normalize()) > 0 &&
               up.dot((q - center2).normalize()) < 0)
            {
                points.push_back(t2);
            }
        }
    }
/*
    float denom = up.dot(ray.getDirection());
    if (denom > 1e-6) {
        Vector3f co = center - ray.getOrigin();
        double t3   = co.dot(up) / denom;

        Vector3f q  = ray.getOrigin() + ray.getDirection()*t3;
        Vector3f v  = q - center;
        double d2   = v.dot(v);

        if(t3 >= 0 && d2 <= radius * radius){
            points.push_back(t3);
        }

    } else if (denom < 1e-6) {
        Vector3f co2 = center2 - ray.getOrigin();
        double t4 = co2.dot(up) / denom;

        if((ray.getDirection() * t4 - co2).lenght2() < radius * radius){
            points.push_back(t4);
        }

    }
*/


