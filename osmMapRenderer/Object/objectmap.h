#ifndef OBJECTMAP_H
#define OBJECTMAP_H

#include "Xml/xmlreader.h"
#include "Renderer/staticspritelinestripe.h"
#include "Renderer/staticspritepolygon.h"
#include "Object/ObjectMap/objectbuilding.h"
#include "Object/ObjectMap/objectplane.h"
#include "Object/ObjectMap/objectway.h"

class ObjectMap
{
public:
    ObjectMap();
    ~ObjectMap();
    void Load(const char* file,Shader shader3D,Shader shader2D,QVector2D pos,QVector2D size);
    void Render(Camera& camera,QMatrix4x4 projection);
    QVector2D Position,Size;
private:
    Shader* shader2D;
    Shader* shader3D;
    string FileName;
    bool Changed;
    std::vector<staticSpriteLinestripRenderer*> LinestripRendererGroup;
    std::vector<staticSpritePolygonRenderer*> PolygonRendererGroup;
    std::vector<ObjectBuilding*> BuildingGroup;
    xmlReader reader;
    void LoadData();
};

#endif // OBJECTMAP_H
