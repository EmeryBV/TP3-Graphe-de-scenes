#include "transform.h"



Transform::Transform() {
    rotation = QQuaternion();
    scale = 1.0;
    position = QVector3D(0, 0, 0);
}

Transform::Transform(QQuaternion &rotation, float &scale, QVector3D &translation ) {
    this->rotation = rotation;
    this->scale = scale;
    this->position = translation;
}


void Transform::applyToModel(QMatrix4x4 &model){

//       model.translate(this->translate);
        model.scale(this->scale);
        model.rotate(this->rotation);
        model.translate(this->position);
}

void Transform::Translate(QVector3D t){
//     qDebug("%f ", translate[0] );
     this->position+= t;
}


void Transform::Translate(float x , float y , float z ){

     this->position+= QVector3D(x,y,z);
}
QVector3D Transform::getTranslate(){
    return this->position;
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
