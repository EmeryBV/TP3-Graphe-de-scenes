#include "mesh.h"

#include <iostream>

#include <QVector2D>
#include <QVector3D>


Mesh::Mesh(){
}

Mesh::Mesh(QString filepath,QOpenGLShaderProgram *program)
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();
    arrayBuf.create();
    indexBuf.create();
    OFFIO::open< QVector3D , unsigned short > (filepath.toStdString() , this->vertices, this->faces, true , false );
    this->program = program;

    // Initializes cube geometry and transfers it to VBOs
    initGeometry();

}

Mesh::~Mesh()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]

void Mesh::initGeometry()
{

    vertArray = new VertexData[vertices.size()];
    for (int var = 0; var < vertices.size(); ++var) {
        vertArray[var].position = vertices[var];
    }

    indArray = new GLushort[faces.size()*3];
    int count =0;
    for (int var = 0; var < faces.size(); var++) {
        for (int var2 = 0; var2 < 3; ++var2) {
            indArray[count++] = faces[var][var2];
        }
    }

    arrayBuf.bind();
    arrayBuf.allocate(vertArray, vertices.size() * sizeof( VertexData));

    indexBuf.bind();
    indexBuf.allocate(indArray,  count* sizeof(GLushort ));
}

//! [2]
void Mesh::inputMesh()
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    //    // Offset for texture coordinate
    //    offset += sizeof(QVector3D);

    //    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    //    int texcoordLocation = program->attributeLocation("a_texcoord");
    //    program->enableAttributeArray(texcoordLocation);
    //    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, faces.size()*3, GL_UNSIGNED_SHORT, 0); //Careful update indicesNumber when creating new geometry
}
//! [2]

