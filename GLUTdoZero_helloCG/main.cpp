#include <iostream>

using namespace std;

#include <gui.h>

Model3DS carro = Model3DS("../3ds/maclaren.3DS");
Model3DS cow   = Model3DS("../3ds/cow/Cow N050213.3DS");

float px = 0.0;
float tr_py = 0.8;

void desenha() {
    GUI::displayInit();

//iluminação
    GUI::setLight(1,0,1,3,true,false);

//referencia global (com sistema de coordenadas)
    GUI::setColor(0,1,0);
    GUI::drawFloor(7);
    GUI::drawOrigin(0.5);

//desenhando piso da garagem
    GUI::setColor(0.4,0.4,0);
    glPushMatrix();
        glTranslated(-1.5, 0.00002, 0.8);
        GUI::drawQuad(1.2, 3.4);
    glPopMatrix();

//desenhando caixa d'água.
    GUI::setColor( 0.8,  0.8,    0.8);
    glPushMatrix(); //esfera
        glTranslatef( -2.9, 2.15, -1.55);
        GUI::drawSphere( 0, 0, 0, 0.9);
    glPopMatrix();

    glPushMatrix(); //topo das pernas
        glTranslatef(-3.3, 1.198, -1.95);
        GUI::drawBox(0,0,0,  0.8,0.3,0.8);
    glPopMatrix();

    glPushMatrix(); //pernas
    glTranslatef( -3.4, 0, -1.35);
        GUI::drawBox(0.1, 0, 0.1,  0.2,1.20,0.2 );
    glPopMatrix();

    glPushMatrix(); //pernas
    glTranslatef( -2.7, 0, -1.35);
        GUI::drawBox(0.1, 0, 0.1,  0.2,1.20,0.2 );
    glPopMatrix();

    glPushMatrix(); //pernas
    glTranslatef( -3.4, 0, -2.05);
        GUI::drawBox(0.1, 0, 0.1,  0.2,1.20,0.2 );
    glPopMatrix();

    glPushMatrix(); //pernas
    glTranslatef( -2.7, 0, -2.05);
        GUI::drawBox(0.1, 0, 0.1,  0.2,1.20,0.2 );
    glPopMatrix();


//inserindo o objeto 3ds
    glPushMatrix();
        GUI::draw3ds(carro,-1.5,0,0.4,0,0,0,0.7,0.7,0.7);
    glPopMatrix();
    glPushMatrix();
        GUI::draw3ds(cow, 3.1, 0, -1.6, 0, 90, 1, 5.0, 5.5, 6 );
    glPopMatrix();


//modelando cercado diretamente no OpenGL
    glPushMatrix();
        GUI::setColor(0.60, 0.30,   0.1);
        glTranslatef(1.05,   -0.000012,  -1.7);
        GUI::drawBox(1.29,0,-0.8,1.32,0.5,0.8);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(3.05, 0.08, -2.3);
        GUI::drawBox( -0.75, 0, 1.29, 0.75, 0.3, 1.32);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(2.45,   -0.000012,  -1.7);
        GUI::drawBox(1.29,0,-0.8,1.32,0.5,0.8);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(3.05, 0.08, -3.75);
        GUI::drawBox( -0.75, 0, 1.29, 0.75, 0.3, 1.32);
    glPopMatrix();


//modelando casinha diretamente no OpenGL
    glBegin(GL_POLYGON);
    glNormal3f(0.5,0,1);
    GUI::setColor(1, 0, 0); //full red
        glVertex3f( 1, tr_py + 0,  1);
        glVertex3f( 0, tr_py + 1,  0);
        glVertex3f(-1, tr_py + 0,  1);
    glEnd();

    glBegin(GL_POLYGON);
    GUI::setColor(0, 1, 0); //full gree
        glVertex3f(-1, tr_py + 0,  1);
        glVertex3f( 0, tr_py + 1,  0);
        glVertex3f(-1, tr_py + 0, -1);
    glEnd();

    glBegin(GL_POLYGON);
    GUI::setColor(0, 0, 1); //full blue
        glVertex3f(-1, tr_py + 0, -1);
        glVertex3f( 0, tr_py + 1,  0);
        glVertex3f( 1, tr_py + 0, -1);
    glEnd();

    glBegin(GL_POLYGON);
    GUI::setColor(0.7, 0.3, 0.7);
        glVertex3f( 1, tr_py + 0, -1);
        glVertex3f( 0, tr_py + 1,  0);
        glVertex3f( 1, tr_py + 0,  1);
    glEnd();



    glBegin(GL_POLYGON);
    GUI::setColor(0, 1, 0); //full gree
        glVertex3f( 0.9,   0,  0.9);
        glVertex3f( 0.9, 0.9,  0.9);
        glVertex3f(-0.9, 0.9,  0.9);
        glVertex3f(-0.9,   0,  0.9);

    glEnd();

    glBegin(GL_POLYGON);
    GUI::setColor(0, 0, 1); //full gree
        glVertex3f(-0.9,   0,  0.9);
        glVertex3f(-0.9, 0.9,  0.9);
        glVertex3f(-0.9, 0.9, -0.9);
        glVertex3f(-0.9,   0, -0.9);
    glEnd();

    // desenhando porta
    glPushMatrix();
        glTranslatef(0.2, 0, 0.9008);
        glBegin(GL_POLYGON);
        GUI::setColor(0.60, 0.30,   0.1);
            glVertex3f( 0.45, 0, 0 );
            glVertex3f( 0.45, 0.6, 0 );
            glVertex3f( 0, 0.6, 0 );
            glVertex3f( 0, 0, 0 );
        glEnd();
    glPopMatrix();

    //desenhando janela
    glPushMatrix();
        glTranslatef(-0.7, 0.2, 0.9008);
        glBegin(GL_POLYGON);
        GUI::setColor(0.5,0.5,0.7);
            glVertex3f( 0.65, 0, 0 );
            glVertex3f( 0.65, 0.4, 0 );
            glVertex3f( 0, 0.4, 0 );
            glVertex3f( 0, 0, 0 );
        glEnd();
    glPopMatrix();

    glBegin(GL_POLYGON);
    GUI::setColor(0.7, 0.3, 0.7);
        glVertex3f(-0.9,    0, -0.9);
        glVertex3f(-0.9,  0.9, -0.9);
        glVertex3f( 0.9,  0.9, -0.9);
        glVertex3f( 0.9,    0, -0.9);
    glEnd();

    glBegin(GL_POLYGON);
    GUI::setColor(1, 0, 0); //full red
        glVertex3f( 0.9,    0, -0.9);
        glVertex3f( 0.9,  0.9, -0.9);
        glVertex3f( 0.9,  0.9,  0.9);
        glVertex3f( 0.9,    0,  0.9);
    glEnd();

    GUI::displayEnd();
}



void teclado(unsigned char key, int x, int y) {
    GUI::keyInit(key, x, y);

    switch (key) {
    case 'd':
        px += 0.1;
        break;
    case 'a':
        px -= 0.1;
        break;
    case 'L':
        glutGUI::trans_luz = !glutGUI::trans_luz;
        break;
    case 'U':
        tr_py += 0.01;
        break;
    case 'D':
        tr_py -= 0.01;
        break;
    default:
        break;
    }
}

int main()
{
    cout << "Hello World!" << endl;

    GUI gui = GUI(1280,800,desenha,teclado);
}



