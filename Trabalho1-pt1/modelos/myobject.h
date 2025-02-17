#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <gui.h>

class MyObject{

public:
    Vetor3D trans = Vetor3D(0, 0, 0);
    Vetor3D rotat = Vetor3D(0, 0, 0);
    Vetor3D scale = Vetor3D(1, 1, 1);
    Vetor3D shear = Vetor3D(0, 0, 0);

    int kind;
    bool origin = false;
    bool selected = false;
    bool reflect = false;
    //bool shear = false;

public:
    MyObject( int k );
    virtual void desenha();

};

#endif // MYOBJECT_H
