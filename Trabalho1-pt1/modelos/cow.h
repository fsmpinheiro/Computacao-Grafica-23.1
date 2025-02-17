#ifndef COW_H
#define COW_H

#include "myobject.h"

class Cow : public MyObject {

public:
    Model3DS * model;

    Cow( );
    Cow(Vetor3D tn, Vetor3D rn, Vetor3D sn);

    ~Cow( );

    void desenha();
    void updateSelection();
    void unSelect();
};

#endif // COW_H
