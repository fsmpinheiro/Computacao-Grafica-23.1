#include <iostream>
#include <gui.h>

using namespace std;

#include "Controller/controllersys.h"
#include "modelos/house.h"
#include "modelos/carr.h"


bool includNewObject = false;
ControllerSys controller = ControllerSys( );


void desenha( ){
    GUI::displayInit();

//iluminação
    GUI::setLight(1, 0,3,1.5, true,false);

    //referencia global (com sistema de coordenadas)
        GUI::setColor(0,1,0);
        GUI::drawFloor(7);
        GUI::drawOrigin(0.5);

    for( int i = 0; i < controller.getVectorSize( ); i++ ){
        glPushMatrix();
            controller.getByIndex( i )->desenha( );
        glPopMatrix();
    }


    //desenhando piso da garagem
        GUI::setColor(0.4,0.4,0);
        glPushMatrix();
            glTranslated(-1.5, 0.00002, 0.8);
            GUI::drawQuad(1.2, 3.4);
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


    GUI::displayEnd();
}


void teclado(unsigned char key, int x, int y) {
    GUI::keyInit(key, x, y);

    switch (key) {
    case 't':
        glutGUI::trans_obj = !glutGUI::trans_obj;
        break;
    case 'l':
        glutGUI::trans_luz = !glutGUI::trans_luz;
        break;

    case '+':
        includNewObject = !includNewObject;
        break;
    case ',':
        controller.prevObject( );
        break;
    case '.':
        controller.nextObject( );
        break;

    case ':':{
        controller.markUnMark( );
        break;
    }

    case '!':
        if( includNewObject ){
            controller.insertObject( 1 ); //insere carro
        }
        break;
    case '@':
        if( includNewObject ){
            controller.insertObject( 2 ); //insere cow
        }
        break;
    case '#':
        if( includNewObject ){
            controller.insertObject( 3 ); //insere casa
        }
        break;
    case '$':
        if( includNewObject ){
            controller.insertObject( 4 ); //insere reservatório
        }
        break;
    default:
        break;
    }
}


int main(){

    cout << "Hello World!" << endl;

    GUI gui = GUI(1280,800, desenha, teclado);
}

