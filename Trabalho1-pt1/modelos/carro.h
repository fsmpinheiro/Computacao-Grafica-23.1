#ifndef CARRO_H
#define CARRO_H

#include "myobject.h"

class Carro : public MyObject{

public:
    Model3DS * model;

    Carro();
    Carro(Vetor3D tn, Vetor3D rn, Vetor3D sn);

    ~Carro();

    void desenha();
    void updateSelection();
    void unSelect();
};

#endif // CARRO_H
