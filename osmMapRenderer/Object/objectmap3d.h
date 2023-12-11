#ifndef OBJECTMAP3D_H
#define OBJECTMAP3D_H

#include "Basics/shader.h"
#include "Basics/camera.h"
#include "Xml/xmlreader.h"
#include "Xml/xmlmanager.h"
#include "Object/ObjectMap/objectbuilding.h"
#include "Object/ObjectMap/objectplane.h"
#include "Object/ObjectMap/objectway.h"
#include "Renderer/dynamicspritelinestripplane.h"


class ObjectMap3D
{
public:
    QVector3D Position,Size;
    bool _3D=true;
    bool _building=true;
    bool _renderpath=false;
    ObjectMap3D();
    ~ObjectMap3D();
    void Load(const char* file,Shader shader,QVector3D pos,QVector3D size);
    void Render(Camera& camera,QMatrix4x4 projection);
    int GetPath(string st,string ed);
    QVector3D GetScreenPosition(QVector3D pos,Camera camera,QMatrix4x4 projection);
private:
    Shader* shader;
    string FileName;
    bool Changed;
    std::vector<ObjectBuilding*> BuildingGroup;
    std::vector<ObjectPlane*> PlaneGroup;
    std::vector<ObjectWay*> WayGroup;
    DynamicSpriteLineStripPlaneRenderer* PathRenderer;
    xmlManager reader;
    void LoadData();
};

#endif // OBJECTMAP3D_H
