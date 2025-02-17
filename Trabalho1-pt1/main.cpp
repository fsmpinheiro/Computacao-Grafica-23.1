#include <iostream>
#include <fstream>
//#include <string>
#include <vector>
#include <cmath>

using namespace std;

#include <gui.h>
#include <modelos/myobject.h>
#include <modelos/carro.h>
#include <modelos/casa.h>
#include <modelos/reservatory.h>
#include <modelos/cow.h>
#include <modelos/pinheiro.h>
//#include "modelos/pinheiro.h"


vector <MyObject*> objsVector;
vector <MyObject*> cenarioVector;

int posSelecionado = -1;
bool incluir_objeto = false;
int objsVectorSize = 0;

bool isFullScreen = false;
int windWidth = 1200, windHeight = 700; //render window dimensions

//-------------------iluminação-------------------
bool pontLight = true, spotLight = false;

//-------------------sombreamento-----------------
bool drawShadow = false;
float k_shadow = 0.0019;


//-------------------picking------------------
bool enable_pick = false;
bool picked = false;
vector <Vetor3D> pontosDeControle;

//int pontoSelecionado = 0;


void loadBasicScenario(){        //objetos fixos do cenário
    //Objetos fixos no cenário (fora do vetor interativo)

    //chão-estradas
    glPushMatrix();
        float posEstradaY = 0.001;
        glBegin(GL_POLYGON);        // eixo x
        glNormal3f(0,1,0);
        GUI::setColor(0.4, 0.5, 0.5,1, true);
            glVertex3f(-3.89, posEstradaY, -0.65);
            glVertex3f(-3.89, posEstradaY,  0.65);
            glVertex3f( 3.89, posEstradaY,  0.65);
            glVertex3f( 3.89, posEstradaY, -0.65);
        glEnd();
        glBegin(GL_POLYGON);        // eixo y_-z
        //glNormal3f(0,1,0);
            //GUI::setColor(0.4, 0.5, 0.5);
            glVertex3f(-0.4,  posEstradaY, -3.95);
            glVertex3f(-0.4,  posEstradaY, -0.658);
            glVertex3f( 0.68, posEstradaY, -0.658);
            glVertex3f( 0.68, posEstradaY, -3.95);
        glEnd();
        glBegin(GL_POLYGON);        // eixo y_+z
            glVertex3f(-0.4,  posEstradaY, 0.658);
            glVertex3f(-0.4,  posEstradaY, 3.95);
            glVertex3f( 0.68, posEstradaY, 3.95);
            glVertex3f( 0.68, posEstradaY, 0.658);
        glEnd();

    glPopMatrix();

    if( drawShadow ){
        //-------------------back-------------------
        glPushMatrix();
        GUI::setColor(0.4, 0.5, 0.5,1, true);
            glTranslated(0.0,5.0,-10.01);
            glRotatef(45, 1, 0, 0);
            GUI::drawFloor(20,20);
        glPopMatrix();

        //-------------------front-------------------
        glPushMatrix();
        GUI::setColor(0.4, 0.5, 0.5,1, true);
            glTranslated(0.0,5.0,10.01);
            glRotatef(-45, 1, 0, 0);
            GUI::drawFloor(20,20);
        glPopMatrix();

        //-------------------left-------------------
        glPushMatrix();
        GUI::setColor(0.4, 0.5, 0.5,1, true);
            glTranslated(-6, 4.0, 0.0); /*-5.99,4.0,0.0);*/
            glRotated(-90, 0, 0, 1);
            GUI::drawFloor(10,28);
        glPopMatrix();

        //-------------------right-------------------
        glPushMatrix();
        GUI::setColor(0.4, 0.5, 0.5,1, true);
            glTranslated(6, 4.0, 0.0); /*.01,4.0,0.0);*/
            glRotatef(90, 0, 0, 1);
            GUI::drawFloor(10,28);
        glPopMatrix();
    }
}


//-------------------picking------------------
void habilitaPontosDeControle(){
    //desenhando objetos controlaveis
    for (int i=0; i < objsVectorSize; i++ ){
        glPushName( i+1 ) ;
            objsVector[i]->desenha();
        glPopName();
    }
}

int picking( GLint cursorX, GLint cursorY, int w, int h ){
    int bufferSize = 512;
    GLuint selectBuff[512];

    GUI::pickingInit(cursorX, cursorY, w, h, selectBuff, bufferSize);
    GUI::displayInit();

    habilitaPontosDeControle();

    return GUI::pickingClosestName(selectBuff, bufferSize);
}

//-------------------picking------------------
//-------------------mouse button------------------
void mouseButtonMain(int button, int state, int x, int y){
    glutGUI::dtx = 0.0; glutGUI::dty = 0.0; glutGUI::dtz = 0.0;
    glutGUI::dax = 0.0; glutGUI::day = 0.0; glutGUI::daz = 0.0;
    glutGUI::dsx = 0.0; glutGUI::dsy = 0.0; glutGUI::dsz = 0.0;


    if( button == GLUT_LEFT_BUTTON ){
        if( state == GLUT_DOWN ){
            glutGUI::lbpressed = true;

            if( enable_pick && !glutGUI::trans_obj ){

                int pick = picking(x, y, 5,5);
                if( pick != 0){
                    if( posSelecionado >= 0){
                        objsVector[posSelecionado] -> selected = false;
                    }

                    if( pick-1 == posSelecionado ){
                        objsVector[posSelecionado] -> selected = false;
                        posSelecionado = -1;
                    } else {
                        posSelecionado = pick -1;
                        objsVector[posSelecionado]->selected = true;
                    }

                    glutGUI::lbpressed = false;
                }
            }

        } else {
            glutGUI::lbpressed = false;
        }
    }

    if( button == GLUT_MIDDLE_BUTTON ){
        if( state == GLUT_DOWN ){
            glutGUI::mbpressed = true;
        } else {
            glutGUI::mbpressed = false;
        }
    }

    if( button == GLUT_RIGHT_BUTTON ){
        if( state == GLUT_DOWN ){
            glutGUI::rbpressed = true;
        } else {
            glutGUI::rbpressed = false;
        }
    }

    glutGUI::last_x = x;
    glutGUI::last_y = y;
}

//-------------------mouse button------------------

void init_cenario() {
    //inicializando
    GUI::displayInit();
    loadBasicScenario();

    //GUI::drawOrigin(0.5);   //desenha origem do cenário ao centro

    GUI::setLight( 1, 0.5, 4.5, 1.5, true, false, false, false,pontLight,spotLight);
    GUI::setColor( 0.85, 0.755, 0.18, 1, true);

    GUI::drawFloor(12.2,10.2,0.9);






    for( int i=0; i<objsVectorSize; i++){
        glPushMatrix();
        objsVector[i]->desenha();
        glPopMatrix();
    }

    // ------ Sombreamento------

    if( drawShadow ){
        bool tempAux_Eixos = glutGUI::draw_eixos;

        glutGUI::draw_eixos = false;
        GLfloat sombra[4][4];

        float glProjPosX = 0.8 + glutGUI::lx, glProjPosY = 3.5 + glutGUI::ly, glProjPosZ = 1.6 + glutGUI::lz;
           // x 0.8 lightPos correction     | y 3.5 lightPos correction     | z 1.6 lightPos correction

        bool boundariesFloorLR = glProjPosX < 6.35333 && glProjPosX > -5.75333;
        //bool boundariesFloorFB_Z =


        Vetor3D p_light = Vetor3D( static_cast<GLfloat>(glutGUI::lx) + 0.35,
                                   static_cast<GLfloat>(glutGUI::ly) + 4.5,
                                   static_cast<GLfloat>(glutGUI::lz) + 1.5);
        Vetor3D p_obj = Vetor3D();

//        cout << p_light.x << " x-pos light / "
//             << p_light.y << " y-pos light / "
//             << p_light.z << " z-pos light;\n";

        float lightPos[4] = {glProjPosX, glProjPosY, glProjPosZ, static_cast<float>(pontLight) };
        glColor3d(0.0, 0.0, 0.0);
//        glColor4d(0.0, 0.0, 0.0, 0.85);

        glDisable(GL_LIGHTING);
        for( int i = 0; i < objsVectorSize; ++i ){
            bool tempSelectAux = objsVector[i]->selected;
            objsVector[i]->selected = false;

            p_obj.x = objsVector[i]->trans.x;
            p_obj.y = objsVector[i]->trans.y;
            p_obj.z = objsVector[i]->trans.z;

            Vetor3D vet_AB = Vetor3D(p_obj.x - p_light.x , p_obj.y - p_light.y , p_obj.z - p_light.z );
            GLfloat comp_AB = sqrt( (vet_AB.x * vet_AB.x) + (vet_AB.y * vet_AB.y)  + (vet_AB.z * vet_AB.z) );


            // sombra parede a esquerda
            bool hab_leftWall = false;
            if ( comp_AB > 3.30 && (p_obj.x < -1.5 && p_obj.x > -6) ){
                hab_leftWall = true;
            }
            // sombra parede a direita
            bool hab_rightWall = false;
            if ( comp_AB > 3.30 && (p_obj.x < 6 && p_obj.x > 1.5) ){
                hab_rightWall = true;
            }

            //sombra no chão

            if( boundariesFloorLR ){
                glPushMatrix();
                    GUI::shadowMatrixYk(sombra, lightPos, k_shadow);
                    glMultTransposeMatrixf((GLfloat*)sombra );
                    objsVector[i]->desenha();
                glPopMatrix();
            }
            //sombra parede esquerda

            if( boundariesFloorLR && hab_leftWall ){
                glPushMatrix();
                    GLfloat planoLeft[4] = {1,0,0, 5.9881};
                    GUI::shadowMatrix(sombra, planoLeft, lightPos);
                    glMultTransposeMatrixf((GLfloat*)sombra);
                    objsVector[i]->desenha();
                glPopMatrix();
            }
            //sombra parede direita

            if( boundariesFloorLR && hab_rightWall ){
                glPushMatrix();
                    GLfloat planoRight[4] = {-1,0,0, 5.9881 };
                    GUI::shadowMatrix(sombra, planoRight, lightPos);
                    glMultTransposeMatrixf((GLfloat*)sombra);
                    objsVector[i]->desenha();
                glPopMatrix();
            }
            //sombra parede fundo

            if(boundariesFloorLR ){
                glPushMatrix();
                    GLfloat planoBack[4] = {0,1,1, 5 + k_shadow};
                    GUI::shadowMatrix(sombra, planoBack, lightPos);
                    glMultTransposeMatrixf((GLfloat*)sombra );
                    objsVector[i]->desenha();
                glPopMatrix();
            }

            p_obj.x = 0; p_obj.y = 0; p_obj.z = 0;
            objsVector[i]->selected = tempSelectAux;
        }

        glutGUI::draw_eixos = tempAux_Eixos;
        glEnable(GL_LIGHTING);
    }


    if( enable_pick ){
        if( posSelecionado >= 0 && posSelecionado < objsVectorSize ){
            if( glutGUI::enable_translate ){    //enable translate com pick
                objsVector[posSelecionado]->trans.x += 0.6*glutGUI::dtx;
                objsVector[posSelecionado]->trans.y += 0.6*glutGUI::dty;
                objsVector[posSelecionado]->trans.z += 0.6*glutGUI::dtz;
            }
        }
    } else {
        if( posSelecionado >= 0 && posSelecionado < objsVectorSize){
            if( glutGUI::enable_translate ){    //enable_translate
                objsVector[posSelecionado]->trans.x += glutGUI::dtx;
                objsVector[posSelecionado]->trans.y += glutGUI::dty;
                objsVector[posSelecionado]->trans.z += glutGUI::dtz;
            }
            if( glutGUI::enable_rotate ){       //enable_rotate
                objsVector[posSelecionado]->rotat.x += glutGUI::dax;
                objsVector[posSelecionado]->rotat.y += glutGUI::day;
                objsVector[posSelecionado]->rotat.z += glutGUI::daz;
            }
            if( glutGUI::enable_scale ){        //enable_scale
                objsVector[posSelecionado]->scale.x += glutGUI::dsx;
                objsVector[posSelecionado]->scale.y += glutGUI::dsy;
                objsVector[posSelecionado]->scale.z += glutGUI::dsz;
            }
            if( glutGUI::enable_shear ){        //enable shear
                objsVector[posSelecionado]->shear.x += glutGUI::dtx;
                objsVector[posSelecionado]->shear.y += glutGUI::dty;
                objsVector[posSelecionado]->shear.z += glutGUI::dtz;
            }
        }
    }

    GUI::displayEnd();
}


void loadObjsListFromFile(){    // carregando objetos e suas caracterísitcas do arquivo
    ifstream baseFile;
    baseFile.open("../baseSaves.txt");

    if( !baseFile ){
        cout << " - ERRO ao carregar aquivo baseSaves.txt" << endl;
        exit(1);

    } else {
        string line;
        getline(baseFile, line);
        cout << line << " Objetos salvos a carregar;" <<endl <<endl;

        int n_objetos = stoi( line );

        int kind;
        double tx = 0, ty = 0, tz = 0;  //responsável pela translação
        double rx = 0, ry = 0, rz = 0;  //responsável pelas rotações
        double sx = 0, sy = 0, sz = 0;  //responsável pela escala

        for( int i = 0; i < n_objetos; i++){
            kind = 0;
            //cout << "objeto " << i + 1 << endl;
            getline( baseFile, line );

            kind = stoi( line );

            getline( baseFile, line );  tx = stod( line );
            getline( baseFile, line );  ty = stod( line );
            getline( baseFile, line );  tz = stod( line );

            getline( baseFile, line );  rx = stod( line );
            getline( baseFile, line );  ry = stod( line );
            getline( baseFile, line );  rz = stod( line );

            getline( baseFile, line );  sx = stod( line );
            getline( baseFile, line );  sy = stod( line );
            getline( baseFile, line );  sz = stod( line );

            Vetor3D ts = Vetor3D( tx, ty, tz );
            Vetor3D rt = Vetor3D( rx, ry, rz );
            Vetor3D sc = Vetor3D( sx, sy, sz );


            if        (kind == 1 ){
                objsVector.push_back( new Carro( ts, rt, sc ) );
                objsVectorSize++;

            } else if (kind == 2 ){
                objsVector.push_back( new  Casa( ts, rt, sc ) );
                objsVectorSize++;

            } else if (kind == 3 ){
                objsVector.push_back( new Cow( ts, rt, sc ) );
                objsVectorSize++;

            } else if (kind == 4 ){
                objsVector.push_back( new Reservatory( ts, rt, sc ) );
                objsVectorSize++;

            } else if (kind == 5 ){
                objsVector.push_back( new Pinheiro( ts, rt, sc ));
                objsVectorSize++;
            }
        }

        baseFile.close();
        cout << "Todos os objetos carregados;\n";

//        objsVector.push_back( new Pinheiro( Vetor3D(1.96667,0.0285715,-1.96667),
//                                            Vetor3D(0,0,0),
//                                            Vetor3D(0.400001,0.400001,0.400001))  );
//        objsVectorSize++;

    }

}


void saveObjsListToFile(){      //guardando objetos e suas caracterísitcas em arquivo
    ofstream baseFile;
    baseFile.open("../baseSaves.txt");
    baseFile.clear();
    if( objsVectorSize > 0  ){

        int vect_size = objsVector.size();
        baseFile << vect_size << "\n";
        for( int i = 0; i< vect_size; i++){
            baseFile << objsVector[i]->kind    << "\n";
            baseFile << objsVector[i]->trans.x << "\n";
            baseFile << objsVector[i]->trans.y << "\n";
            baseFile << objsVector[i]->trans.z << "\n";

            baseFile << objsVector[i]->rotat.x << "\n";
            baseFile << objsVector[i]->rotat.y << "\n";
            baseFile << objsVector[i]->rotat.z << "\n";

            baseFile << objsVector[i]->scale.x << "\n";
            baseFile << objsVector[i]->scale.y << "\n";
            baseFile << objsVector[i]->scale.z << "\n";
        }

    }
    if( objsVectorSize == 0 ){
        baseFile << objsVectorSize << "\n";
    }
    baseFile.close();
    cout << "Objetos guardados;\n";
}


    // Navegando nos objetos do objects_vector
void nextObj(){

    if(objsVectorSize > 0){
        if( posSelecionado >= 0 && posSelecionado < objsVectorSize ){
            objsVector[posSelecionado]->selected = false;
//            objectsVector[posSelecionado].updateSelection();
        }

        posSelecionado++;

        posSelecionado = posSelecionado % objsVectorSize;
        if( posSelecionado >= 0 && posSelecionado < objsVectorSize ){
            objsVector[posSelecionado]->selected = true;
        }

    }
}


void previousObj(){

    //int vect_size = objectsVector.size();

    if(objsVectorSize > 0){
        if( posSelecionado >= 0 && posSelecionado < objsVectorSize ){
            objsVector[posSelecionado]->selected = false;
        }
        posSelecionado--;

        if( posSelecionado < 0){
            posSelecionado = objsVectorSize - 1;
        }

        if( posSelecionado >= 0 && posSelecionado < objsVectorSize ){
            objsVector[posSelecionado]->selected = true;
        }
    }
};


    // Alterando caracterísitcas dos objetos do
void checkTransformations(){
    if(objsVectorSize > 0 && posSelecionado >= 0){
        glutGUI::enable_translate   = false;
        glutGUI::enable_rotate      = false;
        glutGUI::enable_scale       = false;
        glutGUI::enable_shear       = false;
        glutGUI::trans_obj = !glutGUI::trans_obj;
    }
}


void reflectSelectedObj(){  //aplicando reflexão do objeto selecionado
    if(objsVectorSize > 0 && posSelecionado >= 0){
        objsVector[posSelecionado]->reflect = !objsVector[posSelecionado]->reflect;
    }
}


void unmarkSelection(){

    //int vect_size = objsVector.size();

    if( posSelecionado >= 0 && posSelecionado < objsVectorSize ){
        objsVector[posSelecionado]->selected = false;
    }
    glutGUI::enable_translate = false;
    glutGUI::enable_rotate = false;
    glutGUI::enable_scale = false;
    glutGUI::enable_shear = false;
    glutGUI::trans_obj = false;

}


void drawObjectOrigin(){    //desenhando a Origem do objeto
    if( posSelecionado  >= 0 && posSelecionado < objsVectorSize ){
        objsVector[posSelecionado]->origin = !objsVector[posSelecionado]->origin;
    }
}


void deleteSelectedObj(){   // deletando objeto selecionado
    if( glutGUI::trans_obj )
        glutGUI::trans_obj = false;

    if( posSelecionado >= 0 && posSelecionado < objsVectorSize ){
        objsVector.erase(objsVector.begin() + posSelecionado );
        objsVectorSize--;
    }
}


void deleteLastObj(){
    if( objsVectorSize > 0 ){
        objsVector.pop_back();
        objsVectorSize--;
    }
    if( objsVectorSize <= 0 ){
        if( glutGUI::trans_obj )
            glutGUI::trans_obj = false;
    }
}




void teclado(unsigned char key, int x, int y) {
    GUI::keyInit(key,x,y);


    switch (key) {
    case 'l':   //translante fonte de luz
        if(glutGUI::enable_translate){
            glutGUI::enable_translate = false;
        }
        if(glutGUI::enable_scale){
            glutGUI::enable_scale = false;
        }
        if(glutGUI::enable_rotate){
            glutGUI::enable_rotate = false;
        }
        if(glutGUI::enable_shear){
            glutGUI::enable_shear = false;
        }
        glutGUI::trans_luz = !glutGUI::trans_luz;
        break;

    //----------------sombra
    case 'W':
        drawShadow = !drawShadow;
        break;

    //----------------transformações
    case 't':
        checkTransformations();
        break;

    case 'h':        //TRANSLATE
        if(glutGUI::trans_obj && !glutGUI::trans_luz){
            glutGUI::enable_translate = !glutGUI::enable_translate;
            glutGUI::enable_scale     = false;
            glutGUI::enable_rotate    = false;
            glutGUI::enable_shear     = false;
        }
        break;

    case 'j':        //ROTATE
        if(glutGUI::trans_obj && !glutGUI::trans_luz){
            glutGUI::enable_rotate    = !glutGUI::enable_rotate;
            glutGUI::enable_scale     = false;
            glutGUI::enable_translate = false;
            glutGUI::enable_shear     = false;
        }
        break;

    case 'k':        //SCALE
        if(glutGUI::trans_obj && !glutGUI::trans_luz){
            glutGUI::enable_scale     = !glutGUI::enable_scale;
            glutGUI::enable_translate = false;
            glutGUI::enable_rotate    = false;
            glutGUI::enable_shear     = false;
        }
        break;

    case 'u':       //SHEAR from object
        if(glutGUI::trans_obj && !glutGUI::trans_luz ){
            glutGUI::enable_shear     = !glutGUI::enable_shear;
            glutGUI::enable_scale     = false;
            glutGUI::enable_translate = false;
            glutGUI::enable_rotate    = false;
        }
        break;

    case 'i':
        if(glutGUI::trans_obj && !glutGUI::trans_luz){
            reflectSelectedObj();
        }
        break;

    case 'm':
        glutGUI::mouse_lock = MouseLock( (int(glutGUI::mouse_lock) + 1)  % 3);
        break;

    case ',':
        previousObj();
        break;
    case '.':
        nextObj();
        break;
    case ':':
        unmarkSelection();
        break;
    case '*':
        drawObjectOrigin();
        break;
    case ']':
        deleteSelectedObj();
        break;
    case '}':
        deleteLastObj();
        break;
    case 'P':
        enable_pick = !enable_pick;
        if(enable_pick){
            cout << "Pick enabled; enable_pick: " << enable_pick << "\n";
        } else {
            cout << "Pick disabled; enable_pick: " << enable_pick << "\n";
        }
        break;

    case '+':
        if( incluir_objeto ){
            cout << "include cancelado\n";
            incluir_objeto = !incluir_objeto;
        }else{
            cout << "include ativado\n";
            incluir_objeto = !incluir_objeto;
        }
        break;
    case 'S':
        saveObjsListToFile();
        break;


    //Definindo teclas para instanciar Objetos()
    case '!':
        if( incluir_objeto ){       //Carro, objeto do tipo 1
            objsVector.push_back( new Carro( ) );
            objsVectorSize++;
            incluir_objeto = !incluir_objeto;

        } else if( pontLight ){
            pontLight = !pontLight;
            spotLight = !spotLight;
        } else if( spotLight ){
            spotLight = !spotLight;
            pontLight = !pontLight;
        }
        break;

    case '@':
        if( incluir_objeto ){       //Casa, objeto do tipo 2
            objsVector.push_back( new Casa( ) );
            objsVectorSize++;
            incluir_objeto = !incluir_objeto;
        }
        break;

    case '#':
        if( incluir_objeto ){       //Vaquinha, objeto do tipo 3
            objsVector.push_back( new Cow( ) );
            objsVectorSize++;
            incluir_objeto = !incluir_objeto;
        }
        break;

    case '$':
        if( incluir_objeto ){       //Reservatorio, objeto do tipo 4
            objsVector.push_back( new Reservatory( ) );
            objsVectorSize++;
            incluir_objeto = !incluir_objeto;
        }
        break;


        //mudança na projeção
    case 'o':
//        if( glutGUI::perspective )
//          glutGUI::perspective = false;   //projeção ortogonal
        glutGUI::ortho = !glutGUI::ortho;
                //        glutGUI::perspective = false;
                //        glutGUI::ortho = true;
                //        cam = new CameraDistante(6,2,4, 0,0,0, 0,1,0);
                //        cout << ("cam: 9; perspective false; ortho true \n");
                //        break;
        break;
    case 'p':
//        if( glutGUI::ortho )
//            glutGUI::ortho = false;         //projeção perspectiva
        glutGUI::ortho = !glutGUI::ortho;
        glutGUI::perspective = !glutGUI::perspective;
        break;

    case '3':{
        glutGUI::cam = new CameraJogo(0.2,4,-17,  0,0,2.7,  0,1,0); //-10,10,-20,  2,0,0,  0,1,0
        break;
        }
    case '4':{
        glutGUI::cam = new CameraJogo(5,8,-18,  -1,-3,2,  0.4,1,0);  //5,3,-18,  0,1,8,  0.3,1,
        break;
        }
    case '5':{
        glutGUI::cam = new CameraDistante(8,19,21,  1,1,3,  0,1,0);  //8,19,21,  1,1,3,  0,1,0
        break;
        }
    case '6':{
        glutGUI::cam = new CameraDistante(-7,3,14,  5.5,-1,-8.5,  0,1,0);  //-7,3,14,  5.5,-1,-8.5,  0,1,0
        break;
        }


    // resolvendo assuntos da Janela de Renderização
    case 'Q':
        exit(0);
        break;
    case 'F':
        if( !isFullScreen ){
            glutFullScreen();
            isFullScreen = true;
            break;
        }else{
            glutReshapeWindow(windWidth, windHeight);
            isFullScreen = false;
            break;
        }

    default:
        break;
    }
}




int main(){

    cout << "Bem Vindo! A seguir, um guia dos comandos:\n" << endl;
    cout << "Selecionar o objeto anterior: ( , )" << endl;
    cout << "Selecionar o próximo objeto: ( . )" << endl;
    cout << "Desmarcar objeto selecionado: ( : )" <<endl << endl;
    cout << "Realizar transformações no objeto selecionado: ( t )" <<endl;
    cout << "Desenhar eixo do sistema local do objeto: ( * )" <<endl << endl;
    cout << "Incluir novo objeto no cenário: ( + )" << endl;
    cout << "A lista de objetos vai de 1 a 4 (não numerico) + SHIFT" << endl << endl;
    cout << "Eleminar objeto quando selecioando: ( ] )" << endl;
    cout << "Eliminar o ultimo objeto do vetor: ( } )" <<endl;
    cout << "Guardar a atual lista de objetos em arquivo: ( S + SHIFT )" << endl << endl;
    cout << "Alternar entre as câmera: ( 3 .. 6)" <<endl;
    cout << "Resetar para câmera dafult: ( c )" <<endl;

    cout << endl;


    loadObjsListFromFile();

    GUI gui = GUI(windWidth, windHeight, init_cenario, teclado, mouseButtonMain, "CG - 2024.2");
}






















//adicionar:
//-deslocar cubo com o teclado
//-deslocar cubo com o mouse
//-primitivas OpenGL (glBegin, glEnd)
//-glNormal, iluminação

//-leitor 3DS
//-usar as transformacoes matriciais do proprio OpenGL
//-push/popMatrix (podem ser usados um dentro do outro - nocao de pilha)

//-ordem das transformacoes
//  -translacao e rotacao
//  -testar escala!!!
//-interpretacao de uma composicao de transformacoes já definida
//      <----------- globais
//  -   T.Rz.Ry.Rx.S . v
//      -----------> locais
//  -direita->esquerda: Transfs globais
//  -esquerda->direita: Transfs locais
