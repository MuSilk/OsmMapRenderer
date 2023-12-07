#include "objectbuilding.h"

ObjectBuilding::ObjectBuilding(const Shader& shader,const Way& way,GLfloat height,
                               QVector3D topcolor,QVector3D sidecolor):Way(way){
    vector<QVector2D> vertexs;
    for(auto i:way.nodes)vertexs.push_back(QVector2D(i.normalized_lon,i.normalized_lat));
    PrismRenderer=new staticSpritePrismRenderer(shader,vertexs,height,topcolor,sidecolor);
}

ObjectBuilding::~ObjectBuilding(){
    delete PrismRenderer;
}

void ObjectBuilding::Draw(QVector3D position,QVector3D size,Camera camera,QMatrix4x4 projection,bool _3D){
    PrismRenderer->Draw(position,size,camera,projection,_3D);
}
