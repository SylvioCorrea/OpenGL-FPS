//#include <stdlib.h>
//#include <GL/glut.h>
//#include <iostream>
//
//
//GLfloat rotX, rotY, rotX_ini, rotY_ini;
//GLfloat obsX, obsY, obsZ =200, obsX_ini, obsY_ini, obsZ_ini;
//GLfloat fAspect = 100, angle = 44;
//int x_ini,y_ini,bot;
//
//
//
//
//#define SENS_ROT	5.0
//#define SENS_OBS	10.0
//#define SENS_TRANSL	30.0
//
//
//
//
//void PosicionaObservador(void)
//{
//
//	glMatrixMode(GL_MODELVIEW);
//
//	glLoadIdentity();
//
//	glTranslatef(-obsX,-obsY,-obsZ);
//
//	glRotatef(rotX,1,0,0);
//	glRotatef(rotY,0,1,0);
//
//
//	gluLookAt(0.0,80.0,300.0,
//              0,0,200,
//              0.0,1.0,0.0);
//}
//void EspecificaParametrosVisualizacao(void)
//{
//
//	glMatrixMode(GL_PROJECTION);
//
//	glLoadIdentity();
//
//
//	gluPerspective(angle,fAspect,0.5,600);
//
//    PosicionaObservador();
//
//}
//void desenhaChao()
//    {
//        glColor3f(0, 0, 0.5);
//        glLineWidth(1);
//        glBegin(GL_LINES);
//        for(float z=-1000; z<=1000; z+=10)
//        {
//            glVertex3f(-1000,-0.1f,z);
//            glVertex3f( 1000,-0.1f,z);
//        }
//        for(float x=-1000; x<=1000; x+=10)
//        {
//            glVertex3f(x,-0.1f,-1000);
//            glVertex3f(x,-0.1f,1000);
//        }
//        glEnd();
//        glLineWidth(2);
//    }
//void Desenha(void)
//{
//
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//
//	EspecificaParametrosVisualizacao();
//
//    desenhaChao();
//
//	glPushMatrix();
//	glTranslatef(0,28,0);
//    glColor3f(0.0f, 0.0f, 1.0f);
//	glutWireTeapot(35);
//
//	glPopMatrix();
//
//
//
//
//	glFlush();
//}
//
//
//
//void AlteraTamanhoJanela(GLsizei w, GLsizei h)
//{
//	// Para previnir uma divisão por zero
//	if ( h == 0 ) h = 1;
//
//	// Especifica as dimensões da viewport
//	glViewport(0, 0, w, h);
//
//	// Calcula a correção de aspecto
//	fAspect = (GLfloat)w/(GLfloat)h;
//
//	EspecificaParametrosVisualizacao();
//}
//
//
//void Teclado (unsigned char key, int x, int y)
//{
//	if (key == 27)
//		exit(0);
//}
//
//
//void Inicializa (void)
//{
//
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//	glLineWidth(2.0);
//}
//
//void GerenciaMouse(int button, int state, int x, int y)
//{
//	if(state==GLUT_DOWN)
//	{
//		// Salva os parâmetros atuais
//		x_ini = x;
//		y_ini = y;
//		obsX_ini = obsX;
//		obsY_ini = obsY;
//		obsZ_ini = obsZ;
//		rotX_ini = rotX;
//		rotY_ini = rotY;
//		bot = button;
//	}
//	else bot = -1;
//}
//void GerenciaMovim(int x, int y)
//{
//
//	if(bot==GLUT_LEFT_BUTTON)
//	{
//
//		int deltax = x_ini - x;
//		int deltay = y_ini - y;
//
//		rotY = rotY_ini - deltax/SENS_ROT;
//		rotX = rotX_ini - deltay/SENS_ROT;
//	}
//
//	else if(bot==GLUT_RIGHT_BUTTON)
//	{
//
//		int deltaz = y_ini - y;
//
//		obsZ = obsZ_ini + deltaz/SENS_OBS;
//
//
//	}
//
//	else if(bot==GLUT_MIDDLE_BUTTON)
//	{
//
//		int deltax = x_ini - x;
//		int deltay = y_ini - y;
//
//		obsX = obsX_ini + deltax/SENS_TRANSL;
//		obsY = obsY_ini - deltay/SENS_TRANSL;
//	}
//	PosicionaObservador();
//	glutPostRedisplay();
//}
//
//
//int main(void)
//{
//
//	int argc = 0;
//	char *argv[] = { (char *)"gl", 0 };
//
//	glutInit(&argc,argv);
//
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//
//
//	glutInitWindowPosition(5,5);
//
//
//	glutInitWindowSize(450,450);
//
//
//	glutCreateWindow("Camera, Projecao");
//
//
//	glutDisplayFunc(Desenha);
//
//
//	glutReshapeFunc(AlteraTamanhoJanela);
//
//	glutKeyboardFunc (Teclado);
//
//	glutMotionFunc(GerenciaMovim);
//
//	glutMouseFunc(GerenciaMouse);
//
//	Inicializa();
//
//	glutMainLoop();
//
//	return 0;
//}









#include "AllHeaders.h"

//Razão entre largura e altura da tela. Usado em gluPerspective
float whRatio = WINDOW_WIDTH/WINDOW_HEIGHT;

//Ponteiro para o principal objeto do jogo, o jogador. Entre outras
//coisas, este objeto controla a posição da câmera e a direção
//para onde ela está olhando

GameManager* manager;

////Flags de teclado
//int leftKeyFlag;
//int rightKeyFlag;
//int upKeyFlag;
//int downKeyFlag;
//
////Flags do mouse. Não usadas por enquanto
//int leftMouseButton;
//int rightMouseButton;
//
////Registra a posição do mouse na janela.
////Glut considera (0,0) o canto superior esquerdo da janela
//int mouseX;
//int mouseY;




//Inicializa flags, variáveis e objetos para o início do porgrama
void setup()
{
//    leftKeyFlag = 0;
//    rightKeyFlag = 0;
//    upKeyFlag = 0;
//    downKeyFlag = 0;
//
//    leftMouseButton = 0;
//    rightMouseButton = 0;
//
//    mouseX = WINDOW_CENTER_X;
//    mouseY = WINDOW_CENTER_Y;
//
//    Point3D p; //Posição inicial de player
//    p.x = 300.0f;
//    p.y = 150.0f;
//    p.z = 300.0f;
//
//    player = new Player(p);
//
//    GameObject* sphere = new Sphere();
//    gameObjs.push_back(sphere);
//    GameObject* cube = new Cube(-200.0, 50.0, -200.0);
//    gameObjs.push_back(cube);

    manager = new GameManager();
}

void changeSize(int w, int h) {

	//Evita a divisão por zero
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	//matriz de projeção
	glMatrixMode(GL_PROJECTION);

	//reseta matriz
	glLoadIdentity();

	//viewport equivalente a window
	glViewport(0, 0, w, h);

	//perspectiva
	gluPerspective(45.0f, ratio, NEAR_CLIP, FAR_CLIP);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {

//	// Clear Color and Depth Buffers
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	// Reset transformations
//	glLoadIdentity();
//
//	//Player processa inputs de mouse e teclado
//	player->processInputs3( leftKeyFlag,
//                            rightKeyFlag,
//                            upKeyFlag,
//                            downKeyFlag,
//                            mouseX,
//                            mouseY);
//
//    //Recentraliza o mouse;
//    glutWarpPointer(WINDOW_CENTER_X, WINDOW_CENTER_Y);
//	//Define a camera para este frame
//    float la[9];
//	player->getLookAt(la);
//
//	gluLookAt(	la[0], la[1], la[2],
//				la[3], la[4], la[5],
//				la[6], la[7], la[8]);
//
//    drawCheckerboard(0); //Desenha um piso xadrez
//    drawCheckerboard(300); //Desenha um teto xadrez
//
//    for(size_t i=0; i<gameObjs.size(); i++) {
//        gameObjs[i]->draw();
//    }
//
//    player->drawHUD();
//
//    glutSwapBuffers();
    manager->drawEverything();
}

void gameLoop(int n)
{
    //Atualiza os objetos do jogo
    manager->update();
    //Chama a função de desenho
    glutPostRedisplay();
    //Define que uma nova chamada desta função deverá ser feita
    glutTimerFunc(GAMELOOP_TIMER, gameLoop, 1);
}

void specialKeyPress(int key, int xx, int yy)
{
    switch (key) {
		case GLUT_KEY_LEFT :
			manager->leftKeyFlag = 1;
			break;
		case GLUT_KEY_RIGHT :
			manager->rightKeyFlag = 1;
			break;
		case GLUT_KEY_UP :
		    manager->upKeyFlag = 1;
			break;
		case GLUT_KEY_DOWN :
			manager->downKeyFlag = 1;
			break;
	}
}

void specialKeyRelease(int key, int xx, int yy)
{
    switch (key) {
		case GLUT_KEY_LEFT :
			manager->leftKeyFlag = 0;
			break;
		case GLUT_KEY_RIGHT :
			manager->rightKeyFlag = 0;
			break;
		case GLUT_KEY_UP :
		    manager->upKeyFlag = 0;
			break;
		case GLUT_KEY_DOWN :
			manager->downKeyFlag = 0;
			break;
	}
}

void safeExit()
{
    //Aparentemente a mudança desta variável influencia até mesmo outras aplicações
    //portanto ela é retornada para o default aqui antes de fechar o programa.
    glutSetKeyRepeat(GLUT_KEY_REPEAT_DEFAULT);
    exit(0);
}

void normalKeyPress(unsigned char key, int x, int y)
{
    switch (key) {
		case 'a' :
			manager->leftKeyFlag = 1;
			break;
		case 'd' :
			manager->rightKeyFlag = 1;
			break;
		case 'w' :
		    manager->upKeyFlag = 1;
			break;
		case 's' :
			manager->downKeyFlag = 1;
			break;
        case 27 :
            safeExit();
	}
}

void normalKeyRelease(unsigned char key, int x, int y)
{
    switch (key) {
		case 'a' :
			manager->leftKeyFlag = 0;
			break;
		case 'd' :
			manager->rightKeyFlag = 0;
			break;
		case 'w' :
		    manager->upKeyFlag = 0;
			break;
		case 's' :
			manager->downKeyFlag = 0;
			break;
	}
}

void mousePassiveMovement(int x, int y)
{
    manager->mouseX = x;
    manager->mouseY = y;
}

void mouseButtons(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON) {
        if(state==GLUT_DOWN) {
            manager->leftMouseButton = 1;
        } else if (state==GLUT_UP) {
            manager->leftMouseButton = 0;
        }
    }
}

int main(int argc, char **argv) {

	//configurações iniciais glut openGL
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Camera Test");
	gluPerspective(45.0f, whRatio, NEAR_CLIP, FAR_CLIP);


	//Inicialização dos objetos e variáveis do jogo
	setup();


    //Define callbacks para eventos do teclado
    glutKeyboardFunc(normalKeyPress);
    glutKeyboardUpFunc(normalKeyRelease);
	glutSpecialFunc(specialKeyPress);
	glutSpecialUpFunc(specialKeyRelease);
    //Manter a tecla pressionada não registra multiplos eventos:
    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

    //Define callbacks para eventos do mouse
    glutPassiveMotionFunc(mousePassiveMovement);
    glutMouseFunc(mouseButtons);

	//Define callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	//glutIdleFunc(renderScene);
	glutTimerFunc(GAMELOOP_TIMER, gameLoop, 1);

    glutWarpPointer(WINDOW_CENTER_X, WINDOW_CENTER_Y);//Centraliza mouse
    glutSetCursor(GLUT_CURSOR_NONE);//ponteiro do mouse invisível

    // Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();

	return 1;
}
