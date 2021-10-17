#ifndef MESH_H
#define MESH_H

#include <QOpenGLFunctions_3_1>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include "BasicIO.h"

class Mesh : protected QOpenGLFunctions_3_1
{

    struct VertexData
    {
        QVector3D position;
        QVector2D texCoord;
    };

private:
    void initGeometry();
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    std::vector< std::vector< unsigned int >> faces;
    std::vector< QVector3D> vertices;
    QOpenGLShaderProgram *program;
    VertexData* vertArray;
    GLushort* indArray;

public:
    Mesh();
    Mesh(QString filepath,QOpenGLShaderProgram *program);
    virtual ~Mesh();
    void inputMesh();




};

#endif
