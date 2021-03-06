QT       += core gui widgets

TARGET = gameengine
TEMPLATE = app

SOURCES += main.cpp \
    gameobject.cpp \
    mesh.cpp \
    transform.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    BasicIO.h \
    camera.h \
    gameobject.h \
    mainwidget.h \
    geometryengine.h \
    mesh.h \
    transform.h

RESOURCES += \
    mesh.qrc \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[YOUR_PATH]
INSTALLS += target

DISTFILES += \
    sphere.off
