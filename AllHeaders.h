

#ifndef ALLHEADERS_H_INCLUDED
#define ALLHEADERS_H_INCLUDED

#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <GL/glut.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cfloat>

//Constantes matem�ticas
#define PI              3.14159265358979323846
#define NINETY_DEGREES  PI/2.0

//Taxa de atualiza��o do jogo. Se GAME_TICKS_PER_SECOND = 60, isto significa
//que o estado do jogo ser� atualizado 60 vezes por segundo. Esta constante �
//usada como par�metro para a fun��o glutTimerFunc
#define GAME_TICKS_PER_SECOND  60
#define GAMELOOP_TIMER         1000/GAME_TICKS_PER_SECOND

//Clipping bounds
#define NEAR_CLIP   0.1       //Nada mais perto do observador do que esta dist�ncia ser� desenhado
#define FAR_CLIP    5000.0     //Nada al�m desta dist�ncia ser� desenhado

//Medidas da janela
#define WINDOW_WIDTH    1024
#define WINDOW_HEIGHT   576
//#define WINDOW_WIDTH    800
//#define WINDOW_HEIGHT   600
#define WINDOW_CENTER_X WINDOW_WIDTH/2
#define WINDOW_CENTER_Y WINDOW_HEIGHT/2

//Constantes do jogador/c�mera
#define PLAYER_SPEED            10.0f
#define PLAYER_ANGLE_MODIFIER   0.001f
#define MOUSE_SENSITIVITY_X     0.004f
#define MOUSE_SENSITIVITY_Y     0.004f
#define ANGLEV_BOUND    NINETY_DEGREES - 0.1

//HUD
#define HEALTH_BAR_WIDTH    WINDOW_WIDTH/4.0
#define HEALTH_BAR_HEIGHT   WINDOW_HEIGHT/18.0
#define HEALTH_BAR_X_Y      WINDOW_HEIGHT/24.0

//Constantes de objetos
#define OBJECT_SPEED 5.0f

//Medidas do ch�o e teto
#define FLOOR_EXPANSE   2000  //Ch�o � desenhado de -FLOOR_EXPANSE a +FLOOR_EXPANSE
#define TILE_SIZE       100    //Tamanho da aresta dos ladrilhos do ch�o

using namespace std;




//=====================================================================
//Classes and Structs
struct Point3D
{
    float x, y, z;
};

struct ColorRGB
{
    float r;
    float g;
    float b;
};

class HermiteCurve
{
    public:
    Point3D p0;
    Point3D m0;
    Point3D p1;
    Point3D m1;
    float t;

    HermiteCurve();
    HermiteCurve(Point3D a, Point3D b, Point3D c, Point3D d);
    virtual ~HermiteCurve();

    void reset(Point3D currentPos, Point3D target);
    Point3D getCurvePointAtT();
};

class GameManager;

class Player
{
    public:
    GameManager* manager;
    Point3D pos; //Posi��o do jogador no SU
    Point3D up;
    //lookAt � um vetor unit�rio que indica a dire��o para a qual o jogador est� olhando com base no
    //sistema de referencia do pr�prio jogador. Para saber onde fica este vetor no SU, basta som�-lo
    //ao vetor de posi��o do jogador
    Point3D lookAt;

    float angleZX;//�ngulo entre os eixos Z e X
    float angleV; //Inclina��o vertical
    float angleVBound; //Impede que o vetor do olhar seja perpendicular ao plano ZX
    float angleModifier; //"Velocidade" de modifica��o do �ngulo

    //Velocidade de movimento
    float speed;
    float collisionRadius;
    int shotCoolDown; //Um jogador n�o pode atirar enquanto shotCoolDown for maior do que 0
    int vulnerabilityCoolDown;
    int points;
    float maxHealth;
    float currentHealth;

    //Construtores e destruidores
    Player();
    Player(Point3D p1);
    void standardInit();
    virtual ~Player();

    void processInputs3(int left, int right, int up, int down, int newMouseX, int newMouseY, int mouseL, int mouseR);
    void getLookAt(float* la);
    void updateLookAt();
    void hit();
};

enum ObjectState
{
    Idle, Active, Wait
};

class GameObject //interface
{
    public:
    Point3D pos;

    //Usado para detectar colis�o, corresponde ao raio da esfera de colis�o ao quadrado:
    float collisionRadius;
    float collisionRadiusSquared;

    float angleZX;
    float angleV;

    ColorRGB color;

    int isVulnerable;
    int waiting;
    ObjectState state;
    float speed;

    virtual void draw()=0;
    virtual void hit(Point3D origin)=0;
    int checkCollision(Point3D playerPos, float r);
    float checkShotCollision(Point3D origin, Point3D direction);
    virtual void update(Point3D target)=0;
    virtual void reset(Point3D p)=0;
};

class Sphere : public virtual GameObject
{
    public:
    float shapeRadius;
    int slices; //divis�es de "longitude"
    int stacks; //divis�es de "latitude"

    Sphere();
    Sphere(float x, float y, float z);
    Sphere(Point3D p, float r);
    void standardInit(float r);
    virtual ~Sphere();

    void draw();
    void hit(Point3D origin);
    void update(Point3D target);
    void reset(Point3D p);
};

class Cube : public virtual GameObject
{
    public:
    float size;
    HermiteCurve curvePath;

    Cube();
    Cube(float x, float y, float z);
    void standardInit();
    virtual ~Cube();

    void draw();
    void hit(Point3D origin);
    void update(Point3D target);
    void reset(Point3D p);
};

class Octahedron : public virtual GameObject
{
    public:
    float size;

    Octahedron();
    Octahedron(float x, float y, float z);
    void standardInit();
    virtual ~Octahedron();

    void draw();
    void hit(Point3D origin);
    void update(Point3D target);
    void reset(Point3D p);
};

class GameManager
{
    private:
    Player* player;
    vector<GameObject*> gameObjs;
    vector<Point3D> originalPos;
    int idleObjects;
    GameObject* createRandomObject(float x, float y, float metadeX, float metadeY, float scalingFactor);

    public:
    //Flags de teclado
    int leftKeyFlag;
    int rightKeyFlag;
    int upKeyFlag;
    int downKeyFlag;

    //Flags do mouse. N�o usadas por enquanto
    int leftMouseButton;
    int rightMouseButton;

    //Registra a posi��o do mouse na janela.
    //Glut considera (0,0) o canto superior esquerdo da janela
    int mouseX;
    int mouseY;

    GameManager();
    virtual~GameManager();


    void update();
    void drawEverything();
    void drawHUD();
    void shotsFired();
    void resetObjects();
    int playerOutOfBounds();
};




//=====================================================================
//Algebra Linear
float vectorLength(Point3D* p);
void vectorNormalize(Point3D* p);
void vectorAdd(Point3D* p1, Point3D* p2);
void vectorSub(Point3D* p1, Point3D* p2);
void vectorScalarMult(Point3D* p, float scalar);
float dotProduct(Point3D* p1, Point3D* p2);
void vectorRotateZX(Point3D* p, float angleZX);
void polar2Cartesian(Point3D* p, float angle); //Considerando um �ngulo entre os eixos Z e X.
//Point3D sphericalCoordinate(float angleH, float angleV);




//=====================================================================
//Fun��es gerais de desenho
void drawCheckerboard(float y);
void drawPoints(int n);
void drawHealthBar(float currentHealth, float maxHealth);
void drawCrossHair();
void drawDamageIndicator();






//=====================================================================
//Auxiliares
void printLookAt(float* la);
Point3D createPoint3D(float x, float y, float z);



//=====================================================================
//Cores
ColorRGB getColorRed();
ColorRGB getColorGreen();
ColorRGB getColorBlue();

#endif // ALLHEADERS_H_INCLUDED
