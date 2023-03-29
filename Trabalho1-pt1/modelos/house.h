#ifndef HOUSE_H
#define HOUSE_H

#include "myobject.h"


class House : public MyObject{


public:

    House();
    House( Vetor3D tn, Vetor3D an, Vetor3D sn );
    ~House();

    void desenha( );
};

#endif // HOUSE_H
