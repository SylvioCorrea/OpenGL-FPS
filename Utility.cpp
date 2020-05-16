#include "AllHeaders.h"



void printLookAt(float* la)
{
    for(int i=0; i<9; i++) {
        cout << " la[" << i << "]=" << la[i];
    }
    cout << endl;
}

Point3D createPoint3D(float x, float y, float z)
{
    Point3D res;
    res.x = x;
    res.y = y;
    res.z = z;
    return res;
}


//=====================================================================
//Funções gerais de desenho

//Pequena alteração da função DesenhaChão da professora
//y = altura em que o plano xadrez será desenhado
void drawCheckerboard(float y)
{
    //Flags para determinar a cord de cada quadrado
	bool flagx, flagz;

	//Define a normal
	float normalY = (y>=0)? 1 : -1;

	glNormal3f(0,normalY,0);

	flagx = false;

	glBegin(GL_QUADS);
	//X varia de -FLOOR_EXPANSE a FLOOR_EXPANSE, de TILE_SIZE em TILE_SIZE
	for(float x=-FLOOR_EXPANSE; x<FLOOR_EXPANSE; x+=TILE_SIZE)
	{
		//Flagx determina a cor inicial
		if(flagx) flagz = false;
		else flagz = true;
		//Z varia de -FLOOR_EXPANSE a FLOOR_EXPANSE, de TILE_SIZE em TILE_SIZE
		for (float z=-FLOOR_EXPANSE;z<FLOOR_EXPANSE;z+=TILE_SIZE)
		{
			//Escolhe cor
			if(flagz)
				glColor3f(0.4,0.4,0.4);
			else
				glColor3f(1,1,1);
			//E desenha o quadrado

			glVertex3f(x,y,z);
			glVertex3f(x+TILE_SIZE,y,z);
			glVertex3f(x+TILE_SIZE,y,z+TILE_SIZE);
			glVertex3f(x,y,z+TILE_SIZE);

			//Alterna cor
			flagz = !flagz;
		}
		//A cada coluna, alterna cor inicial
		flagx = !flagx;
	}

	glEnd();
}

void drawPoints(int n)
{
    glColor3f(1.0, 1.0, 1.0);
    float pointsY = HEALTH_BAR_X_Y + HEALTH_BAR_HEIGHT + 15;
    glRasterPos2f(HEALTH_BAR_X_Y, pointsY);

    ostringstream convert;
    convert << n;

    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)(convert.str().c_str()));

    glColor3f(0.0, 0.3, 0.3);
    glBegin(GL_QUADS);
        glVertex2f(HEALTH_BAR_X_Y, HEALTH_BAR_X_Y + HEALTH_BAR_HEIGHT);
        glVertex2f(HEALTH_BAR_X_Y + HEALTH_BAR_WIDTH, HEALTH_BAR_X_Y + HEALTH_BAR_HEIGHT);
        glVertex2f(HEALTH_BAR_X_Y + HEALTH_BAR_WIDTH, pointsY+5);
        glVertex2f(HEALTH_BAR_X_Y, pointsY+5);
    glEnd();
}

void drawHealthBar(float currentHealth, float maxHealth)
{
    glBegin(GL_QUADS);
        glColor3f(0.0, 1.0, 0.0);
        float xCap = HEALTH_BAR_X_Y + (HEALTH_BAR_WIDTH * (currentHealth/maxHealth) );
        if(xCap)
        glVertex2f(HEALTH_BAR_X_Y, HEALTH_BAR_X_Y);
		glVertex2f(xCap, HEALTH_BAR_X_Y);
        glVertex2f(xCap, HEALTH_BAR_X_Y + HEALTH_BAR_HEIGHT);
        glVertex2f(HEALTH_BAR_X_Y, HEALTH_BAR_X_Y + HEALTH_BAR_HEIGHT);
    glEnd();
    //Desenha uma barra vermelha equivalente ao totla de vida do jogador
    glBegin(GL_QUADS);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(HEALTH_BAR_X_Y, HEALTH_BAR_X_Y);
		glVertex2f(HEALTH_BAR_X_Y + HEALTH_BAR_WIDTH, HEALTH_BAR_X_Y);
        glVertex2f(HEALTH_BAR_X_Y + HEALTH_BAR_WIDTH, HEALTH_BAR_X_Y + HEALTH_BAR_HEIGHT);
        glVertex2f(HEALTH_BAR_X_Y, HEALTH_BAR_X_Y + HEALTH_BAR_HEIGHT);
    glEnd();
    //Desenha por cima uma barra verde equivalente à quantidade de vida
    //que o jogador possui no momento

}

void drawCrossHair()
{
    float halfLine = WINDOW_HEIGHT/20.0f;
    glColor3f(1.0f, 0.6f, 0.0f);
    glLineWidth(1.5);
    glBegin(GL_LINES);
        glVertex2f(WINDOW_CENTER_X - halfLine, (float)WINDOW_CENTER_Y);
        glVertex2f(WINDOW_CENTER_X + halfLine, (float)WINDOW_CENTER_Y);
        glVertex2f((float)WINDOW_CENTER_X, WINDOW_CENTER_Y - halfLine);
        glVertex2f((float)WINDOW_CENTER_X, WINDOW_CENTER_Y + halfLine);
    glEnd();
}

void drawDamageIndicator()
{
    glEnable(GL_BLEND);
      glDepthMask(GL_FALSE);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glColor4f(1.0, 0.0, 0.0, 0.4);
            glBegin(GL_QUADS);
                glVertex2f(0.0, 0.0);
                glVertex2f(WINDOW_WIDTH, 0.0);
                glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT);
                glVertex2f(0.0, WINDOW_HEIGHT);
            glEnd();

      glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}



//=====================================================================
//Cores

ColorRGB getColorRed()
{
    ColorRGB c;
    c.r = 1.0;
    c.g = 0.0;
    c.b = 0.0;
    return c;
}

ColorRGB getColorGreen()
{
    ColorRGB c;
    c.r = 0.0;
    c.g = 1.0;
    c.b = 0.0;
    return c;
}

ColorRGB getColorBlue()
{
    ColorRGB c;
    c.r = 0.0;
    c.g = 0.0;
    c.b = 1.0;
    return c;
}
