#include "myobject.h"

MyObject::MyObject( int k ){
    kind = k;
}

void MyObject::desenha( ){

    glTranslatef( trans.x, trans.y, trans.z );
    glRotatef( rotat.z, 0, 0, 1);
    glRotatef( rotat.y, 0, 1, 0);
    glRotatef( rotat.x, 1, 0, 0);

//    if( origin ){
//        GUI::drawOrigin( 0.5 );
//    }

    glScalef( scale.x, scale.y, scale.z );
}
