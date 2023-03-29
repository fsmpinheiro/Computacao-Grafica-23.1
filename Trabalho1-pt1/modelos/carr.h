#ifndef CARR_H
#define CARR_H

#include "myobject.h"


class Carr : public MyObject{

public:
    Model3DS * carrModel;

    Carr();
    Carr( Vetor3D tn, Vetor3D an, Vetor3D sn );
    ~Carr();

    void desenha( );
};

#endif // CARR_H
