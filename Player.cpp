#include "AllHeaders.h"

Player::Player()
{
    pos.x = 0.0;
    pos.y = 0.0;
    pos.z = 0.0;

    standardInit();
}

//Recebe um ponto no espaço como parâmetro.
//A posição inicial do jogador será este ponto.
Player::Player(Point3D p1) : pos(p1)
{
    standardInit();
}

void Player::standardInit()
{
    up.x = 0.0;
    up.y = 1.0;
    up.z = 0.0;

    angleZX = 0.0;
    angleV = 0.0;
    angleModifier = PLAYER_ANGLE_MODIFIER;
    speed = PLAYER_SPEED;
    shotCoolDown = 0;
    collisionRadius = 85.0;
    angleVBound = ANGLEV_BOUND;
    vulnerabilityCoolDown = 0;
    points = 0;
    maxHealth = 100.0;
    currentHealth = maxHealth;
}

Player::~Player()
{
    //dtor
}

void Player::processInputs3(int left, int right,
                            int up, int down,
                            int newMouseX, int newMouseY,
                            int mouseL, int mouseR)
{
    float mouseXDelta = WINDOW_CENTER_X - newMouseX;
    angleZX += mouseXDelta*MOUSE_SENSITIVITY_X;

    float mouseYDelta = WINDOW_CENTER_Y - newMouseY;
    angleV += mouseYDelta*MOUSE_SENSITIVITY_Y;
    //mouseY = newMouseY;
    if (angleV > angleVBound) {
        angleV = angleVBound;
    } else if(angleV<(-angleVBound)) {
        angleV = -angleVBound;
    }

    updateLookAt();

    Point3D forwardVector; //Vetor unitário paralelo ao chão apontando para frente
    polar2Cartesian(&forwardVector, angleZX);
    vectorScalarMult(&forwardVector, speed);

    Point3D strafeVector; //Vetor unitário paralelo ao chão apontando para a esquerda
    polar2Cartesian(&strafeVector, angleZX+NINETY_DEGREES);
    vectorScalarMult(&strafeVector, speed);

    if(up) {
        vectorAdd(&pos, &forwardVector);
    } else if(down) {
        vectorSub(&pos, &forwardVector);
    }

    if(right) {
        vectorSub(&pos, &strafeVector);
    } else if (left) {
        vectorAdd(&pos, &strafeVector);
    }

    shotCoolDown = max(shotCoolDown - 1, 0);

    if(!shotCoolDown && mouseL) {
        shotCoolDown = 25;
        manager->shotsFired();
    }

    vulnerabilityCoolDown = max(vulnerabilityCoolDown-1, 0);
}

void Player::getLookAt(float* la)
{
    //Posição da câmera
    la[0] = pos.x;
    la[1] = pos.y;
    la[2] = pos.z;

    //Ponto para onde se está olhando é o vetor de posição
    //+ o vetor de direção do olhar
    la[3] = pos.x + (sin(angleZX) * cos(angleV));
    la[4] = pos.y + sin(angleV);
    la[5] = pos.z + (cos(angleZX) * cos(angleV));

    //Vetor up
    la[6] = up.x;
    la[7] = up.y;
    la[8] = up.z;
}

void Player::updateLookAt()
{
    lookAt.x = sin(angleZX) * cos(angleV);
    lookAt.y = sin(angleV);
    lookAt.z = cos(angleZX) * cos(angleV);
}

//REQUER: quem chama deve checar se o jogador está vulnerável
void Player::hit()
{
    vulnerabilityCoolDown = 60;
    currentHealth = currentHealth-10.0;
    if(currentHealth<=0.0) {
        cout << "Game Over" << endl;
        cout << "Total de pontos: " << points << endl;
        exit(0);
    }
}
