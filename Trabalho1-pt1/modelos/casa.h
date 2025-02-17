#ifndef CASA_H
#define CASA_H

#include "myobject.h"

class Casa : public MyObject {

public:
    Casa( );
    Casa( Vetor3D tn, Vetor3D rn, Vetor3D sn );

    ~Casa( );

    void desenha();
    void updateSelection();
    void unSelect();
};

#endif // CASA_H
