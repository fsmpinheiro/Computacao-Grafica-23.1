#include "cow.h"


Cow::Cow( ) : MyObject( 2 ){
    cowModel = new Model3DS("../3ds/cow/Cow N050213.3DS");
}

Cow::~Cow( ){
}

Cow::Cow( Vetor3D tn, Vetor3D an, Vetor3D sn ) : MyObject( 2 ){
    t = tn; a = an; s = sn;
    origem = false;
    cowModel = new Model3DS("../3ds/cow/Cow N050213.3DS");
}

void Cow::desenha( ){

    glPushMatrix();
        GUI::draw3ds( *cowModel, 0,0,0,  0,90,0,  5.0,5.5,6);
    glPopMatrix();

    glPushMatrix();
        if( selected ){

            GUI::setColor( 0,0,0.9,  0.35 );
            GUI::drawBox( -0.210,0.005,-0.62,  0.210,0.765,0.60 );
        }
    glPopMatrix();
}
