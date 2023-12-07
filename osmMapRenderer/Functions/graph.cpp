#include "graph.h"
#include <queue>
#include <algorithm>
#include <QDebug>

Graph::Graph() {}

void Graph::insertPath(Node a,Node b){
    int u,v;
    if(table.find(a.id)==table.end()){
        table_rev[Size]=a.id;
        u=table[a.id]=Size++;
        path.push_back(std::vector<std::pair<int,double>>());
    }
    else u=table[a.id];
    if(table.find(b.id)==table.end()){
        table_rev[Size]=b.id;
        v=table[b.id]=Size++;
        path.push_back(std::vector<std::pair<int,double>>());
    }
    else v=table[b.id];
    double d=NodeDis(a,b);
    path[u].push_back({v,d});
    path[v].push_back({u,d});
}
double Graph::FindPath(Node start,Node end,std::vector<long long>& ans){
    ans.clear();
    if(table.find(start.id)==table.end())return -1;
    if(table.find(end.id)==table.end())return -1;
    int st=table[start.id];
    int ed=table[end.id];
    std::vector<bool> vis(Size);
    std::vector<double> dis(Size,1e18);
    std::vector<int> pre(Size);
    typedef std::pair<double,int> edge;
    std::priority_queue<edge,std::vector<edge>,std::greater<edge>> q;
    dis[st]=0;
    q.push({0,st});
    while(q.size()){
        int u=q.top().second;
        q.pop();
        if(u==ed){
            vis[ed]=1;
            break;
        }

        if(vis[u])continue;
        for(auto i:path[u]){
            int v=i.first;
            double d=i.second;
            if(vis[v])continue;
            if(dis[v]>dis[u]+d){
                dis[v]=dis[u]+d;
                q.push({dis[v],v});
                pre[v]=u;
            }
        }
        vis[u]=1;
    }
    if(vis[ed]){
        for(int i=ed;i!=st;i=pre[i])ans.push_back(i);
        ans.push_back(st);
        std::reverse(ans.begin(),ans.end());
        for(size_t i=0;i<ans.size();i++)ans[i]=table_rev[ans[i]];
        return dis[ed];
    }
    else return -1;
}
double Graph::FindPath(std::vector<Node> start,std::vector<Node> end,std::vector<long long>& ans){
    ans.clear();
    std::vector<bool> vis(Size),ed(Size),st(Size);
    std::vector<double> dis(Size,1e18);
    std::vector<int> pre(Size);
    typedef std::pair<double,int> edge;
    std::priority_queue<edge,std::vector<edge>,std::greater<edge>> q;

    for(auto &i:start){
        if(table.find(i.id)==table.end())continue;
        int p=table[i.id];
        st[p]=1;
        dis[p]=0;
        q.push({0,p});
    }
    for(auto & i:end){
        if(table.find(i.id)==table.end())continue;
        ed[table[i.id]]=1;
    }
    int endpoint=-1;
    while(q.size()){
        int u=q.top().second;
        q.pop();
        if(ed[u]){
            endpoint=u;
            break;
        }

        if(vis[u])continue;
        for(auto i:path[u]){
            int v=i.first;
            double d=i.second;
            if(vis[v])continue;
            if(dis[v]>dis[u]+d){
                dis[v]=dis[u]+d;
                q.push({dis[v],v});
                pre[v]=u;
            }
        }
        vis[u]=1;
    }
    if(endpoint!=-1){
        int i;
        for(i=endpoint;st[i]==0;i=pre[i])ans.push_back(i);
        ans.push_back(i);
        std::reverse(ans.begin(),ans.end());
        for(size_t i=0;i<ans.size();i++)ans[i]=table_rev[ans[i]];
        return dis[endpoint];
    }
    else return -1;
}
void Graph::Clear(){
    path.clear();
    Size=0;
    table.clear();
    table_rev.clear();
}
