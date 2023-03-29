#ifndef COW_H
#define COW_H

#include "myobject.h"


class Cow : public MyObject{

public:
    Model3DS * cowModel;

    Cow( );
    Cow( Vetor3D tn, Vetor3D an, Vetor3D sn);
    ~Cow( );

    void desenha();
};

#endif // COW_H
