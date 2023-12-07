#include "staticspriteprism.h"

staticSpritePrismRenderer::staticSpritePrismRenderer(const Shader& shader,const vector<QVector2D>& vertexs,GLfloat height,
                                                     QVector3D topcolor,QVector3D sidecolor){
    initializeOpenGLFunctions();
    this->shader=shader;
    Size=vertexs.size();
    Height=height;
    for(int i=0;i<Size;i++){
        Vertexs[0].push_back(vertexs[i].x());
        Vertexs[0].push_back(vertexs[i].y());
        Vertexs[0].push_back(0.0f);
        Vertexs[1].push_back(vertexs[i].x());
        Vertexs[1].push_back(vertexs[i].y());
        Vertexs[1].push_back(height);
        Vertexs[2].push_back(vertexs[i].x());
        Vertexs[2].push_back(vertexs[i].y());
        Vertexs[2].push_back(0.0f);
        Vertexs[2].push_back(vertexs[i].x());
        Vertexs[2].push_back(vertexs[i].y());
        Vertexs[2].push_back(height);
    }
    Vertexs[2].push_back(vertexs[0].x());
    Vertexs[2].push_back(vertexs[0].y());
    Vertexs[2].push_back(0.0f);
    Vertexs[2].push_back(vertexs[0].x());
    Vertexs[2].push_back(vertexs[0].y());
    Vertexs[2].push_back(height);

    initRenderData();
    for(int i=0;i<3;i++)Vertexs[i].clear();
    TopColor=topcolor;
    SideColor=sidecolor;
}

staticSpritePrismRenderer::~staticSpritePrismRenderer(){
    glDeleteVertexArrays(3,VAO);
    glDeleteBuffers(3,VBO);
}

void staticSpritePrismRenderer::Draw(QVector3D position,QVector3D size,Camera camera,QMatrix4x4 projection,bool _3D){
    shader.use();

    QMatrix4x4 view=camera.GetViewMatrix();
    shader.setMat4("view",view);

    shader.setMat4("projection",projection);

    QMatrix4x4 model;
    model.translate(position);
    model.scale(size);
    shader.setMat4("model",model);
    shader.setVec3("color",TopColor);

    glEnable(GL_STENCIL_TEST);

    if(!_3D){
        glDisable(GL_DEPTH_TEST);
        glBindVertexArray(VAO[0]);
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
    }
    else{
        glDisable(GL_DEPTH_TEST);
        glBindVertexArray(VAO[1]);
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

        shader.setVec3("color",SideColor);

        glBindVertexArray(VAO[2]);
        glDrawArrays(GL_TRIANGLE_STRIP,0,2*Size+2);

        glBindVertexArray(0);
    }
    glDisable(GL_STENCIL_TEST);
    shader.unuse();

}

void staticSpritePrismRenderer::initRenderData(){
    glGenVertexArrays(3,VAO);
    glGenBuffers(3,VBO);

    for(int i=0;i<3;i++){
        glBindVertexArray(VAO[i]);
        glBindBuffer(GL_ARRAY_BUFFER,VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, Vertexs[i].size()*sizeof(float), Vertexs[i].data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
    }
}

