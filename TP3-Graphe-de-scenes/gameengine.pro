QT       += core gui widgets

TARGET = gameengine
TEMPLATE = app

SOURCES += main.cpp \
    gameobject.cpp \
    transform.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    camera.h \
    gameobject.h \
    mainwidget.h \
    geometryengine.h \
    transform.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[YOUR_PATH]
INSTALLS += target
