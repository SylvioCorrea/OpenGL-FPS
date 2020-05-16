#include "AllHeaders.h"

//=====================================================================
//Gameobject


//REQUER: |direction| == 1
//RETORNA a distância entre a origem e o ponto de intersecção mais próximo de origin
//ou -1.0 caso não haja intersecção.
float GameObject::checkShotCollision(Point3D origin, Point3D direction)
{
    if(isVulnerable) { //objeto invulnerável não pode ser acertado

        Point3D objCenter = pos;
        vectorSub(&objCenter, &origin);//Centro do objeto em relação ao ponto origin
        float projection = dotProduct(&objCenter, &direction); //Projeção de objCenter sobre origin

        if(projection>0) {
            //Objeto está na frente da origem, logo, pode ter sido acertado pelo tiro
            float a_squared = dotProduct(&objCenter, &objCenter) - projection*projection;

            if(a_squared < collisionRadiusSquared) {//Tiro acertou o objeto

                //retorn a distância entre a origem do disparo e o ponto mais proximo de
                //intersecção
                return projection - sqrt(collisionRadiusSquared - a_squared);

                //b = sqrt(gameObjs[i]->collisionRadiusSquared - a_squared);

                //cópia do vetor unitário de direção
                //intersection1 = direction;
                //multiplica o vetor de direção pelo escalar que corresponde a distancia entre
                //a origem do tiro e o primeiro ponto de intersecção com o objeto
                //vectorScalarMult(&intersection1, projection - b);
                //soma ao ponto de origem do tiro para encontrar o ponto exato de
                //intersecção com a esfera com base no SU
                //vectorAdd(&intersection1, &origin);

                //cópia do vetor unitário de direção
                //intersection2 = direction;
                //multiplica o vetor de direção pelo escalar que corresponde a distancia entre
                //a origem do tiro e o segundo ponto de intersecção com o objeto
                //vectorScalarMult(&intersection2, projection + b);
                //soma ao ponto de origem do tiro para encontrar o ponto exato de
                //intersecção com a esfera com base no SU
                //vectorAdd(&intersection2, &origin);
            }
        }
    }

    return -1.0;
}

int GameObject::checkCollision(Point3D playerPos, float r)
{
    Point3D player_obj = pos;
    vectorSub(&player_obj, &playerPos);
    float distance = sqrt( dotProduct(&player_obj, &player_obj) );
    if(distance <= collisionRadius + r) {
        return 1;
    }
    return 0;
}


//=====================================================================
//Sphere
Sphere::Sphere()
{
    pos.x = 0.0;
    pos.y = 100.0;
    pos.z = 0.0;

    standardInit(50.0);
}

Sphere::Sphere(float x, float y, float z)
{
    pos.x = x;
    pos.y = y;
    pos.z = z;

    standardInit(50.0);
}

Sphere::Sphere(Point3D p, float r)
{
    pos = p;

    standardInit(r);
}

void Sphere::standardInit(float r)
{
    color.r = 0.0;
    color.g = 0.0;
    color.b = 1.0;

    collisionRadius = r;
    collisionRadiusSquared = collisionRadius*collisionRadius;
    shapeRadius = collisionRadius;
    slices = (int)(shapeRadius*2);
    stacks = (int)(shapeRadius*2);

    speed = OBJECT_SPEED;

    angleZX = 0.0;
    angleV = 0.0;

    isVulnerable = 1;

    state = Idle;

    waiting = 0;
}

Sphere::~Sphere()
{
    //dtor
}

void Sphere::draw()
{
    glPushMatrix();
      glTranslatef(pos.x, pos.y, pos.z);
      glColor3f(color.r, color.g, color.b);
      glutSolidSphere(shapeRadius, slices, stacks);
    glPopMatrix();
}

void Sphere::hit(Point3D origin)
{
    if (isVulnerable) {
        color.r = 1.0;
        color.g = 0.0;
        color.b = 0.0;
        isVulnerable = 0;
    }
}

void Sphere::update(Point3D target) {
    if(isVulnerable == 0) {
        vectorSub(&target, &pos);
        float d = sqrt(dotProduct(&target, &target));
        target.x /= d;
        target.y /= d;
        target.z /= d;
        vectorScalarMult(&target, speed);
        vectorAdd(&pos, &target);
    }
}

void Sphere::reset(Point3D p)
{
    pos = p;
    standardInit(50.0);
}


//=====================================================================
//Cube
Cube::Cube()
{
    //TODO
    state = Idle;
}

Cube::Cube(float x, float y, float z)
{
    pos.x = x;
    pos.y = y;
    pos.z = z;

    standardInit();
}

void Cube::standardInit()
{
    color.r = 0.0;
    color.g = 0.0;
    color.b = 1.0;

    angleZX = 0.0;
    angleV = 0.0;
    isVulnerable = 1;
    speed = OBJECT_SPEED;

    size = 80.0;
    collisionRadius = 0.85*size;
    collisionRadiusSquared = collisionRadius*collisionRadius;

    curvePath.p0 = createPoint3D(100, 100, 100);
    curvePath.m0 = createPoint3D(1000, 100, 100);
    //vectorSub(&(curvePath.m0), &(curvePath.p0));
    curvePath.p1 = createPoint3D(100, 100, 1000);
    curvePath.m1 = createPoint3D(-1000, 100, 1000);
    //vectorSub(&(curvePath.m1), &(curvePath.p1));
    state = Idle;

    waiting = 0;
}

Cube::~Cube()
{
    //dtor
}

void Cube::draw()
{
    glPushMatrix();
      glTranslatef(pos.x, pos.y, pos.z);
      glRotatef(angleZX, 0.0, 0.1, 0.0);
      glRotatef(angleV, 0.1, 0.0, 0.0);
      glColor3f(color.r, color.g, color.b);
      glutSolidCube(size);
    glPopMatrix();
}

void Cube::hit(Point3D origin)
{
    if (isVulnerable) {
        color.r = 1.0;
        color.g = 0.0;
        color.b = 0.0;
        isVulnerable = 0;

        state = Active;
        curvePath.reset(pos, origin);
    }
}

void Cube::update(Point3D target) {
    switch(state) {
//        vectorSub(&target, &pos);
//        float d = sqrt(dotProduct(&target, &target));
//        target.x /= d;
//        target.y /= d;
//        target.z /= d;
//        vectorScalarMult(&target, speed);
//        vectorAdd(&pos, &target);

        case Idle:
            break;

        case Active:
            pos = curvePath.getCurvePointAtT();
            angleV += 2.5;
            angleZX += 2.5;
            curvePath.t = min(curvePath.t + 0.002f, 1.0f);
            if(curvePath.t==1.0) {
                state = Wait;
                waiting = 60;
            }
            break;

        case Wait:
            waiting = max(waiting-1, 0);
            angleV += 2.5;
            angleZX += 2.5;
            if(waiting == 0) {
                state = Active;
                curvePath.reset(pos, target);
            }
    }
}

void Cube::reset(Point3D p)
{
    pos = p;
    standardInit();
}



//=====================================================================
//HermiteCurve

HermiteCurve::HermiteCurve()
{
    t = 0.0f;
}

HermiteCurve::HermiteCurve(Point3D a, Point3D b, Point3D c, Point3D d) :
    p0(a), m0(b), p1(c), m1(d)
{
    t = 0.0f;
}

HermiteCurve::~HermiteCurve()
{
    //dtor
}

void HermiteCurve::reset(Point3D currentPos, Point3D target)
{
    t = 0.0f;

    p0 = currentPos;
    p1 = target;

    float r = (rand()%2)? 1.0f : -1.0f;

    Point3D new_m = target;
    vectorSub(&new_m, &currentPos);
    vectorNormalize(&new_m);
    vectorRotateZX(&new_m, NINETY_DEGREES * r);
    vectorScalarMult(&new_m, 5000.0f);

    m0 = currentPos;
    vectorAdd(&m0, &new_m);

    m1 = target;
    vectorSub(&m1, &new_m);
}

Point3D HermiteCurve::getCurvePointAtT()
{
    //p(t) = (2t^3 - 3t^2 + 1)p0 + (t^3 - 2t^2 + t)m0 +
    //       (-2t^3 + 3t^2)p1 + (t^3 - t^2)m1
    //Cada fator calculado dentro dos paredes, corresponde a
    //b0, b1, b2 e b3 respectivamente, na ordem em que aparecem
    float b0 = 2*t*t*t - 3*t*t + 1;
    float b1 = t*t*t - 2*t*t + t;
    float b2 = -2*t*t*t + 3*t*t;
    float b3 = t*t*t - t*t;

    Point3D res;
    res.x = b0*p0.x + b1*m0.x + b2*p1.x + b3*m1.x;
    res.y = b0*p0.y + b1*m0.y + b2*p1.y + b3*m1.y;
    res.z = b0*p0.z + b1*m0.z + b2*p1.z + b3*m1.z;

    return res;
}



//=====================================================================
//Octahedron

Octahedron::Octahedron()
{
    //ctor
}

Octahedron::Octahedron(float x, float y, float z)
{
    pos.x = x;
    pos.y = y;
    pos.z = z;

    standardInit();
}

void Octahedron::standardInit()
{
    color.r = 0.0f;
    color.g = 0.0f;
    color.b = 1.0f;

    angleZX = 0.0f;
    angleV = 0.0f;
    isVulnerable = 1;
    speed = 0.0f;

    size = 80.0f;
    collisionRadius = size;
    collisionRadiusSquared = collisionRadius*collisionRadius;
    state = Idle;

    waiting = 0;
}

Octahedron::~Octahedron()
{
    //dtor
}

void Octahedron::draw()
{
    glPushMatrix();
      glTranslatef(pos.x, pos.y, pos.z);
      glRotatef(angleZX, 0.0, 0.1, 0.0);
      glScalef(size, size, size);
      glColor3f(color.r, color.g, color.b);
      glutSolidOctahedron();
    glPopMatrix();
}

void Octahedron::hit(Point3D origin)
{
    if (isVulnerable) {
        color.r = 1.0;
        color.g = 0.0;
        color.b = 0.0;
        isVulnerable = 0;

        state = Active;
        size *= 2.0f;
        collisionRadius *= 2.0f;
        collisionRadiusSquared *= 2.0f;
    }
}

void Octahedron::update(Point3D target) {
    switch(state) {

        case Idle:
            break;

        case Active:
            angleZX += 0.1f;
            break;

        case Wait:
            waiting = max(waiting-1, 0);
            if(waiting == 0) {
                state = Active;
            }
    }
}

void Octahedron::reset(Point3D p)
{
    pos = p;
    standardInit();
}
