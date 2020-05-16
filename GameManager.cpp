#include "AllHeaders.h"
#include "PreviousHeaders.h"

//vector � passado por referencia
GameManager::GameManager()
{
    srand(time(NULL));

    leftKeyFlag = 0;
    rightKeyFlag = 0;
    upKeyFlag = 0;
    downKeyFlag = 0;

    leftMouseButton = 0;
    rightMouseButton = 0;

    mouseX = WINDOW_CENTER_X;
    mouseY = WINDOW_CENTER_Y;

    Point3D p; //Posi��o inicial de player
    p.x = 300.0f;
    p.y = 150.0f;
    p.z = 300.0f;

    player = new Player(p);
    player->manager = this;

    //Le o arquivo
    VideoData* vd = file2VideoData("Paths_D_DE1.txt");
    zeroFill(vd);
    Point2d menores, maiores;
    //Determina as menores ocorr�ncias de x e y nas posi��es
    //das pessoas
    screenBound(vd, &menores, &maiores);
    //Metade da distancia entre o menor e o maior x
    float metadeX = (maiores.x + menores.x)/2.0;
    //Metade da distancia entre o menor e o maior y
    float metadeY = (maiores.y + menores.y)/2.0;
    //Fator arbitr�rio que multiplicar� os valores das posi��es a fim
    //de ampliar o espa�o entre os objetos a serem desenhados
    float scalingFactor = 8;

    for(size_t i=0; i<vd->persons.size(); i++) {
        if(vd->persons[i] != 0) {
            Point2d* position = vd->persons[i]->path[0]->position;
            GameObject* obj = createRandomObject(position->x, position->y, metadeX, metadeY, scalingFactor);
            gameObjs.push_back(obj);
            originalPos.push_back(obj->pos);
        }
    }

    idleObjects = gameObjs.size();
}

GameManager::~GameManager()
{
    //dtor
}

GameObject* GameManager::createRandomObject(float x, float z, float metadeX, float metadeY, float scalingFactor)
{
    x = (x - metadeX) * scalingFactor;
    float y = (rand()%201) + 50.0;
    z = (z - metadeY) * scalingFactor;
    int objectType = rand()%5;
    switch(objectType) {
        case 0:
        case 1:
            return new Sphere(x, y, z);
            break;
        case 2:
        case 3:
            return new Cube(x, y, z);
            break;
        default:
            return new Octahedron(x, y, z);
            break;
    }
}

//Atualiza todos os objetos do jogo, incluindo o jogador
void GameManager::update()
{
    for(size_t i=0; i<gameObjs.size(); ++i) {
        gameObjs[i]->update(player->pos);
        gameObjs[i]->checkCollision(player->pos, player->collisionRadius);
    }

    player->processInputs3(leftKeyFlag, rightKeyFlag,
                          upKeyFlag, downKeyFlag,
                          mouseX, mouseY,
                          leftMouseButton, rightMouseButton);

    if(player->vulnerabilityCoolDown==0) {//Verifica colis�es com o jogador
        for(size_t i=0; i<gameObjs.size(); ++i) {
            if(gameObjs[i]->checkCollision(player->pos, player->collisionRadius)) {
                player->hit();
                break;
            }
        }
        if(player->vulnerabilityCoolDown==0) {
            if(playerOutOfBounds()) {
                player->hit();
            }
        }
    }

    //Recentraliza o mouse;
    glutWarpPointer(WINDOW_CENTER_X, WINDOW_CENTER_Y);
}

//Desenha toda a cena de um determinado frame do jogo
void GameManager::drawEverything()
{
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	//Define a camera para este frame
	Point3D adjustedLookAt = player->pos;
	vectorAdd(&adjustedLookAt, &(player->lookAt));
    gluLookAt(	player->pos.x, player->pos.y, player->pos.z,
				adjustedLookAt.x, adjustedLookAt.y, adjustedLookAt.z,
				player->up.x, player->up.y, player->up.z);

    drawCheckerboard(0); //Desenha um piso xadrez
    drawCheckerboard(300); //Desenha um teto xadrez

    for(size_t i=0; i<gameObjs.size(); i++) {
        gameObjs[i]->draw();
    }

    drawHUD();

    glutSwapBuffers();
}

void GameManager::drawHUD()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
      glLoadIdentity();
      gluOrtho2D(0.0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0);
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
        glLoadIdentity();

        drawPoints(player->points);

        drawHealthBar(player->currentHealth, player->maxHealth);

        drawCrossHair();

        if (player->vulnerabilityCoolDown > 0) {
            drawDamageIndicator();
        }

        glMatrixMode(GL_PROJECTION);
      glPopMatrix();
      glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

//M�todo chamado pelo objeto player ao atirar, verifica entre os objetos da lista
//gameObjs qual o mais pr�ximo na frente da linha de disparo, se houver.
void GameManager::shotsFired()
{
    Point3D origin = player->pos;
    Point3D direction = player->lookAt;
    float tempDistance;
    float lowerDistance = FLT_MAX;
    GameObject* shotObject = NULL;
    for(size_t i=0; i<gameObjs.size(); ++i) {
        tempDistance = gameObjs[i]->checkShotCollision(origin, direction);
        if(tempDistance!=-1.0 && tempDistance<lowerDistance) {
            lowerDistance = tempDistance;
            shotObject = gameObjs[i];
        }
    }

    if(shotObject != NULL) {
        shotObject->hit(origin);
        player->points += 100;
        idleObjects--;
        if(idleObjects==0) {
            resetObjects();
        }
    }
}

//Retorna 1 se o jogador est� fora dos limites do ch�o (caso em que dever� receber dano)
int GameManager::playerOutOfBounds()
{
    float floorExpanse = (float)FLOOR_EXPANSE;
    if(player->pos.x > floorExpanse || player->pos.x < -floorExpanse ||
       player->pos.z > floorExpanse || player->pos.z < -floorExpanse ) {
        return 1;
       }
    return 0;
}

void GameManager::resetObjects()
{
    int r;
    for(size_t i=0; i<gameObjs.size(); i++) {
        r = rand()%4;
        if(r==0) {
            gameObjs[i]->reset(originalPos[i]);
            idleObjects++;
        }
    }
}
