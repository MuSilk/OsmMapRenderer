#include "spritecube.h"

SpriteCubeRenderer::SpriteCubeRenderer(Shader& shader){
    initializeOpenGLFunctions();
    this->shader=shader;
    this->initRenderData();
}

SpriteCubeRenderer::~SpriteCubeRenderer(){
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
}

void SpriteCubeRenderer::Draw(Texture2D& texture,QVector3D position,QVector3D size,Camera camera,QMatrix4x4 projection,GLfloat alpha=1.0f){
    shader.use();

    QMatrix4x4 view=camera.GetViewMatrix();
    shader.setMat4("view",view);

    shader.setMat4("projection",projection);

    QMatrix4x4 model;
    model.translate(position);
    model.scale(size);
    shader.setMat4("model",model);

    shader.set1f("alpha",alpha);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,36);
    glBindVertexArray(0);
}

void SpriteCubeRenderer::initRenderData(){
    shader.use();
    shader.setInt("texture1",0);

    GLfloat vertices[]={
        1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,  0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,  0.0f, 0.0f,

        0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,  1.0f, 1.0f,

        1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        1.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,  0.0f, 1.0f,

        0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

        1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,  0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,  0.0f, 1.0f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}
