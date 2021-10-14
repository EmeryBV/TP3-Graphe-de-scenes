#include "transform.h"



Transform::Transform() {
    rotation = QQuaternion();
    scale = 1.0;
    translate = QVector3D(0, 0, 0);
}

Transform::Transform(QQuaternion &rotation, float &scale, QVector3D &translation ) {
    this->rotation = rotation;
    this->scale = scale;
    this->translate = translation;
}


void Transform::applyToModel(QMatrix4x4 &model){

//       model.translate(this->translate);
        model.rotate(this->rotation);
        model.scale(this->scale);
        model.translate(this->translate);
}

void Transform::Translate(QVector3D t){
//     qDebug("%f ", translate[0] );
     this->translate+= t;
}


void Transform::Translate(float x , float y , float z ){

     this->translate+= QVector3D(x,y,z);
}
QVector3D Transform::getTranslate(){
    return this->translate;
}

QQuaternion Transform::getRotation(){
    return this->rotation;
}

float Transform::getScale(){
    return this->scale;
}


void Transform::Rotate(QQuaternion r){
     this->rotation = r;
}

void Transform::Scale(float scale){
     this->scale+= scale ;

}
