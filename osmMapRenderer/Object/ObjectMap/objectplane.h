#ifndef OBJECTPLANE_H
#define OBJECTPLANE_H

#include "Renderer/staticspritepolygonplane.h"
#include "Xml/way.h"

class ObjectPlane:Way
{
public:
    ObjectPlane(){}
    ObjectPlane(const Shader& shader,const Way& way,QVector3D color=QVector3D(1.0,1.0,1.0),GLuint level=0);
    ~ObjectPlane();
    void Draw(QVector3D position,QVector3D size,Camera camera,QMatrix4x4 projection);
private:
    GLuint Level;
    staticSpritePolygonPlaneRenderer* PolygonRenderer;
};

#endif // OBJECTPLANE_H
