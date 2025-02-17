TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += bib
INCLUDEPATH += gui_glut
INCLUDEPATH += trab1

LIBS += -lGL -lGLU -lglut -l3ds -lSDL_image -lIL

SOURCES += main.cpp \
    bib/Camera.cpp \
    bib/CameraDistante.cpp \
    bib/CameraJogo.cpp \
    bib/Desenha.cpp \
    bib/model3ds.cpp \
    bib/Vetor3D.cpp \
    gui_glut/extra.cpp \
    gui_glut/gui.cpp \
    gui_glut/OpenTextures.cpp \
    modelos/myobject.cpp \
    modelos/reservatory.cpp \
    modelos/carro.cpp \
    modelos/casa.cpp \
    modelos/cow.cpp \
    modelos/pinheiro.cpp

HEADERS += \
    bib/Camera.h \
    bib/CameraDistante.h \
    bib/CameraJogo.h \
    bib/Desenha.h \
    bib/model3ds.h \
    bib/Vetor3D.h \
    gui_glut/extra.h \
    gui_glut/gui.h \
    gui_glut/OpenTextures.h \
    modelos/myobject.h \
    modelos/reservatory.h \
    modelos/carro.h \
    modelos/casa.h \
    modelos/cow.h \
    modelos/pinheiro.h
