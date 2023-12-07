#ifndef STATICTEXTRENDERER_H
#define STATICTEXTRENDERER_H

#include<QOpenGLExtraFunctions>

#include "Basics/texture2d.h"
#include "Basics/shader.h"
#include "Basics/resourcemanager.h"

class staticTextRenderer:QOpenGLExtraFunctions
{
public:
    enum class TextMode;
    struct Character;

    std::map<GLchar,Character> Characters;
    Shader TextShader;

    staticTextRenderer(Shader shader);
    void Load(const char* text,const char* font,GLuint fontSize);
    void RenderText(QVector3D position,GLfloat scale,QVector3D color,TextMode mode);
private:
    GLuint VAO,VBO;
};

#endif // STATICTEXTRENDERER_H
