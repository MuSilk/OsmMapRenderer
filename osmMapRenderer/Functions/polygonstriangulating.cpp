#include "polygonstriangulating.h"

#include <deque>

int PolygonsTriangulating::n;
vector<PolygonsTriangulating::vec> PolygonsTriangulating::a;
vector<int> PolygonsTriangulating::p;
vector<bool> PolygonsTriangulating::vis;
vector<vector<int>> PolygonsTriangulating::Monotone_Polygon;

void PolygonsTriangulating::polygons_triangulating(const vector<QVector2D>& vertexs, vector<int>& ans){
    ans.clear();
    n=vertexs.size();
    Monotone_Polygon.clear();
    vis.resize(n);p.resize(n);a.resize(n);
    fill(vis.begin(),vis.end(),0);
    for(int i=0;i<n;i++){
        a[i].x=vertexs[i].x();
        a[i].y=vertexs[i].y();
        a[i].id=i;
        p[i]=(i+1)%n;
    }
    Monotone_Decomposition();
    for(auto &i:Monotone_Polygon)Triangulating_Monotone_Polygons(i,ans);
}

void PolygonsTriangulating::get_polygon(int st,int ed){
    vector<int> polygon;
    int x=st;
    while(x!=ed){
        vis[x]=1;
        polygon.push_back(x);
        x=p[x];
    }
    vis[st]=vis[ed]=0;
    polygon.push_back(x);
    Monotone_Polygon.push_back(polygon);
    p[st]=ed;
}


void PolygonsTriangulating::Monotone_Decomposition(){
    vector<vec> e=a;
    auto cmp= [](const vec& a,const vec& b) { return a.y<b.y||(a.y==b.y&&a.x<b.x);};
    sort(e.begin(),e.end(),cmp);
    vec Pre,Nxt;
    size_t cnt=0;
    while(cnt<e.size()){
        vec tmp=e[cnt];
        int pre=(tmp.id-1+n)%n;
        int nxt=(tmp.id+1)%n;
        cnt++;
        Nxt=e[cnt];
        if(vec::cross(a[nxt]-tmp,tmp-a[pre])>0){
            if(tmp.y>a[pre].y&&tmp.y>a[nxt].y){
                if(tmp.y>a[pre].y&&tmp.y>a[nxt].y)get_polygon(Nxt.id,tmp.id);
                else if(tmp.y<a[pre].y&&tmp.y<a[nxt].y)get_polygon(Pre.id,tmp.id);
            }
        }
        Pre=tmp;
    }
    int x=0;
    while(vis[x])x++;
    get_polygon(p[x],x);
}

void PolygonsTriangulating::Triangulating_Monotone_Polygons(vector<int> polygon,vector<int>& ans){
    size_t l=0,r=0;
    auto cmp= [](const int& i,const int& j) { return a[i].x<a[j].x||(a[i].x==a[j].x&&a[i].y<a[j].y);};
    for(size_t i=0;i<polygon.size();i++){
        if(!cmp(polygon[l],polygon[i]))l=i;
        if(cmp(polygon[r],polygon[i]))r=i;
    }
    vector<bool> type(n);
    for(size_t i=(l+1)%polygon.size();i!=r;i=(i+1)%polygon.size())type[polygon[i]]=0;
    for(size_t i=(r+1)%polygon.size();i!=l;i=(i+1)%polygon.size())type[polygon[i]]=1;
    sort(polygon.begin(),polygon.end(),cmp);
    std::deque<int> unused;
    unused.push_back(0);
    unused.push_back(1);
    for(size_t i=2;i<polygon.size();i++){
        if(type[polygon[i]]!=type[polygon[unused.back()]]||i==polygon.size()-1){
            unused.push_back(i);
            while(unused.size()>2){
                int first=unused.front();
                unused.pop_front();
                int second=unused.front();
                ans.push_back(polygon[second]);
                ans.push_back(polygon[first]);
                ans.push_back(polygon[i]);
            }
        }
        else{
            while(unused.size()>=2){
                int first=unused.back();
                unused.pop_back();
                int second=unused.back();
                if(type[polygon[i]]==0&&vec::cross(a[polygon[i]]-a[polygon[first]],a[polygon[first]]-a[polygon[second]])<0){
                    ans.push_back(polygon[second]);
                    ans.push_back(polygon[first]);
                    ans.push_back(polygon[i]);
                }
                else if(type[polygon[i]]==1&&vec::cross(a[polygon[i]]-a[polygon[first]],a[polygon[first]]-a[polygon[second]])>0){
                    ans.push_back(polygon[second]);
                    ans.push_back(polygon[first]);
                    ans.push_back(polygon[i]);
                }
                else{
                    unused.push_back(first);
                    break;
                }
            }
            unused.push_back(i);
        }
    }
}
