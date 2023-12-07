#ifndef DYNAMICSPRITELINESTRIPPLANERENDERER_H
#define DYNAMICSPRITELINESTRIPPLANERENDERER_H

#include <QOpenGLExtraFunctions>
#include <QVector3D>

#include "Basics/shader.h"
#include "Basics/camera.h"

class DynamicSpriteLineStripPlaneRenderer:QOpenGLExtraFunctions
{
public:
    DynamicSpriteLineStripPlaneRenderer();

public:
    QVector3D Color;
    DynamicSpriteLineStripPlaneRenderer(const Shader& shader,QVector3D color=QVector3D(1.0,1.0,1.0));
    ~DynamicSpriteLineStripPlaneRenderer();
    void UpdateData(const vector<float>& data);
    void Draw(QVector3D position,QVector3D size,Camera camera,QMatrix4x4 projection);
private:
    vector<float> Vertexs;
    bool Changed;
    int Size;
    Shader shader;
    GLuint VAO,VBO;
    void initRenderData();
};

#endif // DYNAMICSPRITELINESTRIPPLANERENDERER_H
