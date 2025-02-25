#include "cow.h"

Cow::Cow( ) : MyObject( 3 ){
    model = new Model3DS("../3ds/cow/Cow N050213.3DS");
}


Cow::~Cow( ){

}

Cow::Cow(Vetor3D tn, Vetor3D rn, Vetor3D sn) : MyObject( 3 ){
    trans = tn; rotat = rn; scale = sn;
    origin = false;
    model = new Model3DS("../3ds/cow/Cow N050213.3DS");
}


void Cow::desenha(){
    glPushMatrix();
    MyObject::desenha();

        glTranslatef(0, 0, 0);
        glRotatef(-90, 1, 0, 0);
        glScalef(0.0035,0.0035,0.0035);

        if( reflect ){
            GUI::glReflectPlaneXZf();
        }

        GUI::glShearXYf(shear.x, shear.y);
        model->draw();
    glPopMatrix();

    if(selected){
    glPushMatrix();
    MyObject::desenha();
        glTranslatef(0,0.95,0);
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
        }else if(glutGUI::trans_obj && glutGUI::enable_shear){
            GUI::setColor( 0.7,    0.3,  1, 0.45 ); //especular 0.35
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
