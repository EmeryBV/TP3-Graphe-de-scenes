#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QMatrix4x4>
class Camera{

private:


public:

    QVector3D cameraPosition;
    QVector3D cameraTarget;

    QVector3D cameraDirection;
    QVector3D cameraUp;
    QVector3D cameraRight;
    Camera(){
    }

    Camera(QVector3D cameraPosition, QVector3D cameraTarget){
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;


        this->cameraDirection = (cameraPosition - cameraTarget).normalized();
        this->cameraRight = QVector3D::crossProduct( QVector3D(0.,1.,0.) ,this->cameraDirection).normalized();
        this->cameraUp = QVector3D::crossProduct( this->cameraDirection, this->cameraRight );
        cameraDirection = (cameraPosition - cameraTarget).normalized();

    }

    QMatrix4x4 getViewMatrix(){
        QMatrix4x4 view;

        view.lookAt(this->cameraPosition, this->cameraTarget, this->cameraUp);
        return view;
    }

};

#endif // CAMERA_H
