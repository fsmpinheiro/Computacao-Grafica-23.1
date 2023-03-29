#ifndef RESERVATORY_H
#define RESERVATORY_H

#include "myobject.h"


class Reservatory : public MyObject{

public:

    Reservatory( );
    Reservatory( Vetor3D tn, Vetor3D an, Vetor3D sn );
    ~Reservatory( );

    void desenha( );
};

#endif // RESERVATORY_H
