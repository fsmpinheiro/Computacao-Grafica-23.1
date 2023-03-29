//#include <iostream>
//#include <vector>
#include <fstream>
#include "controllersys.h"

#include "../modelos/carr.h"
#include "../modelos/house.h"
#include "../modelos/cow.h"
//#include "../modelos/myobject.h"

//using namespace std;

ControllerSys::ControllerSys( ){
    vector< MyObject* > temp;
    objectsVector = temp;
}

ControllerSys::~ControllerSys( ){
}


void ControllerSys::loadFile( ){
    ifstream basefile;
    basefile.open( "../sabedSaves.txt" );

    if(!basefile){
        cout << " - Erro ao carregar o arquivo sabedSaves.txt" << endl;

    } else {
        string line;
        getline(basefile, line);
        cout << line << " Objetos no vetor;" <<endl <<endl;

        int n_objects = stoi( line );

        int tipo = 0;
        double tx = 0, ty = 0, tz = 0; //Vetor 3D da translação salvo
        double ax = 0, ay = 0, az = 0; //Vetor 3D da rotação salvo
        double sx = 0, sy = 0, sz = 0; //Vetor 3D da escala salvo

        for( int i=0; i < n_objects; i++ ){
            getline( basefile, line );
            tipo = stoi( line );    //identificador do tipo de objeto

        //carregando a translação
            getline( basefile, line );
            tx = stoi(line);
            getline( basefile, line );
            ty = stoi(line);
            getline( basefile, line );
            tz = stoi(line);

        //carregando a rotação
            getline( basefile, line );
            ax = stoi(line);
            getline( basefile, line );
            ay = stoi(line);
            getline( basefile, line );
            az = stoi(line);

        //carregando a escala
            getline( basefile, line );
            sx = stoi(line);
            getline( basefile, line );
            sy = stoi(line);
            getline( basefile, line );
            sz = stoi(line);

            Vetor3D tn = Vetor3D(tx,ty,tz);
            Vetor3D an = Vetor3D(ax,ay,az);
            Vetor3D sn = Vetor3D(sx,sy,sz);

            if( tipo == 1 ){            //tipo refente ao objeto 3Ds
                objectsVector.push_back( new Carr( tn, an, sn ) );
            } else if ( tipo == 2 ){    //tipo referente ao objeto House
                objectsVector.push_back( new House( tn, an, sn ) );
            } else if ( tipo == 3 ){    //tipo referente ao objeto House
//                objectsVector.push_back( new MyObject( tn, an, sn) );
            }

        }

    }
    basefile.close( );
}

void ControllerSys::saveFile( ){
    ofstream baseFile;
    baseFile.open( "../baseSaves.txt");
    baseFile.clear();
    int sizeOfVector = objectsVector.size( );

        baseFile << objectsVector.size( ) << "\n";
    for (int i = 0; i < sizeOfVector; i++) {
        baseFile << objectsVector[ i ]->tipo << "\n";
        baseFile << objectsVector[ i ]->t.x << "\n";
        baseFile << objectsVector[ i ]->t.y << "\n";
        baseFile << objectsVector[ i ]->t.z << "\n";

        baseFile << objectsVector[ i ]->a.x << "\n";
        baseFile << objectsVector[ i ]->a.y << "\n";
        baseFile << objectsVector[ i ]->a.z << "\n";

        baseFile << objectsVector[ i ]->s.x << "\n";
        baseFile << objectsVector[ i ]->s.y << "\n";
        baseFile << objectsVector[ i ]->s.z << "\n";
    }

//    baseFile.write( );
}


void ControllerSys::prevObject( ){
    int vectSize = objectsVector.size();
    if( posSelected >= 0 && posSelected < vectSize ){
        objectsVector[posSelected]->selected = false;
    }
    posSelected--;
    if( posSelected < 0 ){
        posSelected = objectsVector.size( ) - 1;
    }
    if( posSelected >= 0 && posSelected < vectSize ){
        objectsVector[posSelected]->selected = true;
    }
}

void ControllerSys::nextObject( ){
    int vectSize = objectsVector.size();
    if( posSelected >= 0 && posSelected < vectSize ){
        objectsVector[posSelected]->selected = false;
    }

    posSelected++;
    posSelected = posSelected % objectsVector.size( );

    if( posSelected >= 0 && posSelected < vectSize ){
        objectsVector[posSelected]->selected = true;
    }
}

void ControllerSys::insertObject( int tipo ){

    if( tipo == 1 ){
        objectsVector.push_back( new  Carr( ) );
    }
    if( tipo == 2 ){
        objectsVector.push_back( new Cow( ) );
    }
    if( tipo == 3 ){
        objectsVector.push_back( new House( )   );
    }
}


void ControllerSys::markUnMark( ){
    if( posSelected >= 0 && posSelected < objectsVector.size( ) ){
        objectsVector[posSelected]->selected = false;
    }
    glutGUI::trans_obj == false;
}

void ControllerSys::drawObjectOrigin( ){
    if( posSelected >= 0 && posSelected < objectsVector.size( ) ){
        objectsVector[posSelected]->origem = !objectsVector[posSelected]->origem;
    }
}


void ControllerSys::deleteSelected( ){

}

void ControllerSys::deleteLastObject( ){

}

int ControllerSys::getVectorSize( ){
    int vSize = objectsVector.size( );
    return vSize;
}

MyObject* ControllerSys::getByIndex( int index ){
    return objectsVector[index];
}
