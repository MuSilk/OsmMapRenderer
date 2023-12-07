#ifndef STATICSPRITEPRISMRENDERER_H
#define STATICSPRITEPRISMRENDERER_H

#include <QOpenGLExtraFunctions>

#include "Basics/shader.h"
#include "Basics/camera.h"

class staticSpritePrismRenderer:QOpenGLExtraFunctions
{
public:
    QVector3D TopColor,SideColor;
    staticSpritePrismRenderer(const Shader& shader,const vector<QVector2D>& vertexs,GLfloat height,QVector3D topcolor=QVector3D(1.0,1.0,1.0),QVector3D sidecolor=QVector3D(1.0,1.0,1.0));
    ~staticSpritePrismRenderer();
    void Draw(QVector3D position,QVector3D size,Camera camera,QMatrix4x4 projection,bool _3D=true);
private:
    vector<float> Vertexs[3];
    GLfloat Height;
    GLuint VAO[3],VBO[3];
    int Size;
    Shader shader;
    void initRenderData();
};

#endif // STATICSPRITEPRISMRENDERER_H
