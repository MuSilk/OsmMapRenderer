#include "staticspritepolygonplane.h"

staticSpritePolygonPlaneRenderer::staticSpritePolygonPlaneRenderer(const Shader& shader,const vector<QVector2D>& vertexs,QVector3D color){
    initializeOpenGLFunctions();
    this->shader=shader;
    Size=vertexs.size();
    for(int i=0;i<Size;i++){
        Vertexs.push_back(vertexs[i].x());
        Vertexs.push_back(vertexs[i].y());
        Vertexs.push_back(0.0f);
    }
    initRenderData();
    Vertexs.clear();
    Color=color;
}

staticSpritePolygonPlaneRenderer::~staticSpritePolygonPlaneRenderer(){
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
}

void staticSpritePolygonPlaneRenderer::Draw(QVector3D position,QVector3D size,Camera camera,QMatrix4x4 projection){
    shader.use();

    QMatrix4x4 view=camera.GetViewMatrix();
    shader.setMat4("view",view);

    shader.setMat4("projection",projection);

    QMatrix4x4 model;
    model.translate(position);
    model.scale(size);
    shader.setMat4("model",model);
    shader.setVec3("color",Color);

    glEnable(GL_STENCIL_TEST);
    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(VAO);
    glStencilOp(GL_KEEP,GL_KEEP,GL_INVERT);
    glStencilFunc(GL_ALWAYS,1,1);
    glStencilMask(0x1);
    glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
    glDrawArrays(GL_TRIANGLE_FAN,0,Size);
    glEnable(GL_DEPTH_TEST);
    glStencilFunc(GL_NOTEQUAL,0,1);
    glStencilOp(GL_ZERO,GL_ZERO,GL_ZERO);
    glStencilMask(0x1);
    glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
    glDrawArrays(GL_TRIANGLE_FAN, 0, Size);

    glDisable(GL_STENCIL_TEST);

    glBindVertexArray(0);
    shader.unuse();
}

void staticSpritePolygonPlaneRenderer::initRenderData(){
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER, Vertexs.size()*sizeof(float), Vertexs.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

