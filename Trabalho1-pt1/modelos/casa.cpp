#include "casa.h"

Casa::Casa( ) : MyObject( 2 ){
}

Casa::~Casa( ){
}

Casa::Casa( Vetor3D tn, Vetor3D rn, Vetor3D sn ) : MyObject( 2 ){
    trans = tn; rotat = rn; scale = sn;
    origin = false;
}


void Casa::desenha(){
    bool changCullFace = true;

    glPushMatrix();
    MyObject::desenha();
    glScalef( 1,1,1 );

        if( origin )
            GUI::drawOrigin( 0.5 );

        if( reflect ){
            GUI::glReflectPlaneXYf();
        }

        GUI::glShearXYf(shear.x, shear.y);

        if(changCullFace) glDisable(GL_CULL_FACE);
        glBegin(GL_TRIANGLES);    //telhado -frontal
        glNormal3f(0,1,1);
        GUI::setColor( 1,0,0, 1,true);
            glVertex3f( 1, 0.8,  1);
            glVertex3f( 0, 1.8,  0);
            glVertex3f(-1, 0.8,  1);
        glEnd();
        if(changCullFace) glEnable(GL_CULL_FACE);


        if(changCullFace) glDisable(GL_CULL_FACE);
        glBegin(GL_TRIANGLES);    //telhado -esquerdo front
        glNormal3f(-1,1,0);
        GUI::setColor( 0,1,0, 1,true); //full green
            glVertex3f(-1, 0.8,  1);
            glVertex3f( 0, 1.8,  0);
            glVertex3f(-1, 0.8,  0);
        glEnd();
        if(changCullFace) glEnable(GL_CULL_FACE);

        if(changCullFace) glDisable(GL_CULL_FACE);
        glBegin(GL_TRIANGLES);    //telhado -esquerdo back
        glNormal3f(-1,1,0);
        GUI::setColor( 0.7, 0.3, 0.7, 1,true);
            glVertex3f(-1, 0.8,  0);
            glVertex3f( 0, 1.8,  0);
            glVertex3f(-1, 0.8, -1);
        glEnd();
        if(changCullFace) glEnable(GL_CULL_FACE);

        if(changCullFace) glDisable(GL_CULL_FACE);
        glBegin(GL_TRIANGLES);    //telhado -trazeiro
        glNormal3f(0,1,-1);
        GUI::setColor(0, 0, 1, 1,true); //full blue
            glVertex3f(-1, 0.8, -1);
            glVertex3f( 0, 1.8,  0);
            glVertex3f( 1, 0.8, -1);
        glEnd();
        if(changCullFace) glEnable(GL_CULL_FACE);

        if(changCullFace) glDisable(GL_CULL_FACE);
        glBegin(GL_TRIANGLES);    //telhado -direito front
        glNormal3f(1,1,0);
        GUI::setColor(0,1,0, 1,true);
            glVertex3f( 1, 0.8,  0);
            glVertex3f( 0, 1.8,  0);
            glVertex3f( 1, 0.8,  1);
        glEnd();
        if(changCullFace) glEnable(GL_CULL_FACE);

        if(changCullFace) glDisable(GL_CULL_FACE);
        glBegin(GL_TRIANGLES);    //telhado -direito back
        glNormal3f(1,1,0);
        GUI::setColor(0.7, 0.3, 0.7, 1,true);
            glVertex3f( 1, 0.8, -1);
            glVertex3f( 0, 1.8,  0);
            glVertex3f( 1, 0.8,  0);
        glEnd();
        if(changCullFace) glEnable(GL_CULL_FACE);

                    // desenhando porta
                    glPushMatrix();
                        glTranslatef(0.2, 0, 0.9008);
                        if(changCullFace) glDisable(GL_CULL_FACE);
                        glBegin(GL_POLYGON);
                        GUI::setColor(0.60, 0.30,   0.1);
                            glVertex3f(    0,   0, 0 );
                            glVertex3f( 0.45,   0, 0 );
                            glVertex3f( 0.45, 0.6, 0 );
                            glVertex3f(    0, 0.6, 0 );
                        glEnd();
                        if(changCullFace) glEnable(GL_CULL_FACE);
                    glPopMatrix();

                    //desenhando janela
                    glPushMatrix();
                        glTranslatef(-0.7, 0.2, 0.9008);
                        if(changCullFace) glDisable(GL_CULL_FACE);
                        glBegin(GL_POLYGON);
                        GUI::setColor(0.5, 0.5, 0.7);
                            glVertex3f( 0.65,   0, 0 );
                            glVertex3f( 0.65, 0.4, 0 );
                            glVertex3f(    0, 0.4, 0 );
                            glVertex3f(    0,   0, 0 );
                        glEnd();
                        if(changCullFace) glEnable(GL_CULL_FACE);
                    glPopMatrix();

        if(changCullFace) glDisable(GL_CULL_FACE);
        glBegin(GL_POLYGON);
        glNormal3f(0,1,1);
        GUI::setColor(0.8, 1,0, 1,true); //mid yellow
            glVertex3f( 0.9,   0,  0.9);
            glVertex3f( 0.9, 0.9,  0.9);
            glVertex3f(-0.9, 0.9,  0.9);
            glVertex3f(-0.9,   0,  0.9);
        glEnd();
        if(changCullFace) glEnable(GL_CULL_FACE);

        if(changCullFace) glDisable(GL_CULL_FACE);
        glBegin(GL_POLYGON);
        GUI::setColor(0, 0, 1); //full blue
            glVertex3f(-0.9,   0,  0.9);
            glVertex3f(-0.9, 0.9,  0.9);
            glVertex3f(-0.9, 0.9, -0.9);
            glVertex3f(-0.9,   0, -0.9);
        glEnd();
        if(changCullFace) glEnable(GL_CULL_FACE);

        if(changCullFace) glDisable(GL_CULL_FACE);
        glBegin(GL_POLYGON);
        GUI::setColor(0.7, 0.3, 0.7, 1, true);
            glVertex3f(-0.9,    0, -0.9);
            glVertex3f(-0.9,  0.9, -0.9);
            glVertex3f( 0.9,  0.9, -0.9);
            glVertex3f( 0.9,    0, -0.9);
        glEnd();
        if(changCullFace) glEnable(GL_CULL_FACE);

        if(changCullFace) glDisable(GL_CULL_FACE);
        glBegin(GL_POLYGON);
        glNormal3f(1,1,0);
        GUI::setColor(1, 0, 0, 1,true); //full red
            glVertex3f( 0.9,    0, -0.9);
            glVertex3f( 0.9,  0.9, -0.9);
            glVertex3f( 0.9,  0.9,  0.9);
            glVertex3f( 0.9,    0,  0.9);
        glEnd();
        if(changCullFace) glEnable(GL_CULL_FACE);

    glPopMatrix();

    if( selected ){
        glPushMatrix();
        MyObject::desenha();
            glTranslatef(0,1.78,0);
            glScalef(0.5,0.5,0.5);

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
            glBegin(GL_TRIANGLES);        //Face 1 - sentido anti-hor
            glNormal3f(0,0,1);
                glVertex3f(0.5,1,0.5);
                glVertex3f(-0.5,1,0.5);
                glVertex3f(0,0.2,0);
            glEnd();
            glBegin(GL_TRIANGLES);        //Face 2 - sentido anti-hor
            glNormal3f(1,0,0);
                glVertex3f(0.5,1,-0.5);
                glVertex3f(0.5,1,0.5);
                glVertex3f(0,0.2,0);
            glEnd();
            glBegin(GL_TRIANGLES);        //Face 3 - sentido anti-hor
            glNormal3f(0,0,-1);
                glVertex3f(-0.5,1,-0.5);
                glVertex3f(0.5,1,-0.5);
                glVertex3f(0,0.2,0);
            glEnd();
            glBegin(GL_TRIANGLES);        //Face 4 - sentido anti-hor
            glNormal3f(-1,0,0);
                glVertex3f(-0.5,1,0.5);
                glVertex3f(-0.5,1,-0.5);
                glVertex3f(0,0.2,0);
            glEnd();
        glPopMatrix();
    }
}

void Casa::updateSelection(){
    this->selected = !this->selected;
}

void Casa::unSelect(){
    this->selected = false;
}
