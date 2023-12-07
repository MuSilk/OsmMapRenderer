#ifndef SPRITECUBERENDERER_H
#define SPRITECUBERENDERER_H

#include <QOpenGLExtraFunctions>

#include "Basics/texture2d.h"
#include "Basics/shader.h"
#include "Basics/camera.h"

class SpriteCubeRenderer:QOpenGLExtraFunctions
{
public:
    SpriteCubeRenderer(Shader& shader);
    ~SpriteCubeRenderer();
    void Draw(Texture2D& texture,QVector3D position,QVector3D size,Camera camera,QMatrix4x4 projection,GLfloat alpha);
private:
    Shader shader;
    GLuint VAO,VBO;

    void initRenderData();
};

#endif // SPRITECUBERENDERER_H
