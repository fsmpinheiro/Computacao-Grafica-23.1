#include "reservatory.h"

Reservatory::Reservatory( ) : MyObject( 4 ){
}

Reservatory::~Reservatory( ){
}

Reservatory::Reservatory( Vetor3D tn, Vetor3D rn, Vetor3D sn ) : MyObject( 4 ){
    trans = tn; rotat = rn; scale = sn;
    origin = false;
}


void Reservatory::desenha( ){


    glPushMatrix();
    MyObject::desenha();
    glScalef( 1,1,1 );

        if( origin )
            GUI::drawOrigin( 0.5);

        if( reflect ){
            //GUI::glReflectPlaneXYf();
            glTranslatef(0,3.5,0);
            GUI::glReflectPlaneXZf();
        }

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

    if( selected ){
    glPushMatrix();
    MyObject::desenha();
        glTranslatef(0,3.05,0);
        glScalef(0.35,0.35,0.35);

        if( glutGUI::trans_obj ){
            GUI::setColor(   0,    0,  0.9, 0.45 ); //especular 0.35
            GUI::drawSphere(0,1.4,0, 0.3);
        }

        if( glutGUI::trans_obj && glutGUI::enable_translate){
            GUI::setColor( 0.9,  0.3,    0, 0.45 ); //especular 0.35
        }else if(glutGUI::trans_obj && glutGUI::enable_rotate){
            GUI::setColor( 0.5,  0.9,  0.3, 0.45 ); //especular 0.35
        }else if(glutGUI::trans_obj && glutGUI::enable_scale){
            GUI::setColor( 0.8,    1,  0.1, 0.45 ); //especular 0.35
        }else{
            GUI::setColor(   0,    0,  0.9, 0.45 ); //especular 0.35
        }

        glBegin(GL_POLYGON);        //base da pirâmide
            glNormal3f(0,1,0);
            glVertex3f(0.5,1,0.5);
            glVertex3f(0.5,1,-0.5);
            glVertex3f(-0.5,1,-0.5);
            glVertex3f(-0.5,1,0.5);
        glEnd();
        glBegin(GL_POLYGON);        //Face 1 - sentido anti-hor
            glNormal3f(0,0,1);
            glVertex3f(0.5,1,0.5);
            glVertex3f(-0.5,1,0.5);
            glVertex3f(0,0.2,0);
        glEnd();
        glBegin(GL_POLYGON);        //Face 2 - sentido anti-hor
            glNormal3f(1,0,0);
            glVertex3f(0.5,1,-0.5);
            glVertex3f(0.5,1,0.5);
            glVertex3f(0,0.2,0);
        glEnd();
        glBegin(GL_POLYGON);        //Face 3 - sentido anti-hor
            glNormal3f(0,0,-1);
            glVertex3f(-0.5,1,-0.5);
            glVertex3f(0.5,1,-0.5);
            glVertex3f(0,0.2,0);
        glEnd();
        glBegin(GL_POLYGON);        //Face 4 - sentido anti-hor
            glNormal3f(-1,0,0);
            glVertex3f(-0.5,1,0.5);
            glVertex3f(-0.5,1,-0.5);
            glVertex3f(0,0.2,0);
        glEnd();
    glPopMatrix();
    }
}
