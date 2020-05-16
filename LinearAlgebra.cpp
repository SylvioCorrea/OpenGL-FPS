#include "AllHeaders.h"

float vectorLength(Point3D* p)
{
    float x = p->x;
    float y = p->y;
    float z = p->z;
    return sqrt(x*x + y*y + z*z);
}

////Modifica o vetor recebido tornando-o um vetor unitário;
void vectorNormalize(Point3D* p)
{
    float length = vectorLength(p);
    p->x /= length;
    p->y /= length;
    p->z /= length;
}

//Modifica o vetor p1 somando-o a p2
void vectorAdd(Point3D* p1, Point3D* p2)
{
    p1->x += p2->x;
    p1->y += p2->y;
    p1->z += p2->z;
}

//Modifica o vetor p1 subtraindo-o por p2
void vectorSub(Point3D* p1, Point3D* p2)
{
    p1->x -= p2->x;
    p1->y -= p2->y;
    p1->z -= p2->z;
}

//Modifica o vetor p, multiplicando-o por um escalar
void vectorScalarMult(Point3D* p, float scalar)
{
    p->x *= scalar;
    p->y *= scalar;
    p->z *= scalar;
}

//Função que retorna a multiplicação escalar de dois vetores p1 e p2
//Se p1 e p2 são o mesmo vetor, este cálculo é equivalente ao tamanho do vetor ao quadrado
float dotProduct(Point3D* p1, Point3D* p2)
{
    return (p1->x * p2->x) + (p1->y * p2->y) + (p1->z * p2->z);
}

//Dado o ângulo !!ENTRE OS EIXOS Z e X!! angle, modifica o vetor p
//tal que este represente o vetor unitário com ângulo angle
void polar2Cartesian(Point3D* p, float angle)
{
    p->x = sin(angle);
    p->y = 0;
    p->z = cos(angle);
}

//Rotaciona um vetor em torno do eixo y
void vectorRotateZX(Point3D* p, float angle)
{
    float newX = p->x * cos(angle) + p->z * sin(angle);
    float newZ = p->x * -1 * sin(angle) + p->z * cos(angle);
    p->x = newX;
    p->z = newZ;
}


//Considera raio = 1
//NÃO USADO
//Point3D sphericalCoordinate(float angleZX, float angleV)
//{
//    Point3D p;
//    return p;
//}
