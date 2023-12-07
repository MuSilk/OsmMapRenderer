#ifndef OBJECTBUILDING_H
#define OBJECTBUILDING_H

#include "Renderer/staticspriteprism.h"
#include "Xml/way.h"

class ObjectBuilding:Way
{
public:
    ObjectBuilding(){}
    ObjectBuilding(const Shader& shader,const Way& way,GLfloat height,
                   QVector3D topcolor=QVector3D(1.0,1.0,1.0),QVector3D sidecolor=QVector3D(1.0,1.0,1.0));

    ~ObjectBuilding();
    void Draw(QVector3D position,QVector3D size,Camera camera,QMatrix4x4 projection,bool _3D=true);
private:
    staticSpritePrismRenderer* PrismRenderer;
};

#endif // OBJECTBUILDING_H
