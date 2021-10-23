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
#include "mesh.h"
class GameObject
{


private:

    QMatrix4x4 model;
    std::vector<GameObject> childList;
    Transform transform;
    bool instanciate = false;
    GameObject *parent;
    QTime chrono ;
    float lastFrame;
    float currentFrame;
    Mesh *mesh ;
    bool meshImport=false;
    QVector4D color = QVector4D(1.0f,1.0f,1.0f,1.0f);

protected:

public:
    GameObject();
    ~GameObject();
    GameObject(QMatrix4x4 &matrix);
    bool isInstanciate();
    GameObject& addChild();

    QMatrix4x4 getObject();
    void rotateAround(float speed, float x , float y, float z ) ;

    QMatrix4x4 matrix;
    QMatrix4x4 matrix2;
    void Translate(QVector3D translation);
    void Translate(float x, float y , float z );
    void Rotate(QQuaternion rotation);
    void Rotate(float angle, char axe);
    void Scale(float scale);

    Transform &getTransform();
    void applyTransform();
    void draw( QOpenGLShaderProgram *program, QMatrix4x4 projection,  QMatrix4x4 view );
    void drawChild();
    void assignTexture(char *value, int idx);
    void rotateObject (float angle );
    void importMesh(QString filepath,QOpenGLShaderProgram *program);
    void renderMesh();
    void resetModel();
    void assignParentTrans();

    std::vector<GameObject> &getChildList() ;
    void setColor(float R, float G, float B, float alpha);
};



#endif // GameObject_H
