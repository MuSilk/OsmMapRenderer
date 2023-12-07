#include "statictextrenderer.h"

//#include "ft2build.h"
//#include FT_FREETYPE_H

enum class staticTextRenderer::TextMode{
    TOP,MIDDLE,BOTTOM,
    LEFT,RIGHT,LEFT_TOP,
    LEFT_BOTTOM,RIGHT_TOP,RIGHT_BOTTOM
};

struct staticTextRenderer::Character{
    GLuint TextureID;
    QVector2D Size;
    QVector2D Bearing;
    GLuint Advance;
};

staticTextRenderer::staticTextRenderer(Shader shader){
    TextShader=shader;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindVertexArray(0);
}

void staticTextRenderer::Load(const char* text,const char* font,GLuint fontSize){
    //failed qaq
//    Characters.clear();
//    FT_Library ft;
//    if(FT_Init_FreeType(&ft))qDebug()<< "ERROR::FREETYPE: Could not init FreeType Library\n";
//    FT_Face face;
//    if(FT_New_Face(ft,font,0,&face))qDebug() << "ERROR::FREETYPE: Failed to load font\n";
//    FT_Set_Pixel_Sizes(face,0,fontSize);
}
