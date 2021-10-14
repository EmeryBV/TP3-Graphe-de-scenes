#ifndef GameObject_H
#define GameObject_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include "transform.h"
#include <QTime>
#include "geometryengine.h"
#include <QTime>

class GameObject
{


private:

    QMatrix4x4 model;
    std::vector<GameObject> childList;
    Transform transform;
    bool instanciate = false;
    GameObject *parent;

    GeometryEngine *geometry;
    QOpenGLShaderProgram *program;

    QMatrix4x4 projection;
    QMatrix4x4 view;
    QTime chrono ;

protected:

public:
    GameObject();
    GameObject(QMatrix4x4 &matrix, GeometryEngine *geometry, QOpenGLShaderProgram *program, QMatrix4x4 projection,  QMatrix4x4 view );
    bool isInstanciate();
    GameObject& addChild();

    QMatrix4x4 getObject();
    void rotateAroundHimSelf() ;


    void Translate(QVector3D translation);
    void Translate(float x, float y , float z );
    void Rotate(QQuaternion rotation);
    void Scale(float scale);

    Transform &getTransform();
    void applyTransform();
    void draw();
    void assignTexture(char *value, int idx);
    void rotateObject (float angle );

     std::vector<GameObject> &getChildList() ;
};



#endif // GameObject_H
