#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <gui.h>

class MyObject{

public:
    Vetor3D t = Vetor3D(0, 0, 0);
    Vetor3D a = Vetor3D(0, 0, 0);
    Vetor3D s = Vetor3D(1, 1, 1);

    /*
     *   se objeto carro.3DS: 1
     *   se objeto cow.3Ds: 2
     *   se objeto pre-modelado: 3
     */
    int tipo;
    bool origem = true;
    bool selected = false;

    MyObject( int t );
    virtual void desenha();
};

#endif // MYOBJECT_H
