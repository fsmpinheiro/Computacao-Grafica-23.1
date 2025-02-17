#ifndef PINHEIRO_H
#define PINHEIRO_H

# include "myobject.h"

class Pinheiro : public MyObject {

public:
    Pinheiro();
    Pinheiro( Vetor3D tn, Vetor3D rn, Vetor3D sn );

    ~Pinheiro();

    void desenha();
    void updateSelection();
    void unSelect();
};

#endif // PINHEIRO_H
