#include "xmlreader.h"

#include <iostream>
#include <QString>

#include "tinyxml.h"

using std::stoll;
using std::stold;

xmlReader::xmlReader(){}

void xmlReader::LoadFile(const char* path){
    ways.clear();
    nodes.clear();

    TiXmlDocument tinyXmlDoc(path);
    tinyXmlDoc.LoadFile();
    TiXmlElement* root = tinyXmlDoc.RootElement();

    TiXmlElement* bounds=root->FirstChildElement("bounds");
    minlat=stold(bounds->Attribute("minlat"));
    maxlat=stold(bounds->Attribute("maxlat"));
    minlon=stold(bounds->Attribute("minlon"));
    maxlon=stold(bounds->Attribute("maxlon"));
    Width=maxlon-minlon;
    Height=maxlat-minlat;
    //std::cout<<minlat<<" "<<maxlat<<" "<<minlon<<" "<<maxlon<<"\n";

    TiXmlElement* nodeElement = root->FirstChildElement("node");
    for (; nodeElement; nodeElement = nodeElement->NextSiblingElement("node")) {
        Node node;
        node.id = stoll(nodeElement->Attribute("id"));
        node.lon = stold(nodeElement->Attribute("lon"));
        node.lat = stold(nodeElement->Attribute("lat"));
        node.normalized_lon=(node.lon-minlon)/Width;
        node.normalized_lat=(node.lat-minlat)/Height;
        nodes[node.id] = node;
    }
    TiXmlElement* wayElement = root->FirstChildElement("way");
    for (; wayElement; wayElement=wayElement->NextSiblingElement("way")) {
        Way way;
        way.id = stoll(wayElement->Attribute("id"));
        TiXmlElement* childNode = wayElement->FirstChildElement("nd");
        for (; childNode; childNode = childNode->NextSiblingElement("nd")) {
            long long ref = stoll(childNode->Attribute("ref"));
            way.nodes.push_back(nodes[ref]);
        }
        TiXmlElement* childTag = wayElement->FirstChildElement("tag");
        for (; childTag; childTag = childTag->NextSiblingElement("tag")) {
            string name = childTag->Attribute("k");
            string value = childTag->Attribute("v");
            way.tags[name] = value;
        }
        way.InitAveNode();
        ways[way.id] = way;
    }
}

void xmlReader::PrintNodes(){
    for(const auto& i:nodes){
        std::cout<<i.second<<std::endl;
    }
    std::cout<<nodes.size()<<" in total"<<std::endl;
}

void xmlReader::PrintWays(){
    for(const auto& i:ways){
        std::cout<<i.second<<std::endl;
    }
    std::cout<<ways.size()<<" in total"<<std::endl;
}
