/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwidget.h"
#include "gameobject.h"

#include <QMouseEvent>
#include <iostream>
#include <math.h>
#include <QElapsedTimer>
#include <QApplication>



bool rotate = false;
 GameObject world;
 GameObject child;
MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometries(0),
    heightMap(0),
    angularSpeed(0)
{
}


MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete heightMap;

    delete textureGrass;
    delete textureRock;
    delete textureSnow;


    delete geometries;
    doneCurrent();
}

//! [0]
void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}
//! [0]


//! [1]
void MainWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
        update();
    }

}
//! [1]

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

   glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
// glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
    // Enable back face culling
//    glEnable(GL_CULL_FACE);
//! [2]

    geometries = new GeometryEngine;

    // Use QBasicTimer because its faster than QTimer
}

//! [3]
void MainWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
//! [3]

//! [4]
void MainWidget::initTextures()
{
    // Load cube.png image
    heightMap = new QOpenGLTexture(QImage(":/Heightmap_Rocky.png").mirrored());
    textureGrass =new QOpenGLTexture(QImage(":/grass.png").mirrored());
    textureRock =new QOpenGLTexture(QImage(":/rock.png").mirrored());
    textureSnow =new QOpenGLTexture(QImage(":/snowrocks.png").mirrored());



    // Set nearest filtering mode for texture minification
    heightMap->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    heightMap->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    heightMap->setWrapMode(QOpenGLTexture::Repeat);


    textureGrass->setMinificationFilter(QOpenGLTexture::Nearest);
    textureGrass->setMagnificationFilter(QOpenGLTexture::Linear);
    textureGrass->setWrapMode(QOpenGLTexture::Repeat);

    textureRock->setMinificationFilter(QOpenGLTexture::Nearest);
    textureRock->setMagnificationFilter(QOpenGLTexture::Linear);
    textureRock->setWrapMode(QOpenGLTexture::Repeat);

    textureSnow->setMinificationFilter(QOpenGLTexture::Nearest);
    textureSnow->setMagnificationFilter(QOpenGLTexture::Linear);
    textureSnow->setWrapMode(QOpenGLTexture::Repeat);

}
//! [4]

//! [5]
void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 0.001, zFar = 1500.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void MainWidget::keyPressEvent(QKeyEvent *event)
{

    float amplitude = 0.25;

    switch (event->key()) {
        case Qt::Key_Right:
            cameraPos[0]+=amplitude;
            update();
            break;
        case Qt::Key_Left:
            cameraPos[0]-=amplitude;
            update();
            break;
        case Qt::Key_Up:
           cameraPos[2]+=amplitude;
           update();
          break;
        case Qt::Key_Down:
            cameraPos[2]-=amplitude;
            update();
            break;

        case Qt::Key_R:
        {
            if(rotate == false)rotate = true;
            else rotate = false;
//            qDebug("%i", rotate);
            break;

         }
    }


update();
}


void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    heightMap->bind(0);
    textureGrass->bind(1);
    textureRock->bind(2);
    textureSnow->bind(3);
//! [6]
    // Calculate model view transformation
    std::vector< QVector3D> vertices;
    std::vector< std::vector< unsigned int >> faces;

    QString filepath =  "../TP3-Graphe-de-scenes/sphere.off";



    QMatrix4x4 matrix;
    QMatrix4x4 matrix2;
    matrix.rotate(rotation2);


    Camera camera =  Camera(cameraPos,cameraFront);
    view = camera.getViewMatrix();

    world =  GameObject(matrix,geometries,&program,projection,view);

    GameObject &Sun = world.addChild();
    Sun.importMesh(filepath);
    Sun.rotateAround(0.055,0.0,1.0,0.0);

    GameObject &Earth = Sun.addChild();
    Earth.importMesh(filepath);
    Earth.Translate(2.0,0.0,0.0);
    Earth.Rotate(23.44,'y');
    Earth.Scale(0.6783/4);

    GameObject &Moon = Earth.addChild();
    Moon.importMesh(filepath);
    Moon.Translate(-2.0,0.0,0.0);
    Moon.rotateAround(0.055,0.0,1.0,1.0);
    Moon.Translate(2.0,0.0,0.0);
    Moon.Scale(0.1738);


    world.draw();
    update();

//    world.rotateObject(0.1*(float)chrono.currentTime().second());

//    QVector3D translationTest = QVector3D(1.0,0.0,0.0);
//    world.getTransform().Translate(translationTest);
//    world.applyTransform();



//    qDebug("%f ", world.getTransform().getTranslate()[0] );


//    world.assignTexture((char *)"texture", 0);
//    world.assignTexture((char *)"textureGrass", 1);
//    world.assignTexture((char *)"textureRock", 2);
//    world.assignTexture((char *)"textureSnow", 3);



//! [6]
    // Use texture unit 0 which contains cube.png

//    program.setUniformValue("texture", 0);
//    program.setUniformValue("textureGrass", 1);
//     program.setUniformValue("textureRock", 2);
//      program.setUniformValue("textureSnow", 3);
    // Draw cube geometry
//    world.draw();
}



