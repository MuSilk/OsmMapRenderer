#include "dynamicspritelinestripplane.h"

DynamicSpriteLineStripPlaneRenderer::DynamicSpriteLineStripPlaneRenderer(const Shader& shader,QVector3D color) {
    initializeOpenGLFunctions();
    this->shader=shader;
    initRenderData();
    Color=color;
}

DynamicSpriteLineStripPlaneRenderer::~DynamicSpriteLineStripPlaneRenderer(){
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
}

void DynamicSpriteLineStripPlaneRenderer::UpdateData(const vector<float>& data){
    Vertexs=data;
    Size=data.size()/3;
    Changed=true;
}

void DynamicSpriteLineStripPlaneRenderer::Draw(QVector3D position,QVector3D size,Camera camera,QMatrix4x4 projection){
    shader.use();
    QMatrix4x4 view=camera.GetViewMatrix();
    shader.setMat4("view",view);
    shader.setMat4("projection",projection);

    QMatrix4x4 model=QMatrix4x4();
    model.translate(position);
    model.scale(size);
    shader.setMat4("model",model);
    shader.setVec3("color",Color);

    glBindVertexArray(VAO);
    if(Changed){
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferSubData(GL_ARRAY_BUFFER,0,Vertexs.size()*sizeof(float),Vertexs.data());
        Changed=false;
    }

    glDrawArrays(GL_LINE_STRIP, 0, Size);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    shader.unuse();
}

void DynamicSpriteLineStripPlaneRenderer::initRenderData(){
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER, 32768*sizeof(float), NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}
