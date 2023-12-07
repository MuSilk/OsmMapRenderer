#include "textrenderer.h"

#include <QPainter>

enum class TextRenderer::TextMode{
    TOP,MIDDLE,BOTTOM,
    LEFT,RIGHT,LEFT_TOP,
    LEFT_BOTTOM,RIGHT_TOP,RIGHT_BOTTOM
};

TextRenderer::TextRenderer(Shader shader){

    initializeOpenGLFunctions();
    TextShader=shader;
    GLfloat vertices[] = {
        0.0f,1.0f,0.0f,1.0f,
        1.0f,0.0f,1.0f,0.0f,
        0.0f,0.0f,0.0f,0.0f,

        0.0f,1.0f,0.0f,1.0f,
        1.0f,1.0f,1.0f,1.0f,
        1.0f,0.0f,1.0f,0.0f
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindVertexArray(0);
}

TextRenderer::~TextRenderer(){
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO);
}

void TextRenderer::Load(std::string& text,std::string& font,GLuint fontSize){
    QFont qfont;
    qfont.setPixelSize(fontSize);
    qfont.setFamily(font.c_str());

    QRect rect=QFontMetrics(qfont).boundingRect(text.c_str());
    QImage img(rect.width(),rect.height(),QImage::Format_ARGB32);
    img.fill(0);
    QPainter painter(&img);
    painter.setFont(qfont);
    painter.setPen(QColor(255,255,255));
    painter.drawText(-rect.x(),-rect.y(),text.c_str());
    img.mirror();
    Texttexture=Texture2D(img);
}

void TextRenderer::RenderText(QVector3D position,QVector3D size,Camera camera,QMatrix4x4 projection, QVector3D color){
    TextShader.use();

    QMatrix4x4 view=camera.GetViewMatrix();
    TextShader.setMat4("view",view);

    TextShader.setMat4("projection",projection);

    QMatrix4x4 model;
    model.translate(position);
    model.scale(size);
    TextShader.setMat4("model",model);

    TextShader.setVec3("color",color);

    TextShader.setInt("image",0);
    glActiveTexture(GL_TEXTURE0);
    Texttexture.Bind();

    glDisable(GL_DEPTH_TEST);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,6);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);
}
