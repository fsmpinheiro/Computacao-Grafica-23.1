#include "reservatory.h"


Reservatory::Reservatory( ) : MyObject( 4 ){
}

Reservatory::~Reservatory( ){
}

Reservatory::Reservatory( Vetor3D tn, Vetor3D an, Vetor3D sn ) : MyObject( 4 ){
    t = tn; a = an; s = sn;
    origem = false;
}

void Reservatory::desenha( ){
    origem = true;

    glPushMatrix();
    glScalef( 1,1,1 );
        GUI::setColor( 0.8,  0.8,    0.8);
        glPushMatrix(); //esfera
            glTranslatef(0, 2.15, 0);
            GUI::drawSphere( 0, 0, 0, 0.9);
        glPopMatrix();

        glPushMatrix(); //topo das pernas
            glTranslatef(-0.4, 1.198, -0.4);
            GUI::drawBox(0,0,0,  0.8,0.3,0.8);
        glPopMatrix();

        glPushMatrix(); //pernas
            glTranslatef( -0.5,0,0.20 );
            GUI::drawBox(0.1, 0, 0.1,  0.2,1.20,0.2 );
        glPopMatrix();

        glPushMatrix(); //pernas
            glTranslatef( 0.2, 0, 0.20);
            GUI::drawBox(0.1, 0, 0.1,  0.2,1.20,0.2 );
        glPopMatrix();

        glPushMatrix(); //pernas
            glTranslatef( -0.5,0,-0.5 );
            GUI::drawBox(0.1, 0, 0.1,  0.2,1.20,0.2 );
        glPopMatrix();

        glPushMatrix(); //pernas
            glTranslatef( 0.2,0,-0.5 );
            GUI::drawBox(0.1, 0, 0.1,  0.2,1.20,0.2 );
        glPopMatrix();

    glPopMatrix();

    glPushMatrix();
        if( selected ){

            GUI::setColor( 0,0,0.9,  0.35 );
            GUI::drawBox( -0.46,0.005,-0.46,  0.46,1.6,0.46 );
        }
    glPopMatrix();
}
