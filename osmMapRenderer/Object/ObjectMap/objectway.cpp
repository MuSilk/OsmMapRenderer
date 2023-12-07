#include "objectway.h"

ObjectWay::ObjectWay(const Shader& shader,const Way& way,QVector3D color):Way(way){
    vector<QVector2D> vertexs;
    for(auto i:way.nodes)vertexs.push_back(QVector2D(i.normalized_lon,i.normalized_lat));
    StripRenderer=new staticSpriteLineStripPlaneRenderer(shader,vertexs,color);
}

ObjectWay::~ObjectWay(){
    delete StripRenderer;
}

void ObjectWay::Draw(QVector3D position,QVector3D size,Camera camera,QMatrix4x4 projection){
    StripRenderer->Draw(position,size,camera,projection);
}

