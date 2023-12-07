#ifndef OBJECTWAY_H
#define OBJECTWAY_H


#include "Renderer/staticspritelinestripplane.h"
#include "Xml/way.h"

class ObjectWay:Way
{
public:
    ObjectWay(){}
    ObjectWay(const Shader& shader,const Way& way,QVector3D color=QVector3D(1.0,1.0,1.0));
    ~ObjectWay();
    void Draw(QVector3D position,QVector3D size,Camera camera,QMatrix4x4 projection);
private:
    staticSpriteLineStripPlaneRenderer* StripRenderer;
};

#endif // OBJECTWAY_H
