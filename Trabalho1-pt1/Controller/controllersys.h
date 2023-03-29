#ifndef CONTROLLERSYS_H
#define CONTROLLERSYS_H

#include <vector>
#include "../modelos/myobject.h"

class ControllerSys{
private:

    int posSelected = -1;
    bool includeObject = false;

    vector <MyObject*> objectsVector;

public:

    ControllerSys();
    ~ControllerSys();

    void loadFile();
    void saveFile();

    void prevObject();
    void nextObject();
    void insertObject( int tipo );

    void markUnMark();
    void drawObjectOrigin();

    void deleteSelected();
    void deleteLastObject();

    int getVectorSize( );
    MyObject* getByIndex( int index );
};

#endif // CONTROLLERSYS_H
