#ifndef Transform_H
#define Transform_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include "camera.h"
#include <QTime>

class Transform
{


    QQuaternion rotation ; // rotation
    QVector3D position;    // translation
    float scale;    // scaling


public:

    Transform();
    Transform(QQuaternion &R  , float &scale, QVector3D &translation );

public:

    QVector3D applyToPoint(QVector3D p);

    QVector3D applyToVector(QVector3D v);
    void applyToModel(QMatrix4x4 &model);
    QVector3D &getTransform();

    QVector3D getTranslate();
    float getScale();
    QQuaternion getRotation() ;

    void Translate(QVector3D translation);
    void Translate(float x, float y , float z );
    void Rotate(QQuaternion rotation);
    void Scale(float scale);

    //    const QMatrix4x4 &getRotation() const;

};

#endif // Transform_H
