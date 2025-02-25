#include "pinheiro.h"

Pinheiro::Pinheiro() : MyObject( 5 ){
}

Pinheiro::~Pinheiro( ){
}

Pinheiro::Pinheiro( Vetor3D tn, Vetor3D rn, Vetor3D sn ) : MyObject( 5 ){
    trans = tn; rotat = rn; scale = sn;
    origin = false;
}

void Pinheiro::desenha(){

    glPushMatrix();
    MyObject::desenha();
    //glTranslatef(0,0.008,0.02);
    //glScalef(0.95, 0.95, 0.95);
    if( origin )
        GUI::drawOrigin(0.5);

    if( reflect ){
        GUI::glReflectPlaneXZf();
    }

    GUI::glShearXYf(shear.x, shear.y);

    //Quadrica para os Cones/Cilindros
    GLUquadricObj *quad = gluNewQuadric();

    gluQuadricNormals(quad, GLU_SMOOTH);  // Create Smooth Normals
    gluQuadricTexture(quad, GL_TRUE);     // Create Texture Coords

        glPushMatrix();
            glTranslated(0,0.52,0);     //altura da árvore
                glPushMatrix();             //cone Superior
                    GUI::setColor(0.1,0.7,0.2);
                    glTranslated(0,0.6,0);
                    glRotatef(-90, 1,0,0);

                    glPushMatrix();
                        gluCylinder( quad, 0.4,0.001, 0.8, 12,20 );
                    glPopMatrix();
                    glPushMatrix();
                        glRotatef(180, 0,1,0);
                        gluDisk(quad, 0.12, 0.4, 12, 20);
                    glPopMatrix();
                glPopMatrix();

                glPushMatrix();             //cone Inferior
                    GUI::setColor(0.1,0.6,0.0);
                    glRotatef(-90, 1,0,0);

                    glPushMatrix();
                        gluCylinder( quad, 0.6,0.001, 0.9, 12,20 );
                    glPopMatrix();
                    glPushMatrix();
                        glRotatef(180, 0,1,0);
                        gluDisk(quad, 0,0.6, 12, 20);
                    glPopMatrix();

                glPopMatrix();
        glPopMatrix();

        glPushMatrix();         //tronco da arvore
            GUI::setColor(0.6,0.5,0.1);
            glTranslatef(0,0.10,0);
            glRotatef(-90, 1,0,0);
            gluCylinder(quad, 0.2, 0.2, 0.62, 10,10 );
        glPopMatrix();

        //jarro da arvore
                GLfloat tampAlt = 0.10, tampLarg = 0.45;
                GLfloat baseLarg = 0.4;
        glPushMatrix();
            GUI::setColor(0.3,0.2,0);
            glRotatef(-90, 1,0,0);

            glPushMatrix();        //tampa do jarro
                glTranslatef(0, 0, tampAlt);
                gluDisk(quad, 0.18, tampLarg, 15,10);
            glPopMatrix();

            glPushMatrix();        //corpo do jarro
                gluCylinder(quad, baseLarg,tampLarg, tampAlt, 15, 10 );
            glPopMatrix();

            glPushMatrix();        //base do jarro
                glRotatef(180, 0,1,0);
                gluDisk(quad, 0,baseLarg, 15,10 );
            glPopMatrix();
        glPopMatrix();


    gluDeleteQuadric(quad);

    glPopMatrix();

    if( selected ){
        glPushMatrix();
        MyObject::desenha();
            glTranslatef(0,1.9,0);     //translação da piramide de selecao
            glScalef(0.3,0.3,0.3);      //escala da piramide de selecao

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
