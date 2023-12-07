#include "objectplane.h"

ObjectPlane::ObjectPlane(const Shader& shader,const Way& way,QVector3D color,GLuint level):Way(way),Level(level){
    vector<QVector2D> vertexs;
    for(auto i:way.nodes)vertexs.push_back(QVector2D(i.normalized_lon,i.normalized_lat));
    PolygonRenderer=new staticSpritePolygonPlaneRenderer(shader,vertexs,color);
}

ObjectPlane::~ObjectPlane(){
    delete PolygonRenderer;
}

void ObjectPlane::Draw(QVector3D position,QVector3D size,Camera camera,QMatrix4x4 projection){
    PolygonRenderer->Draw(position+QVector3D(0,0,0.0001)*Level,size,camera,projection);
}

