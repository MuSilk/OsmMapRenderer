#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <map>
#include <QOpenGLExtraFunctions>

#include "Basics/shader.h"
#include "Basics/texture2d.h"
#include "Basics/camera.h"

class TextRenderer:QOpenGLExtraFunctions
{
public:
    enum class TextMode;

    TextRenderer(Shader shader);
    ~TextRenderer();
    void Load(std::string& text,std::string& font, GLuint fontSize);
    void RenderText(QVector3D position,QVector3D size,Camera camera,QMatrix4x4 projection ,QVector3D color);
    Texture2D Texttexture;
private:
    Shader TextShader;
    GLuint VAO,VBO;

};
#endif // TEXTRENDERER_H
