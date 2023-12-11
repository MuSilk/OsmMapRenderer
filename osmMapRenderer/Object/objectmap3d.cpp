#include "objectmap3d.h"

ObjectMap3D::ObjectMap3D(){
    PathRenderer=nullptr;
    shader=nullptr;
}

ObjectMap3D::~ObjectMap3D(){
    for(auto &i:BuildingGroup)delete i;
    for(auto &i:PlaneGroup)delete i;
    for(auto &i:WayGroup)delete i;
    BuildingGroup.clear();
    PlaneGroup.clear();
    WayGroup.clear();
    delete PathRenderer;
}

void ObjectMap3D::Load(const char* file,Shader shader,QVector3D pos,QVector3D size){
    for(auto &i:BuildingGroup)delete i;
    for(auto &i:PlaneGroup)delete i;
    for(auto &i:WayGroup)delete i;
    BuildingGroup.clear();
    PlaneGroup.clear();
    WayGroup.clear();

    Position=pos;
    Size=size;
    FileName=file;
    Changed=true;
    delete this->shader;
    this->shader=new Shader(shader);
    _renderpath=false;
    if(PathRenderer==nullptr)PathRenderer=new DynamicSpriteLineStripPlaneRenderer(shader,QVector3D(0.0,0.0,1.0));
}

void ObjectMap3D::LoadData(){
    reader.LoadFile(FileName.c_str());
    for(auto& i:reader.ways){
        Way& way=i.second;
        if(way.tags.find("building")!=way.tags.end()){
            BuildingGroup.push_back(new ObjectBuilding(*shader,way,1.0,QVector3D(0.90,0.95,1.00),QVector3D(0.77,0.78,0.80)));
        }
        else if(way.nodes[0].id==way.nodes.back().id){
            if(way.tags.find("leisure")!=way.tags.end())
                PlaneGroup.push_back(new ObjectPlane(*shader,way,QVector3D(0.66,0.93,0.76),2));
            else if(way.tags["landuse"]=="forest")
                PlaneGroup.push_back(new ObjectPlane(*shader,way,QVector3D(0.66,0.93,0.76),2));
            else if(way.tags["landuse"]=="grass")
                PlaneGroup.push_back(new ObjectPlane(*shader,way,QVector3D(0.66,0.93,0.76),2));
            else if(way.tags["landuse"]=="meadow")
                PlaneGroup.push_back(new ObjectPlane(*shader,way,QVector3D(0.66,0.93,0.76),2));
            else if(way.tags["landuse"]=="parking")
                PlaneGroup.push_back(new ObjectPlane(*shader,way,QVector3D(0.66,0.93,0.76),2));
            else if(way.tags["amenity"]=="parking")
                PlaneGroup.push_back(new ObjectPlane(*shader,way,QVector3D(0.66,0.93,0.76),2));
            else if(way.tags["landuse"]=="residential")
                PlaneGroup.push_back(new ObjectPlane(*shader,way,QVector3D(0.89,0.92,0.95)));
            else if(way.tags["amenity"]=="hospital")
                PlaneGroup.push_back(new ObjectPlane(*shader,way,QVector3D(1.00,0.94,0.95)));
            else if(way.tags["amenity"]=="university")
                PlaneGroup.push_back(new ObjectPlane(*shader,way,QVector3D(0.94,0.98,0.99),1));
            else if(way.tags["amenity"]=="school")
                PlaneGroup.push_back(new ObjectPlane(*shader,way,QVector3D(0.94,0.98,0.99),1));
            else if(way.tags["amenity"]=="kindergarten")
                PlaneGroup.push_back(new ObjectPlane(*shader,way,QVector3D(0.94,0.98,0.99),1));
            else if(way.tags["landuse"]=="commercial")
                PlaneGroup.push_back(new ObjectPlane(*shader,way,QVector3D(0.85,0.85,0.96)));
//            else if(way.tags["landuse"]=="retail")
//                PlaneGroup.push_back(new ObjectPlane(*shader,way,QVector3D(0.85,0.85,0.96)));
            else if(way.tags.find("water")!=way.tags.end())
                PlaneGroup.push_back(new ObjectPlane(*shader,way,QVector3D(0.68,0.84,1.00),3));
            else if(way.tags["natural"]=="water")
                PlaneGroup.push_back(new ObjectPlane(*shader,way,QVector3D(0.68,0.84,1.00),3));
            else;
                //std::cout<<way<<std::endl;
                //PlaneGroup.push_back(new ObjectPlane(*shader,way,QVector3D(1.0,0.0,1.0),4));
        }
        else{
            WayGroup.push_back(new ObjectWay(*shader,way,QVector3D(1.0,1.0,1.0)));
        }
    }

}

void ObjectMap3D::Render(Camera& camera,QMatrix4x4 projection){
    if(Changed)LoadData(),Changed=false;
    for(auto i:PlaneGroup)i->Draw(Position,Size,camera,projection);
    for(auto i:WayGroup)i->Draw(Position+QVector3D(0,0,0.0004),Size,camera,projection);
    if(_building)for(auto i:BuildingGroup)i->Draw(Position+QVector3D(0,0,0.0004),Size,camera,projection,_3D);

    if(_renderpath)PathRenderer->Draw(Position+QVector3D(0,0,0.0005),Size,camera,projection);
}

int ObjectMap3D::GetPath(string st,string ed){
    if(reader.table.find(st)==reader.table.end())return -1;
    if(reader.table.find(ed)==reader.table.end())return -2;
    vector<Node> ans;
    double d=reader.GetPath(st,ed,ans);
    vector<float> path;
    for(auto i:ans){
        path.push_back(i.normalized_lon);
        path.push_back(i.normalized_lat);
        path.push_back(0);
    }
    _renderpath=true;
    PathRenderer->UpdateData(path);
    return d;
}

QVector3D ObjectMap3D::GetScreenPosition(QVector3D pos,Camera camera,QMatrix4x4 projection){
    QMatrix4x4 view=camera.GetViewMatrix();
    QMatrix4x4 model;
    model.translate(Position);
    model.scale(Size);
    return QVector3D(projection*view*model*QVector4D(pos,1.0));
}
