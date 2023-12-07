#ifndef STATICSPRITEPOLYGONPLANERENDERER_H
#define STATICSPRITEPOLYGONPLANERENDERER_H

#include <QOpenGLExtraFunctions>

#include "Basics/shader.h"
#include "Basics/camera.h"

class staticSpritePolygonPlaneRenderer:QOpenGLExtraFunctions
{
public:
    QVector3D Color;
    staticSpritePolygonPlaneRenderer(const Shader& shader,const vector<QVector2D>& vertexs,QVector3D color=QVector3D(1.0,1.0,1.0));
    ~staticSpritePolygonPlaneRenderer();
    void Draw(QVector3D position,QVector3D size,Camera camera,QMatrix4x4 projection);
private:
    vector<float> Vertexs;
    GLuint VAO,VBO;
    int Size;
    Shader shader;
    void initRenderData();
};

#endif // STATICSPRITEPOLYGONPLANERENDERER_H
