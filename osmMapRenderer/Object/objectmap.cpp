#include "objectmap.h"

ObjectMap::ObjectMap(){
}

ObjectMap::~ObjectMap(){
    for(auto &i:LinestripRendererGroup)delete i;
    for(auto &i:PolygonRendererGroup)delete i;
    LinestripRendererGroup.clear();
    PolygonRendererGroup.clear();
}

void ObjectMap::Load(const char* file,Shader shader2D,Shader shader3D,QVector2D pos,QVector2D size){
    for(auto &i:LinestripRendererGroup)delete i;
    for(auto &i:PolygonRendererGroup)delete i;
    for(auto &i:BuildingGroup)delete i;
    LinestripRendererGroup.clear();
    PolygonRendererGroup.clear();
    BuildingGroup.clear();
    Position=pos;
    Size=size;
    FileName=file;
    Changed=true;
    this->shader2D=new Shader(shader2D);
    this->shader3D=new Shader(shader3D);
}

void ObjectMap::LoadData(){
    reader.LoadFile(FileName.c_str());
    vector<Way> ways;
    for(auto& i:reader.ways)if(i.second.tags.find("landuse")!=i.second.tags.end())ways.emplace_back(i.second);
    for(auto& i:reader.ways)if(i.second.tags.find("landuse")==i.second.tags.end())ways.emplace_back(i.second);


    for(auto& way:ways){
        if(way.tags.find("building")!=way.tags.end()){
            BuildingGroup.push_back(new ObjectBuilding(*shader3D,way,0.1,QVector3D(1.0,0.0,1.0),QVector3D(0.0,0.0,0.0)));
        }
        vector<QVector2D> vertexs;
        for(auto j:way.nodes){
            vertexs.push_back(QVector2D(j.normalized_lon,j.normalized_lat));
        }
        //building,landuse,highway,leisure
        if(way.nodes.size()>0&&way.nodes[0].id==way.nodes.back().id){
           // vertexs.pop_back();vertexs.pop_back();
            if(way.tags.find("building")!=way.tags.end()){
                PolygonRendererGroup.push_back(new staticSpritePolygonRenderer(*shader2D,vertexs,QVector3D(0.77,0.78,0.80)));
            }
            else if(way.tags.find("leisure")!=way.tags.end()){
                PolygonRendererGroup.push_back(new staticSpritePolygonRenderer(*shader2D,vertexs,QVector3D(0.66,0.93,0.76)));
            }
            else if(way.tags.find("water")!=way.tags.end()){
                PolygonRendererGroup.push_back(new staticSpritePolygonRenderer(*shader2D,vertexs,QVector3D(0.68,0.84,1.00)));
            }
            else if(way.tags.find("landuse")!=way.tags.end()){
                //std::cout<<way<<std::endl;
                //PolygonRendererGroup.push_back(new staticSpritePolygonRenderer(*shader,vertexs,QVector3D(0,0,0)));
            }
            else if(way.tags.find("amenity")!=way.tags.end()){
                //PolygonRendererGroup.push_back(new staticSpritePolygonRenderer(*shader,vertexs,QVector3D(1.0,0,0)));
            }
            else if(way.tags.find("highway")!=way.tags.end()){
                //std::cout<<way<<std::endl;
                //PolygonRendererGroup.push_back(new staticSpritePolygonRenderer(*shader,vertexs,QVector3D(0.0,0.0,1.0)));
            }
            else{
                //PolygonRendererGroup.push_back(new staticSpritePolygonRenderer(*shader,vertexs,QVector3D(1.0,0.0,1.0)));
            }
        }
        else{
            LinestripRendererGroup.push_back(new staticSpriteLinestripRenderer(*shader2D,vertexs,QVector3D(0.88,0.88,0.88)));
        }
    }
}

void ObjectMap::Render(Camera& camera,QMatrix4x4 projection){
    //glDisable(GL_DEPTH_TEST);
    if(Changed)LoadData(),Changed=false;
    for(auto i:LinestripRendererGroup)i->Draw(Position,Size);
    for(auto i:PolygonRendererGroup)i->Draw(Position,Size);
    //glEnable(GL_DEPTH_TEST);
    for(auto i:BuildingGroup)i->Draw(QVector3D(-0.1,-0.1,-10),QVector3D(0.1,0.1,0.02),camera,projection);
}
