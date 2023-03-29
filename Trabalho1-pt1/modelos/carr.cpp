#include "carr.h"


Carr::Carr( ) : MyObject( 1 ){
    carrModel = new Model3DS( "../3ds/maclaren.3DS" );
}

Carr::~Carr( ){
}

Carr::Carr(Vetor3D tn, Vetor3D an, Vetor3D sn) : MyObject( 1 ){
    t = tn; a = an; s = sn;
    origem = false;
    carrModel = new Model3DS( "../3ds/maclaren.3DS" );
}

void Carr::desenha(){

    glPushMatrix();
        GUI::draw3ds( *carrModel,  0,0,0,  0,0,0,  0.7,0.7,0.7);
    glPopMatrix();

    glPushMatrix();
        if( selected ){

            GUI::setColor( 0,0,0.9,  0.25 );
            GUI::drawBox( -0.412,0.480,0.861,  0.412,0.015,-0.861 );
        }
    glPopMatrix();
}
