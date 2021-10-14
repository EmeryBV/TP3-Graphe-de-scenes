#include "gameobject.h"



GameObject::GameObject()
{
    this->model = QMatrix4x4();
    this->transform = Transform();
}

GameObject::GameObject(QMatrix4x4 &model, GeometryEngine *geometry, QOpenGLShaderProgram *program, QMatrix4x4 projection,  QMatrix4x4 view )
{
    if(!instanciate)    {
        this->model = model;
        this->transform = Transform();
        this->geometry = geometry;
        this->program = program;
        this->projection = projection;
        this->view = view;
    }
}

bool GameObject::isInstanciate(){
    return this->instanciate;
}

QMatrix4x4 GameObject::getObject(){
    return this->model;
}

GameObject& GameObject::addChild(){
    GameObject child = GameObject(model,geometry,program,this->projection,this->view);
    child.transform = this->transform;
    this->childList.push_back(child);
    return childList[childList.size()-1];
}

 std::vector<GameObject> &GameObject::getChildList()
{
    return childList;
}

Transform &GameObject::getTransform(){
    return this->transform;
}


void GameObject::Translate(QVector3D translation){
    getTransform().Translate(translation);
    this->model.translate(getTransform().getTranslate());
}

void GameObject::Translate(float x, float y , float z ){
    getTransform().Translate(x,y,z);
    this->model.translate(getTransform().getTranslate());
}

void GameObject::Rotate(QQuaternion rotation){
    getTransform().Rotate(rotation);
    this->model.rotate(getTransform().getRotation());
}
void GameObject::Scale(float scale){
    getTransform().Scale(scale);
    this->model.scale(scale);
}

void GameObject::applyTransform(){
    this->transform.applyToModel(this->model);
}

void GameObject::assignTexture(char* value, int idx){
    program->setUniformValue(value,idx);
}

void GameObject::rotateObject (float angle ){
    this->getTransform().Translate(QVector3D(angle,0.0,0.0));
}

void GameObject::rotateAroundHimSelf(){
        long time = 0 ;
        time = chrono.currentTime().msecsSinceStartOfDay();
        float amplitude = 0.055f * time ;
        QQuaternion rotation = QQuaternion::fromAxisAndAngle(QVector3D(0.0,1.0,0.0), amplitude);
         this->Rotate(rotation);

        this->applyTransform();

}



void GameObject::draw(){

     this->geometry->drawCubeGeometry(this->program);
//    qDebug("%i ", childList.size() );
    program->setUniformValue("mvp_matrix",  projection *view * this->getObject());

    for (GameObject child:  this->childList) {
//        qDebug("%f La ", child.getTransform().getTranslate()[0] );
        child.draw();
    }


}
