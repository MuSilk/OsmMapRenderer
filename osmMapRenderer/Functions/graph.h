#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include "Xml/node.h"

class Graph
{
public:
    Graph();
    void insertPath(Node a,Node b);
    double FindPath(Node start,Node end,std::vector<long long>& ans);
    double FindPath(std::vector<Node> start,std::vector<Node> end,std::vector<long long>& ans);
    void Clear();
private:
    int Size=0;
    std::map<long long,int> table;
    std::map<int,long long> table_rev;
    std::vector<std::vector<std::pair<int,double>>> path;
};

#endif // GRAPH_H
