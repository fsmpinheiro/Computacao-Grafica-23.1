#include "house.h"


House::House( ) : MyObject( 3 ){
}

House::~House( ){
}

House::House( Vetor3D tn, Vetor3D an, Vetor3D sn ) : MyObject( 3 ){
    t = tn; a = an; s = sn;
    origem = false;
}


void House::desenha( ){
    origem = true;



    float tr_py = 0.8;

    glPushMatrix();
    glScalef( 1,1,1 );

        glBegin(GL_POLYGON);    //telhado -frontal
        glNormal3f(0,1,1);
        GUI::setColor( 1,0,0, 1,true);
        glVertex3f( 1, tr_py + 0,  1);
        glVertex3f( 0, tr_py + 1,  0);
        glVertex3f(-1, tr_py + 0,  1);
        glEnd();

        glBegin(GL_POLYGON);    //telhado -esquerdo
        glNormal3f(-1,1,0);
        GUI::setColor( 0,1,0, 1,true); //full gree
            glVertex3f(-1, tr_py + 0,  1);
            glVertex3f( 0, tr_py + 1,  0);
            glVertex3f(-1, tr_py + 0, -1);
        glEnd();

        glBegin(GL_POLYGON);    //telhado -trazeiro
        glNormal3f(0,1,-1);
        GUI::setColor(0, 0, 1, 1,true); //full blue
            glVertex3f(-1, tr_py + 0, -1);
            glVertex3f( 0, tr_py + 1,  0);
            glVertex3f( 1, tr_py + 0, -1);
        glEnd();

        glBegin(GL_POLYGON);    //telhado -direito
        glNormal3f(1,1,0);
        GUI::setColor(0.7, 0.3, 0.7, 1,true);
            glVertex3f( 1, tr_py + 0, -1);
            glVertex3f( 0, tr_py + 1,  0);
            glVertex3f( 1, tr_py + 0,  1);
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
        glNormal3f(0,1,1);
        GUI::setColor(0.8, 1,0, 1,true); //mid yellow
            glVertex3f( 0.9,   0,  0.9);
            glVertex3f( 0.9, 0.9,  0.9);
            glVertex3f(-0.9, 0.9,  0.9);
            glVertex3f(-0.9,   0,  0.9);

        glEnd();

        glBegin(GL_POLYGON);
        GUI::setColor(0, 0, 1); //full blue
            glVertex3f(-0.9,   0,  0.9);
            glVertex3f(-0.9, 0.9,  0.9);
            glVertex3f(-0.9, 0.9, -0.9);
            glVertex3f(-0.9,   0, -0.9);
        glEnd();

        glBegin(GL_POLYGON);
        GUI::setColor(0.7, 0.3, 0.7);
            glVertex3f(-0.9,    0, -0.9);
            glVertex3f(-0.9,  0.9, -0.9);
            glVertex3f( 0.9,  0.9, -0.9);
            glVertex3f( 0.9,    0, -0.9);
        glEnd();

        glBegin(GL_POLYGON);
        glNormal3f(1,1,0);
        GUI::setColor(1, 0, 0); //full red
            glVertex3f( 0.9,    0, -0.9);
            glVertex3f( 0.9,  0.9, -0.9);
            glVertex3f( 0.9,  0.9,  0.9);
            glVertex3f( 0.9,    0,  0.9);
        glEnd();

    glPopMatrix();

    glPushMatrix();
        if( selected ){
            GUI::setColor(0,0,0.9,  0.35 );
            GUI::drawBox( -0.99,0.005,-1,  0.99,1.765,1 );
        }
    glPopMatrix();
}

