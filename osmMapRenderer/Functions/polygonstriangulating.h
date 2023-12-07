#ifndef POLYGONSTRIANGULATING_H
#define POLYGONSTRIANGULATING_H

#include <vector>
#include <QVector2D>

using std::vector;

class PolygonsTriangulating
{
public:
    struct vec{
        double x,y;
        int id;
        vec operator+(vec a){return {x+a.x,y+a.y,id};}
        vec operator-(vec a){return {x-a.x,y-a.y,id};}
        bool operator<(const vec& a)const{return y<a.y||(y==a.y&&x<a.x);}
        static double cross(const vec& a,const vec& b){return a.x*b.y-a.y*b.x;}
    };
    static void polygons_triangulating(const vector<QVector2D>& vertexs, vector<int>& ans);
private:
    static int n;
    static vector<vec> a;
    static vector<int> p;
    static vector<bool> vis;
    static vector<vector<int>> Monotone_Polygon;
    static void get_polygon(int st,int ed);
    static void Monotone_Decomposition();
    static void Triangulating_Monotone_Polygons(vector<int> polygon,vector<int>& ans);
};

#endif // POLYGONSTRIANGULATING_H
